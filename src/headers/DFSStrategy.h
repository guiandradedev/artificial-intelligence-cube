#pragma once

#include "AlgorithmStrategy.h"
#include "Node.h"        
#include "Hasher.h"           
#include <unordered_map>    
#include "Node.h"
#include "DataStructure.h"  

class DFSStrategy : public AlgorithmStrategy {
private:
    std::unordered_map<Cube, int> g_costs;  // Declare este membro

public:
    DFSStrategy();
    bool poda(Node *state) override;
    void sucessora(Node *current_state, short int moviment, DataStructure &structure, std::unordered_set<Cube> &visited) override;
};