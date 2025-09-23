#ifndef ASTARNODE_H
#define ASTARNODE_H

#include "Node.h"
#include "Cube.h"

class AstarNode : public Node {
public:
    int g_cost; // custo do caminho até aqui
    int f_cost; // custo total estimado (g + h)

    AstarNode();
    AstarNode(const Cube& cube, Node* root, short int mov, int g_cost, int f_cost);

    // Para uso em priority_queue (menor f_cost tem prioridade)
    bool operator>(const AstarNode& other) const {
        return f_cost > other.f_cost;
    }
};
#endif