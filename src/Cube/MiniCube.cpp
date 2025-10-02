#include "Cube/MiniCube.h"
#include <cstring>
#include <iostream>

using namespace std;
MiniCube::MiniCube() : left(0), right(0), mid(0), orientation(0), index(0) {}

MiniCube::MiniCube(int l, int r, int t, short int o, int i)
    : left(l), right(r), mid(t), orientation(o), index(i)
{
}

MiniCube MiniCube::clone() const
{
    return MiniCube(left, right, mid, orientation, index);
}

void MiniCube::print()
{
    cout << left << right << mid << orientation << endl;
}
