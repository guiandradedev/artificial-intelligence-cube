#pragma once

#include "AlgorithmStrategy.h"
#include "AstarNode.h"        
#include "Hasher.h"           
#include <unordered_map>    
#include "Node.h"
#include "DataStructure.h"  

class AStarStrategy : public AlgorithmStrategy {
public:
    AStarStrategy();
    bool poda(Node *state) override;
    void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited) override;
    std::unordered_map<Cube, int> g_costs;  // Declare este membro
};