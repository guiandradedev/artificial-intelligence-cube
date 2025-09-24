#include <unordered_set>    
#include "Strategies/AStarStrategy.h"
#include "Strategies/AlgorithmStrategy.h"
#include "DataStructure/DataStructure.h"  
#include "DataStructure/PriorityQueue.h"  
#include "Node/Node.h"
#include "Node/AstarNode.h"        
#include "Hasher.h"           

AStarStrategy::AStarStrategy()
{
}

bool AStarStrategy::poda(Node *current_state)
{
    if (AstarNode *stated_casted = dynamic_cast<AstarNode *>(current_state))
    {
        if (stated_casted->g_cost > g_costs[stated_casted->cube])
        {
            return true;
        }
        return false;
    }
    return false;
}

void AStarStrategy::sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited, std::vector<Node*>& all_nodes)
{
    if (AstarNode *stated_casted = dynamic_cast<AstarNode *>(current_state))
    {
        Cube next_cube = stated_casted->cube.applyMove(moviment);
        int new_g_cost = stated_casted->g_cost + 1;

        // só processa se nunca visitou ou achou custo melhor
        if (visited.find(next_cube) == visited.end() || new_g_cost < g_costs[next_cube])
        {
            g_costs[next_cube] = new_g_cost;
            visited.insert(next_cube);

            int h_cost = Hasher::get_distance(next_cube);
            int f_cost = new_g_cost + h_cost;

            AstarNode* node = new AstarNode{next_cube, stated_casted, moviment, new_g_cost, f_cost};

            all_nodes.push_back(node);

            structure.insert(node);
        }
    }
}

Node* AStarStrategy::create_root_node(Cube &cube) {
    int g_start = 0;
    int h_start = Hasher::get_distance(cube);
    if (h_start == -1)
    {
        std::cout << "erro" << std::endl;
        throw std::runtime_error("Invalid Hash");
    }

    g_costs[cube] = g_start;

    AstarNode *root = new AstarNode{cube, nullptr, -1, g_start, g_start + h_start};
    return root;
}
DataStructure* AStarStrategy::create_data_structure() {
    return new PriorityQueue();
}