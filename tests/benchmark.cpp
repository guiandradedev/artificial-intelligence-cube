#include <iostream>
#include "Cube/Cube.h"
#include "Solver.h"
#include "vector"
#include "Tools/Colors.h"
#include "Tools/messages.h"
#include "Cube/Move.h"

using namespace std;

// Linux: g++ tests/commands.cpp $(find src -name "*.cpp" | grep -v "src/main.cpp") -I ./includes -o test_runner && ./test_runner

int main() {
    srand(time(NULL));
    header(false);
    
    Cube cubo;
    cubo.init();

    Solver solver;

    char op = ' ';
    

    return 0;
}