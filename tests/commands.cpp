#include <iostream>
#include "Cube/Cube.h"
#include "Solver.h"
#include "vector"
#include "Tools/Colors.h"
#include "Tools/messages.h"
#include "Cube/Move.h"
#include <chrono>

using namespace std;

// Linux: g++ tests/commands.cpp $(find src -name "*.cpp" | grep -v "src/main.cpp" | grep -v "src/UI/") -I ./includes -o test_runner && ./test_runner

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

int main()
{
    srand(time(NULL));
    header(false);

    Cube cubo;
    cubo.init();

    Solver solver;

    char op = ' ';
    do
    {
        cout << "\n-----------------------------------\n";
        cubo.print();
        cli_message();
        cout << Colors::OKCYAN << "Q/q:   " << Colors::ENDC << "Sair do programa" << endl;
        cout << "Sua opção: ";
        cin >> op;

        std::vector<short int> path;
        int num_tries = 0;

        switch (op)
        {
        case 's':
        case 'S':
            cubo = cubo.shuffle(10, true);
            break;
        // 2. Adicionado escopo local com {} para cada case que declara variáveis
        case 'a':
        case 'A':
        {
            auto start = std::chrono::high_resolution_clock::now();
            solver.A_star(cubo, path, &num_tries, -1);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            path_reconstruct("A*", path, num_tries, duration_ms);
            break;
        }
        case 'b':
        case 'B':
        {
            auto start = std::chrono::high_resolution_clock::now();
            solver.bfs(cubo, path, &num_tries);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            path_reconstruct("BFS", path, num_tries, duration_ms);
            break;
        }
        case 'd':
        case 'D':
        {
            auto start = std::chrono::high_resolution_clock::now();
            solver.dfs(cubo, path, &num_tries);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            path_reconstruct("DFS", path, num_tries, duration_ms);
            break;
        }
        case 'l':
            cubo = Move::L_FW(cubo);
            break;
        case 'L':
            cubo = Move::L_BW(cubo);
            break;
        case 'u':
            cubo = Move::U_FW(cubo);
            break;
        case 'U':
            cubo = Move::U_BW(cubo);
            break;
        case 'f':
            cubo = Move::F_FW(cubo);
            break;
        case 'F':
            cubo = Move::F_BW(cubo);
            break;
        case 'q':
        case 'Q':
            cout << "Saindo..." << endl;
            break;
        default:
            Colors::error("Opção inválida!");
            break;
        }

    } while (op != 'q' && op != 'Q');

    return 0;
}