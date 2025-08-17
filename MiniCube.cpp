// MiniCube.cpp
#include "MiniCube.h"
#include <cstring>

MiniCube::MiniCube() : left(0), right(0), mid(0) {
    strcpy(this->name, "");
}

MiniCube::MiniCube(char n[4], int l, int r, int t) : left(l), right(r), mid(t) {
    strcpy(this->name, n);
}

MiniCube MiniCube::clone() const {
    return MiniCube((char*)name, left, right, mid);
}