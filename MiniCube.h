// MiniCube.h
#ifndef MINICUBE_H
#define MINICUBE_H

class MiniCube {
public:
    int left;
    int right;
    int mid;
    // char name[4];
    short int orientation;

    MiniCube();
    MiniCube(int l, int r, int t, short int orientation); 
    // MiniCube(char n[4], int l, int r, int t, short int orientation); 
    MiniCube clone() const;
    void print();
};

#endif
