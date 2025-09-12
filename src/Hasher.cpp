#include <fstream>
#include "Hasher.h"
#include <iostream>

std::unordered_map<Cube, short int> Hasher::distance_hash;
bool Hasher::is_initialized = false;

void Hasher::init(const std::string &filename)
{
    if (is_initialized)
    {
        std::cout << "ja inicializado" << std::endl;

        return;
    }

    std::ifstream infile(filename, std::ios::binary);

    if (!infile)
    {
        std::cerr << "ERRO: Nao foi possivel abrir o arquivo de banco de dados '" << filename << "'." << std::endl;
        std::cerr << "      Voce precisa gerar o arquivo primeiro." << std::endl;
        return;
    }

    size_t map_size;

    infile.read(reinterpret_cast<char *>(&map_size), sizeof(map_size));

    distance_hash.clear();
    distance_hash.reserve(map_size);

    for (size_t i = 0; i < map_size; ++i)
    {
        Cube key;
        short int value;
        infile.read(reinterpret_cast<char *>(&key), sizeof(Cube));
        infile.read(reinterpret_cast<char *>(&value), sizeof(short int));
        distance_hash[key] = value;
    }

    is_initialized = true;
    std::cout << "Hasher inicializado. " << distance_hash.size() << " estados carregados do arquivo." << std::endl;
}

short int Hasher::get_distance(const Cube &cube)
{
    if (!is_initialized)
    {
        std::cerr << "ERRO: Hasher::getDistance() chamado antes de Hasher::init()." << std::endl;
        return -1;
    }

    auto it = distance_hash.find(cube);
    if (it != distance_hash.end())
    {
        // Encontrou o estado no mapa, retorna a distância (o valor)
        return it->second;
    }

    // Não encontrou o estado no mapa
    return -1;
}

size_t Hasher::countStoredStates()
{
    return distance_hash.size();
}