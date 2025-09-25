#include "Tools/messages.h"
#include "Tools/Colors.h"
#include <iostream>

using namespace std;

void cli_message() {
    Colors::bold("Comandos esperados:");
    cout << Colors::OKCYAN << "Q/q:   " << Colors::ENDC << "Finalizar execucão" << endl;
    cout << Colors::OKCYAN << "S/s:   " << Colors::ENDC << "Embaralha o cubo" << endl;
    cout << Colors::OKCYAN << "A/a:   " << Colors::ENDC << "Resolve o algoritmo A*" << endl;
    cout << Colors::OKCYAN << "B/b:   " << Colors::ENDC << "Resolve o algoritmo BFS" << endl;
    cout << Colors::OKCYAN << "D/d:   " << Colors::ENDC << "Resolve o algoritmo DFS" << endl;
    cout << Colors::OKCYAN << "l/L:   " << Colors::ENDC << "Movimento Left/Left'" << endl;
    cout << Colors::OKCYAN << "u/U:   " << Colors::ENDC << "Movimento Up/Up'" << endl;
    cout << Colors::OKCYAN << "f/F:   " << Colors::ENDC << "Movimento Face/Face'" << endl;
}

void ui_message() {
    Colors::bold("Comandos esperados:");
    cout << Colors::OKCYAN << "Setas: " << Colors::ENDC << "Rotacionam a câmera" << endl;
    cout << Colors::OKCYAN << "Q/q:   " << Colors::ENDC << "Finalizar execucão" << endl;
    cout << Colors::OKCYAN << "S/s:   " << Colors::ENDC << "Embaralha o cubo" << endl;
    cout << Colors::OKCYAN << "A/a:   " << Colors::ENDC << "Resolve o algoritmo A*" << endl;
    cout << Colors::OKCYAN << "B/b:   " << Colors::ENDC << "Resolve o algoritmo BFS" << endl;
    cout << Colors::OKCYAN << "D/d:   " << Colors::ENDC << "Resolve o algoritmo DFS" << endl;
    cout << Colors::OKCYAN << "l/L:   " << Colors::ENDC << "Movimento Left/Left'" << endl;
    cout << Colors::OKCYAN << "u/U:   " << Colors::ENDC << "Movimento Up/Up'" << endl;
    cout << Colors::OKCYAN << "f/F:   " << Colors::ENDC << "Movimento Face/Face'" << endl;
}

void header(bool ui) {
    Colors::header("Cubo Magico 2x2");
    cout << endl;
    cout << "Proposto na disciplina PI: Inteligencia Artificial e Aprendizado Supervisionado" << endl;
    cout << endl;
    Colors::underline("Desenvolvido por:");
    cout << "Guilherme Andrade" << endl;
    cout << "Guilherme Ximenes" << endl;
    cout << "Pedro Gasparotto" << endl;
    cout << "Luigi Zanon" << endl;
    cout << endl;

    if(ui) {
        ui_message();
    } else {
        cli_message();
    }

    cout << endl;
}