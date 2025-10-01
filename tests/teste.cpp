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

// Linux: g++ tests/teste.cpp $(find src -name "*.cpp" | grep -v "src/main.cpp" | grep -v "src/UI/") -I ./includes -o teste && ./teste

void path_reconstruct(const char* name, std::vector<short int> path, int num_tries, long long duration_ms) {
    cout << "\nExecucão do algoritmo " << name << endl;
    cout << "Reconstrucão do cubo: ";
    size_t i;
    for (i = 0; i < path.size(); ++i)
    {
        cout << Solver::moviments_name[path[i]] << (i == path.size() - 1 ? "" : " -> ");
    }
    cout << endl;
    cout << "Total de movimentos: " << i << endl;
    cout << "Total de iteracões (estados visitados): " << num_tries << endl;
    cout << "Tempo de execucão: " << std::to_string(duration_ms) + " ms" << endl;
}

int main() {
    srand(time(NULL));

    Cube cubo;
    cubo.init();
    Solver solver;

    // cubo = cubo.shuffle(15, true);
        // Primeiro conjunto de movimentos: LBW - UBW - LBW - FFW - UFW - FBW - UBW - FFW - UFW - UFW
    cout << "Aplicando primeiro conjunto de movimentos:" << endl;
    cout << "LBW - UBW - LBW - FFW - UFW - FBW - UBW - FFW - UFW - UFW" << endl;
    
    // LBW = 3, UBW = 1, LBW = 3, FFW = 4, UFW = 0, FBW = 5, UBW = 1, FFW = 4, UFW = 0, UFW = 0
    cubo = cubo.applyMove(3); // LBW
    cubo = cubo.applyMove(1); // UBW
    cubo = cubo.applyMove(3); // LBW
    cubo = cubo.applyMove(4); // FFW
    cubo = cubo.applyMove(0); // UFW
    cubo = cubo.applyMove(5); // FBW
    cubo = cubo.applyMove(1); // UBW
    cubo = cubo.applyMove(4); // FFW
    cubo = cubo.applyMove(0); // UFW
    cubo = cubo.applyMove(0); // UFW
    
    // Segundo conjunto de movimentos: LFW - FBW - UFW - FFW - UBW - LBW - FBW - UBW - LFW - UBW
    cout << "Aplicando segundo conjunto de movimentos:" << endl;
    cout << "LFW - FBW - UFW - FFW - UBW - LBW - FBW - UBW - LFW - UBW" << endl;
    
    // LFW = 2, FBW = 5, UFW = 0, FFW = 4, UBW = 1, LBW = 3, FBW = 5, UBW = 1, LFW = 2, UBW = 1
    cubo = cubo.applyMove(2); // LFW
    cubo = cubo.applyMove(5); // FBW
    cubo = cubo.applyMove(0); // UFW
    cubo = cubo.applyMove(4); // FFW
    cubo = cubo.applyMove(1); // UBW
    cubo = cubo.applyMove(3); // LBW
    cubo = cubo.applyMove(5); // FBW
    cubo = cubo.applyMove(1); // UBW
    cubo = cubo.applyMove(2); // LFW
    cubo = cubo.applyMove(1); // UBW
    cout << endl;
    

    std::vector<short int> path;
    int num_tries = 0;
    auto start = std::chrono::high_resolution_clock::now();
    bool find = solver.dfs(cubo, path, &num_tries);
    if(!find) {
        cout << "Nao encontrado" << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    path_reconstruct("DFS", path, num_tries, duration_ms);

    path.clear(); num_tries = 0;
    auto start_bfs = std::chrono::high_resolution_clock::now();
    solver.bfs(cubo, path, &num_tries); 
    auto end_bfs = std::chrono::high_resolution_clock::now();
    auto duration_bfs = std::chrono::duration_cast<std::chrono::milliseconds>(end_bfs - start_bfs).count();
    cout << setw(12) << (to_string(duration_bfs) + "ms") << setw(12) << num_tries;
    path_reconstruct("BFS", path, num_tries, duration_ms);

    // cubo.applyMove()
    
    return 0;
}