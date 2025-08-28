// MiniCube.cpp
#include "MiniCube.h"
#include <cstring>
#include <iostream>

using namespace std;
MiniCube::MiniCube() : left(0), right(0), mid(0), orientation(0) {
    // strcpy(this->name, "");
}

MiniCube::MiniCube(int l, int r, int t, short int o) 
// MiniCube::MiniCube(char n[4], int l, int r, int t, short int o) 
    : left(l), right(r), mid(t), orientation(o) {
    // strcpy(this->name, n);
}

MiniCube MiniCube::clone() const {
    // char tempName[4];
    // strcpy(tempName, name);
    // return MiniCube(tempName, left, right, mid, orientation);
    return MiniCube(left, right, mid, orientation);
}

void MiniCube::print() {
    cout << left << 
            right <<
            // name <<
            mid << endl;

}
