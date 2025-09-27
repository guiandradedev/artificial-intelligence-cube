#include <iostream>
#include "Cube/Cube.h"
#include "Solver.h"
#include "vector"
#include "Tools/Colors.h"
#include "Tools/messages.h"
#include "Cube/Move.h"
#include <chrono>
#include <iomanip>

using namespace std;

// Linux: g++ tests/benchmark.cpp $(find src -name "*.cpp" | grep -v "src/main.cpp" | grep -v "src/UI/") -I ./includes -o benchmark && ./benchmark

int main() {
    srand(time(NULL));

    Cube cubo;
    cubo.init();
    Solver solver;

    cout << left 
         << setw(8) << "Index"
         << setw(10) << "Shuffles"
         << right 
         << setw(12) << "BFS Time"
         << setw(12) << "BFS States"
         << setw(12) << "DFS Time"
         << setw(12) << "DFS States"
         << setw(12) << "A* Time"
         << setw(12) << "A* States" << endl;
    cout << string(88, '-') << endl;

    int shuffle_max = 16;

    std::vector<short int> path;
    int num_tries = 0;

    Cube copy = cubo.cloneMatrix();

    int index = 0;
    for(int shuffle = 1; shuffle < shuffle_max; shuffle++) {
        copy = cubo.shuffle(shuffle, false);
        
        cout << left 
             << setw(8) << index
             << setw(10) << shuffle
             << right;

        // BFS
        path.clear(); num_tries = 0;
        auto start_bfs = std::chrono::high_resolution_clock::now();
        solver.bfs(copy, path, &num_tries); 
        auto end_bfs = std::chrono::high_resolution_clock::now();
        auto duration_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(end_bfs - start_bfs).count();
        cout << setw(12) << (to_string(duration_bfs) + "ms") << setw(12) << num_tries;

        // DFS
        path.clear(); num_tries = 0;
        auto start_dfs = std::chrono::high_resolution_clock::now();
        solver.dfs(copy, path, &num_tries); 
        auto end_dfs = std::chrono::high_resolution_clock::now();
        auto duration_dfs = std::chrono::duration_cast<std::chrono::milliseconds>(end_dfs - start_dfs).count();
        cout << setw(12) << (to_string(duration_dfs) + "ms") << setw(12) << num_tries;
        
        // A*
        path.clear(); num_tries = 0;
        auto start_astar = std::chrono::high_resolution_clock::now();
        solver.A_star(copy, path, &num_tries, -1); 
        auto end_astar = std::chrono::high_resolution_clock::now();
        auto duration_astar = std::chrono::duration_cast<std::chrono::milliseconds>(end_astar - start_astar).count();
        cout << setw(12) << (to_string(duration_astar) + "ms") << setw(12) << num_tries << endl;

        index++;
    }
    
    return 0;
}