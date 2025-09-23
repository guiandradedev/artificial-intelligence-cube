#include "AstarNode.h"

AstarNode::AstarNode() : Node(), g_cost(0), f_cost(0) {}

AstarNode::AstarNode(const Cube& cube, Node* root, short int mov, int g_cost, int f_cost)
    : Node(cube, root, mov), g_cost(g_cost), f_cost(f_cost) {}