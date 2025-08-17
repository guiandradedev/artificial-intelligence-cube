#include "Cube.h"

using namespace std;

int main() {
    Cube cubo;
    cubo.init();
    cubo.print();
    cout << "" << endl;

    Cube newCube = cubo.U();

    cout << "" << endl;
    newCube.print();
    cout << "" << endl;

    cubo.print();

    return 0;
}
