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
    if (DFSNode *stated_casted = dynamic_cast<DFSNode *>(current_state))
    {
        if (stated_casted->depth >= max_depth)
        {
            // stated_casted->cube.print();
            return true;
        }
        return false;
    }
    return false;
}

void DFSStrategy::sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited, std::vector<Node *> &all_nodes)
{
    if (DFSNode *stated_casted = dynamic_cast<DFSNode *>(current_state))
    {
        if (Move::isInverse(moviment, stated_casted->mov))
            return;

        // Impede 3 rotacoes iguais
        if (current_state->root && current_state->root->mov == moviment && current_state->mov == moviment)
            return;

        // Impede duas rotacoes anti horarias iguais em sequencia
        if (current_state->mov == moviment && (moviment == 1 || moviment == 3 || moviment == 5))
            return;

        Cube next_cube = stated_casted->cube.applyMove(moviment);

        // if (visited.find(next_cube) == visited.end())
        // {
            // std::cout << "Profundidade: " << stated_casted->depth + 1 << std::endl;

            DFSNode *next_node = new DFSNode{next_cube, stated_casted, moviment, stated_casted->depth + 1};

            all_nodes.push_back(next_node);

            structure.insert(next_node);
            visited.insert(next_cube);
        // }
    }
}

Node *DFSStrategy::create_root_node(Cube &cube)
{
    DFSNode *root = new DFSNode{cube, nullptr, -1, 0};
    return root;
}

DataStructure *DFSStrategy::create_data_structure()
{
    return new Stack();
}