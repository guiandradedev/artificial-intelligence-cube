#pragma once

#include "Node/Node.h"

class AstarNode : public Node
{
public:
    int g_cost; // custo do caminho até aqui
    int f_cost; // custo total estimado (g + h)

    AstarNode();
    AstarNode(const Cube &cube, Node *root, short int mov, int g_cost, int f_cost);

    bool operator>(const AstarNode &other) const
    {
        return f_cost > other.f_cost;
    }
};