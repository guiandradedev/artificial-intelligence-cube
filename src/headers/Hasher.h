#ifndef HASHER_H
#define HASHER_H

#include <unordered_map>
#include <Cube.h>

namespace std {
    template<>
    struct hash<Cube> {
        size_t operator()(const Cube& c) const {
            size_t h = 0;
            for (int x = 0; x < 2; ++x) {
                for (int y = 0; y < 2; ++y) {
                    for (int z = 0; z < 2; ++z) {
                        const MiniCube& m = c.matrix[x][y][z];
                        // Usando o índice da peça para um hash mais estável
                        h ^= std::hash<int>{}(m.index) + 0x9e3779b9 + (h << 6) + (h >> 2);
                        h ^= std::hash<short>{}(m.orientation) + 0x9e3779b9 + (h << 6) + (h >> 2);
                    }
                }
            }
            return h;
        }
    };
}

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

#endif // HASHER_H