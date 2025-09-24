#include <unordered_set>    
#include "Strategies/BFSStrategy.h"
#include "Strategies/AlgorithmStrategy.h"
#include "DataStructure/DataStructure.h"  
#include "DataStructure/Queue.h"  
#include "Node/Node.h"
#include "Node/AstarNode.h"        
#include "Hasher.h"   
#include "Cube/Move.h"    

BFSStrategy::BFSStrategy()
{
}

bool BFSStrategy::poda(Node *current_state)
{
    return false;
}

void BFSStrategy::sucessora(Node *current_state, short moviment, DataStructure &structure, std::unordered_set<Cube> &visited)
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

Node* BFSStrategy::create_root_node(Cube &cube) {
    Node *root = new Node{cube, nullptr, -1};
    return root;
}
DataStructure* BFSStrategy::create_data_structure() {
    return new Queue();
}