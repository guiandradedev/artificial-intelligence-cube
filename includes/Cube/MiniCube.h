#pragma once

class MiniCube {
public:
    int left;
    int right;
    int mid;
    int index;
    short int orientation;

    MiniCube();
    MiniCube(int l, int r, int t, short int orientation, int index); 
    MiniCube clone() const;
    void print();


    bool operator==(const MiniCube& other) const {
        return left == other.left && right == other.right && mid == other.mid && orientation == other.orientation;
    }
    bool operator!=(const MiniCube& other) const {
        return left != other.left || right != other.right || mid != other.mid || orientation != other.orientation;
    }
};