#include "AStarStrategy.h"
#include "AlgorithmStrategy.h"
#include "AstarNode.h"        
#include "Hasher.h"           
#include <unordered_set>    
#include "Node.h"
#include "DataStructure.h"  

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

void AStarStrategy::sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited)
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

            structure.insert(
                new AstarNode{next_cube, stated_casted, moviment, new_g_cost, f_cost});
        }
    }
}