#include <iostream>
#include "Cube/Cube.h"
#include "Solver.h"
#include "vector"
#include "Tools/Colors.h"
#include "Tools/messages.h"
#include "Cube/Move.h"

using namespace std;

// Linux: g++ tests/commands.cpp $(find src -name "*.cpp" | grep -v "src/main.cpp" | grep -v "src/UI/") -I ./includes -o test_runner && ./test_runner

int main() {
    srand(time(NULL));
    header(false);
    
    Cube cubo;
    cubo.init();

    Solver solver;

    char op = ' ';
    do {
        cout << "\n-----------------------------------\n";
        cubo.print();
        cli_message();
        cout << Colors::OKCYAN << "Q/q:   " << Colors::ENDC << "Sair do programa" << endl;
        cout << "Sua opção: ";
        cin >> op;

        std::vector<short int> path;
        int num_tries = 0;

        switch (op) {
            case 's':
            case 'S':
                cubo = cubo.shuffle(10, true);
                break;
            case 'a':
            case 'A':
                solver.A_star(cubo, path, &num_tries, -1);
                break;
            case 'b':
            case 'B':
                solver.bfs(cubo, path, &num_tries);
                break;
            case 'd':
            case 'D':
                solver.dfs(cubo, path, &num_tries);
                break;
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