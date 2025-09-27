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

print("Leu arquivo")

if stderr:
    print("Erros durante a execução do programa:")
    print(stderr)

shuffles = []
bfs_time = []
bfs_states = []
dfs_time = []
dfs_states = []
astar_time = []
astar_states = []

pattern = re.compile(
    r"^\s*(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)ms\s+(\d+)"
)

for line in stdout.splitlines():
    match = pattern.match(line)
    if match:
        idx = int(match.group(1))
        shf = int(match.group(2))
        bfs_t = int(match.group(3))
        bfs_s = int(match.group(4))
        dfs_t = int(match.group(5))
        dfs_s = int(match.group(6))
        astar_t = int(match.group(7))
        astar_s = int(match.group(8))

        shuffles.append(shf)
        bfs_time.append(bfs_t)
        bfs_states.append(bfs_s)
        dfs_time.append(dfs_t)
        dfs_states.append(dfs_s)
        astar_time.append(astar_t)
        astar_states.append(astar_s)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

ax1.plot(shuffles, bfs_time, marker='o', label='BFS Time (ms)')
ax1.plot(shuffles, dfs_time, marker='o', label='DFS Time (ms)')
ax1.plot(shuffles, astar_time, marker='o', label='A* Time (ms)')
ax1.set_xlabel('Shuffles')
ax1.set_ylabel('Tempo (ms)')
ax1.set_title('Tempo vs Shuffles')
ax1.legend()
ax1.grid(True)

# Subplot 2 - Estados vs Shuffles
ax2.plot(shuffles, bfs_states, marker='o', label='BFS States')
ax2.plot(shuffles, dfs_states, marker='o', label='DFS States')
ax2.plot(shuffles, astar_states, marker='o', label='A* States')
ax2.set_xlabel('Shuffles')
ax2.set_ylabel('Número de Estados')
ax2.set_title('Estados vs Shuffles')
ax2.legend()
ax2.grid(True)

plt.tight_layout()
# plt.show()
plt.savefig("resultado_graficos.png")