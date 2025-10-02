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

// Linux: g++ tests/a_star_noises.cpp $(find src -name "*.cpp" | grep -v "src/main.cpp" | grep -v "src/UI/") -I ./includes -o bench_astar && ./bench_astar

int main() {
    srand(time(NULL));
    
    Cube cubo;
    cubo.init();
    Solver solver;

    // Define tamanhos fixos para cada coluna
    cout << left
         << setw(8) << "Index"
         << setw(10) << "Shuffles"
         << setw(7) << "Noise"
         << setw(18) << "Execution Time"
         << setw(8) << "States" << endl;
    cout << string(60, '-') << endl;

    int noise_max = 5;
    int shuffle_max = 15;

    std::vector<short int> path;
    int num_tries = 0;

    Cube copy = cubo.cloneMatrix();

    int index = 0;
    for(int noise = 1; noise < noise_max; noise++) {
        for(int shuffle = 1; shuffle < shuffle_max; shuffle++) {
            path.clear(); 
            num_tries = 0;
            
            auto start = std::chrono::high_resolution_clock::now();
            
            copy = cubo.shuffle(shuffle, false);
            solver.A_star(copy, path, &num_tries, noise); 

            auto end = std::chrono::high_resolution_clock::now();
            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            
            // Define tamanhos fixos para cada coluna
            cout << left
                 << setw(8) << index
                 << right
                 << setw(5) << shuffle
                 << setw(7) << noise
                 << setw(14) << (to_string(duration_ms) + "ms")
                 << setw(12) << num_tries << endl;
            index++;
        }
    }
}