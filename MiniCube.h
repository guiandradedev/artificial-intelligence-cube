// MiniCube.h
#ifndef MINICUBE_H
#define MINICUBE_H

class MiniCube {
public:
    int left;
    int right;
    int mid;
    char name[4];

    MiniCube();
    MiniCube(char n[4], int l, int r, int t); 
    MiniCube clone() const;
};

#endif
