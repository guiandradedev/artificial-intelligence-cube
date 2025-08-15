// MiniCube.h
#ifndef MINICUBE_H
#define MINICUBE_H

class MiniCube {
public:
    int left;
    int right;
    int top;
    char name[4];

    MiniCube(); // Construtor padrão
    MiniCube(char name[4], int l, int r, int t); // Construtor com valores
};

#endif
