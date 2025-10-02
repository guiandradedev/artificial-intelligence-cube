import subprocess
import re
import matplotlib.pyplot as plt
import os

project_root = os.path.abspath("..")

process = subprocess.Popen(
    ["./benchmark"],
    cwd=project_root,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE,
    text=True
)
stdout, stderr = process.communicate()

if stderr:
    print("Erros durante a execução do programa:")
    print(stderr)

print("Saída do programa:")
print("-" * 50)
print(stdout)
print("-" * 50)

shuffles = []
bfs_time = []
bfs_moves = []
bfs_states = []
dfs_time = []
dfs_moves = []
dfs_states = []
astar_time = []
astar_moves = []
astar_states = []

pattern = re.compile(
    r"^\s*(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)"
)

for line in stdout.splitlines():
    match = pattern.match(line)
    if match:
        idx = int(match.group(1))        # Index
        shf = int(match.group(2))        # Shuffles
        bfs_t = int(match.group(3))      # BFS Time
        bfs_m = int(match.group(4))      # BFS Moves
        bfs_s = int(match.group(5))      # BFS States
        dfs_t = int(match.group(6))      # DFS Time
        dfs_m = int(match.group(7))      # DFS Moves
        dfs_s = int(match.group(8))      # DFS States
        astar_t = int(match.group(9))    # A* Time
        astar_m = int(match.group(10))   # A* Moves
        astar_s = int(match.group(11))   # A* States

        shuffles.append(shf)
        bfs_time.append(bfs_t)
        bfs_moves.append(bfs_m)
        bfs_states.append(bfs_s)
        dfs_time.append(dfs_t)
        dfs_moves.append(dfs_m)
        dfs_states.append(dfs_s)
        astar_time.append(astar_t)
        astar_moves.append(astar_m)
        astar_states.append(astar_s)

print(f"Dados extraídos: {len(shuffles)} linhas processadas")

fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(18, 5))

# Tempo x Shuffles
ax1.plot(shuffles, bfs_time, marker='o', label='BFS Time (ms)', color='blue')
ax1.plot(shuffles, dfs_time, marker='s', label='DFS Time (ms)', color='red')
ax1.plot(shuffles, astar_time, marker='^', label='A* Time (ms)', color='green')
ax1.set_xlabel('Shuffles')
ax1.set_ylabel('Tempo (ms)')
ax1.set_title('Tempo x Shuffles')
ax1.set_yscale('log')
ax1.legend()
ax1.grid(True)

# Número de Movimentos x Shuffles
ax2.plot(shuffles, bfs_moves, marker='o', label='BFS N.Moves', color='blue')
ax2.plot(shuffles, dfs_moves, marker='s', label='DFS N.Moves', color='red')
ax2.plot(shuffles, astar_moves, marker='^', label='A* N.Moves', color='green')
ax2.set_xlabel('Shuffles')
ax2.set_ylabel('Número de Movimentos')
ax2.set_title('Movimentos x Shuffles')
ax2.legend()
ax2.grid(True)

# Estados x Shuffles
ax3.plot(shuffles, bfs_states, marker='o', label='BFS States', color='blue')
ax3.plot(shuffles, dfs_states, marker='s', label='DFS States', color='red')
ax3.plot(shuffles, astar_states, marker='^', label='A* States', color='green')
ax3.set_xlabel('Shuffles')
ax3.set_ylabel('Número de Estados')
ax3.set_title('Estados x Shuffles')
ax3.legend()
ax3.grid(True)

plt.tight_layout()
plt.savefig("resultado_graficos.png", dpi=300, bbox_inches='tight')
print("Gráfico salvo como 'resultado_graficos.png'")