#include "AlgorithmStrategy.h"
#include "Node.h"
#include "Hasher.h"
#include <unordered_map>
#include "Node.h"
#include "DataStructure.h"
#include "DFSStrategy.h"
#include "Move.h"

DFSStrategy::DFSStrategy()
{
}

bool DFSStrategy::poda(Node *current_state)
{
    return false;
}

void DFSStrategy::sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited)
{
    if (Move::isInverse(moviment, current_state->mov))
        return;

    if (current_state->root && current_state->root->mov == moviment && current_state->mov == moviment)
        return;

    if (current_state->mov == moviment && (moviment == 1 || moviment == 3 || moviment == 5))
        return;

    Cube next_cube = current_state->cube.applyMove(moviment);

    if (visited.count(next_cube) == 0)
    {
        visited.insert(next_cube);

        Node *next_node = new Node{next_cube, current_state, moviment};

        structure.insert(next_node);
    }
}