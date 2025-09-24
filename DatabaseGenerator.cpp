#include <Cube/Cube.h>
#include <Cube/Move.h>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
#include <chrono>

// comando para compilar: g++ ./DatabaseGenerator.cpp ./src/Cube.cpp ./src/Move.cpp ./src/MiniCube.cpp -I ./src/headers/ -std=c++17 -o2 -o generate_db
// g++ ./DatabaseGenerator.cpp ./src/Cube/Cube.cpp ./src/Cube/Move.cpp ./src/Cube/MiniCube.cpp -I ./includes/ -std=c++17 -o2 -o generate_db
int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "Gerando banco de dados de distancias para o cubo 2x2..." << std::endl;

    std::unordered_map<Cube, short int> distance_map;

    std::queue<Cube> q;

    Cube solved_state;
    solved_state.init();

    distance_map[solved_state] = 0;
    q.push(solved_state);

    std::cout << "Iniciando busca em largura (BFS)..." << std::endl;
    int max_depth = 0;

    while (!q.empty())
    {
        Cube current_state = q.front();
        q.pop();

        short int current_dist = distance_map.at(current_state);

        if (current_dist > max_depth)
        {
            max_depth = current_dist;
            std::cout << "Alcancando profundidade " << max_depth << "..." << std::endl;
        }

        for (short int move_id = 0; move_id < 6; ++move_id)
        {
            Cube next_state = current_state.applyMove(move_id);

            if (distance_map.count(next_state) == 0)
            {
                distance_map[next_state] = current_dist + 1;
                q.push(next_state);
            }
        }
    }

    auto bfs_end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> bfs_duration = bfs_end_time - start_time;
    std::cout << "BFS reverso completo em " << bfs_duration.count() << " segundos." << std::endl;
    std::cout << distance_map.size() << " estados unicos encontrados." << std::endl;
    std::cout << "Salvando o banco de dados em 'hashing.bin'..." << std::endl;

    std::ofstream outfile("./src/hashing.bin", std::ios::binary);
    if (!outfile)
    {
        std::cerr << "ERRO: Nao foi possivel criar o arquivo hashing.bin." << std::endl;
        return 1;
    }

    size_t map_size = distance_map.size();
    outfile.write(reinterpret_cast<const char *>(&map_size), sizeof(map_size));

    for (const auto &pair : distance_map)
    {
        outfile.write(reinterpret_cast<const char *>(&pair.first), sizeof(Cube));
        outfile.write(reinterpret_cast<const char *>(&pair.second), sizeof(short int));
    }

    outfile.close();

    auto total_end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_duration = total_end_time - start_time;
    std::cout << "Arquivo 'hashing.bin' gerado com sucesso." << std::endl;
    std::cout << "Tempo total: " << total_duration.count() << " segundos." << std::endl;

    return 0;
}