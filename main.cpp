#include "Cube.h"

using namespace std;

int main() {
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;

    Cube newCube = cubo.R();

    cout << "" << endl;
    newCube.print();
    cout << "" << endl;

    newCube = newCube.U();

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
