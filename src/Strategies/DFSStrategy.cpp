#include <unordered_set>    
#include "Strategies/DFSStrategy.h"
#include "Strategies/AlgorithmStrategy.h"
#include "DataStructure/DataStructure.h"  
#include "DataStructure/Stack.h"  
#include "Node/Node.h"
#include "Node/DFSNode.h"     
#include "Hasher.h"   
#include "Cube/Move.h"    

DFSStrategy::DFSStrategy()
{
}

bool DFSStrategy::poda(Node *current_state)
{
    // False: continua o loop
    // True: para o loop e vai pra proxima iteracao
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

Node* DFSStrategy::create_root_node(Cube &cube) {
    Node *root = new Node{cube, nullptr, -1};
    return root;
}

DataStructure* DFSStrategy::create_data_structure() {
    return new Stack();
}