#include "Node/DFSNode.h"

DFSNode::DFSNode() : Node(), depth(0) {}

DFSNode::DFSNode(const Cube& cube, Node* root, short int mov, int depth)
    : Node(cube, root, mov), depth(depth) {}