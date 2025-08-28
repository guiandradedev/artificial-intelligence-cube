#include "Cube.h"

// x - tras | frente
// y - esquerda | direita
// z - cima | baixo
using namespace std;

int main() {
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;

    cubo.position(0,0,0).print();
    cubo.position(1,0,0).print();

    Cube newCube = cubo.cloneMatrix();

    newCube = newCube.U_FW();

    // cout << "" << endl;
    // newCube.print();
    // cout << "" << endl;

    // newCube = newCube.R();

    // cout << "" << endl;
    // newCube.print();
    // cout << "" << endl;

    cubo.print();

    // Cube shuffledCube = cubo.shuffle(1);
    // shuffledCube.print();

    return 0;
}
