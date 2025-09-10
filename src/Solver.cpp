#include "Solver.h"
#include "Cube.h"
#include <queue>
#include <stack>
#include "Move.h"
#include <set>
#include <iostream>
#include <unordered_set>
#include <chrono>
#include <cstring>
#include "DataStructure.h"
#include "Queue.h"
#include "Stack.h"
#include <thread>
#include <atomic>
#include <vector>
#include "ThreadSafeQueue.cpp"
#include "ThreadSafeSet.cpp"
#include <barrier>

using namespace std::chrono;
namespace std
{
    template <>
    struct hash<Cube>
    {
        size_t operator()(const Cube &c) const
        {
            size_t h = 0;
            for (int x = 0; x < 2; ++x)
            {
                for (int y = 0; y < 2; ++y)
                {
                    for (int z = 0; z < 2; ++z)
                    {
                        const MiniCube &m = c.matrix[x][y][z];
                        h ^= std::hash<int>{}(m.left) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<int>{}(m.right) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<int>{}(m.mid) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<short>{}(m.orientation) + 0x9e3779b9 + (h << 6) + (h >> 2);
                    }
                }
            }
            return h;
        }
    };
}

using namespace std;

// Todo:
// Implement visited hash

Solver::Solver()
{
    final_state.init();
}

void Solver::algorithm(Cube cube, DataStructure &structure)
{
    unordered_set<Cube> visited;
    auto start = high_resolution_clock::now();
    int i = 0;

    Node *root = new Node{cube, nullptr, -1};
    Node *final_move;
    structure.insert(root);
    visited.insert(root->cube);

    while (!structure.isEmpty())
    {
        Node *state = structure.remove();

        if (state->cube == final_state)
        {
            cout << "Solucao encontrada na " << i << " iteracao!" << endl;
            final_move = state;
            break;
        }

        for (const auto &moviment : cube.moviments)
        {
            // if(strcmp(Move::reverse_moves(moviment), state->mov) == 0) continue;

            // std::cout << "Movimento: " << moviment << " na iteracao " << i << endl;

            // Se for inverso do anterior, pula pro proximo
            if (Move::isInverse(moviment, state->mov))
                continue;

            if (state->root && state->root->mov == moviment && state->mov == moviment)
                continue;

            if (state->mov == moviment && (moviment == 1 || moviment == 3 || moviment == 5))
                continue;

            Cube next_cube = state->cube.applyMove(moviment);

            if (visited.count(next_cube) == 0)
            {
                visited.insert(next_cube);

                Node *next_node = new Node{next_cube, state, moviment};

                structure.insert(next_node);
            }
        }
        i++;
    }
    auto end = high_resolution_clock::now();
    cout << "Tempo BFS: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    cout << "Reconstrucao do cubo:" << endl;
    int moves = 0;
    while (final_move->root != nullptr)
    {
        cout << moviments_name[final_move->mov] << endl;
        final_move = final_move->root;
        moves++;
    }

    cout << "Com um total de " << moves << " movimentos." << endl;
}

void Solver::bfs(Cube cube)
{
    Queue queue_structure;
    cout << "Iniciando BFS..." << endl;
    algorithm(cube, queue_structure);
}

void Solver::dfs(Cube cube)
{
    Stack stack_structure;
    cout << "Iniciando DFS..." << endl;
    algorithm(cube, stack_structure);
}

void Solver::algorithm_parallel(const Cube &cube)
{
    ThreadSafeVector<NodePtr> node_pool;
    // ThreadSafeVector<NodePtr> next_level;
    ThreadSafeSet<Cube> visited;
    std::vector<NodePtr> current_level;

    std::atomic<bool> found = false;
    std::atomic<size_t> work_index = 0;

    NodePtr root = std::make_shared<Node2>(Node2{cube, WeakNodePtr(), -1});

    
    NodePtr final_node = nullptr;
    std::mutex final_node_mutex;
    
    visited.insert(root->cube);
    current_level.push_back(root);
    node_pool.push_back(root);
    
    unsigned int num_threads = std::thread::hardware_concurrency() + 1;
    std::vector<std::vector<NodePtr>> next_level_main_storage(num_threads);
    
    std::barrier sync_point(num_threads + 1);
    
    auto worker_function = [&](size_t thread_id)
    {
        std::vector<NodePtr>& local_next_level = next_level_main_storage[thread_id];

        while (true)
        {
            sync_point.arrive_and_wait();
            
            if (found || current_level.empty())
            break;
            
            while (!found)
            {
                size_t index = work_index.fetch_add(1);
                
                if (index >= current_level.size())
                break;
                
                NodePtr state = current_level[index];
                
                if (state->cube == final_state)
                {
                    std::cout << "Solução encontrada!" << std::endl;
                    std::lock_guard<std::mutex> lock(final_node_mutex);
                    if (!found.load())
                    {
                        final_node = state; // Armazena o nó final encontrado
                        found = true;       // Marca que a solução foi encontrada
                    }
                }
                
                for (const auto &moviment : cube.moviments)
                {
                    if (found)
                    break; // Se já encontrou a solução, não continua
                    
                    if (Move::isInverse(moviment, state->mov))
                    continue;
                    
                    if (auto parent = state->root.lock())
                    {
                        if (parent->mov == moviment && state->mov == moviment)
                        continue;
                    }
                    
                    if (state->mov == moviment && (moviment == 1 || moviment == 3 || moviment == 5))
                    continue;
                    
                    Cube next_cube = state->cube.applyMove(moviment);
                    
                    if (visited.insert(next_cube))
                    {
                        NodePtr next_node = std::make_shared<Node2>(Node2{next_cube, state, moviment});
                        node_pool.push_back(next_node);
                        local_next_level.push_back(next_node);
                    }
                }
            }

            sync_point.arrive_and_wait();
        }
    };
    
    std::vector<std::thread> threads_workers;
    
    for (unsigned int i = 0; i < num_threads; i++)
    {
        threads_workers.emplace_back(worker_function, i);
    }
    
    auto start = high_resolution_clock::now();
    int level = 0;

    
    while (!found && !current_level.empty())
    {
        work_index = 0;

        for (auto& vector : next_level_main_storage)
        {
            vector.clear();
        }
        
        sync_point.arrive_and_wait();
        sync_point.arrive_and_wait();
        
        std::vector<NodePtr> new_current_level;
        for (const auto& local_vector : next_level_main_storage)
        {
            new_current_level.insert(new_current_level.end(), local_vector.begin(), local_vector.end());
        }

        current_level = std::move(new_current_level);

        std::cout << "Nível " << level++ << std::endl;
    }

    std::cout << "Finalizou os níveis." << std::endl;

    if (!found)
        found = true; // Para sair dos threads se não encontrou

    sync_point.arrive_and_wait(); // Garante que todos os threads terminaram

    for (auto &thread : threads_workers)
    {
        thread.join();
    }

    auto end = high_resolution_clock::now();
    cout << "Tempo paralelo: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;

    if (final_node)
    {
        int moves = 0;
        NodePtr current = final_node;
        while (const auto &parent = current->root.lock())
        {
            cout << moviments_name[current->mov] << endl;
            current = parent;
            moves++;
        }
        cout << "Com um total de " << moves << " movimentos." << endl;
    }
}