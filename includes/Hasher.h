#pragma once

#include <unordered_map>
#include "Cube/Cube.h"

class Hasher
{
private:
    static std::unordered_map<Cube, short int> distance_hash;

    static bool is_initialized;

public:
    Hasher() = delete;

    static void init(const std::string &filename);

    static short int get_distance(const Cube &cube);

    static size_t countStoredStates();
};