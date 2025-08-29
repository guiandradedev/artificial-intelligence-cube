#pragma once

#include "Cube.h"
#include <functional>

// namespace Solver {
//     extern Cube final_state;

//     void bfs(Cube cube);
// }

class Solver {
protected:
    // void algorithm(Cube cube, function<Cube()> getNext, );

public:
    Solver();       
    Cube final_state;

    void bfs(Cube cube);

};