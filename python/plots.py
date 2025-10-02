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

# Novo padrão regex para capturar todas as colunas incluindo número de movimentos
pattern = re.compile(
    r"^\s*(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)\s+(\d+)ms\s+(\d+)\s+(\d+)"
)

for line in stdout.splitlines():
    match = pattern.match(line)
    if match:
        idx = int(match.group(1))        # Index
        shf = int(match.group(2))        # Shuffles
        bfs_t = int(match.group(3))      # BFS Time
        bfs_m = int(match.group(4))      # BFS N.Moves
        bfs_s = int(match.group(5))      # BFS States
        dfs_t = int(match.group(6))      # DFS Time
        dfs_m = int(match.group(7))      # DFS N.Moves
        dfs_s = int(match.group(8))      # DFS States
        astar_t = int(match.group(9))    # A* Time
        astar_m = int(match.group(10))   # A* N.Moves
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

# Criando 3 subplots para visualizar tempo, movimentos e estados
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(18, 5))

# Subplot 1 - Tempo vs Shuffles
ax1.plot(shuffles, bfs_time, marker='o', label='BFS Time (ms)', color='blue')
ax1.plot(shuffles, dfs_time, marker='s', label='DFS Time (ms)', color='red')
ax1.plot(shuffles, astar_time, marker='^', label='A* Time (ms)', color='green')
ax1.set_xlabel('Shuffles')
ax1.set_ylabel('Tempo (ms)')
ax1.set_title('Tempo vs Shuffles')
ax1.legend()
ax1.grid(True)

# Subplot 2 - Número de Movimentos vs Shuffles
ax2.plot(shuffles, bfs_moves, marker='o', label='BFS N.Moves', color='blue')
ax2.plot(shuffles, dfs_moves, marker='s', label='DFS N.Moves', color='red')
ax2.plot(shuffles, astar_moves, marker='^', label='A* N.Moves', color='green')
ax2.set_xlabel('Shuffles')
ax2.set_ylabel('Número de Movimentos')
ax2.set_title('Movimentos vs Shuffles')
ax2.legend()
ax2.grid(True)

# Subplot 3 - Estados vs Shuffles
ax3.plot(shuffles, bfs_states, marker='o', label='BFS States', color='blue')
ax3.plot(shuffles, dfs_states, marker='s', label='DFS States', color='red')
ax3.plot(shuffles, astar_states, marker='^', label='A* States', color='green')
ax3.set_xlabel('Shuffles')
ax3.set_ylabel('Número de Estados')
ax3.set_title('Estados vs Shuffles')
ax3.legend()
ax3.grid(True)

plt.tight_layout()
plt.savefig("resultado_graficos.png", dpi=300, bbox_inches='tight')
print("Gráfico salvo como 'resultado_graficos.png'")

# Criando um segundo gráfico com subplot 2x2 para análises mais detalhadas
fig2, ((ax4, ax5), (ax6, ax7)) = plt.subplots(2, 2, figsize=(14, 10))

# Comparação de eficiência: Estados vs Movimentos
ax4.scatter(bfs_moves, bfs_states, label='BFS', color='blue', alpha=0.7)
ax4.scatter(dfs_moves, dfs_states, label='DFS', color='red', alpha=0.7)
ax4.scatter(astar_moves, astar_states, label='A*', color='green', alpha=0.7)
ax4.set_xlabel('Número de Movimentos')
ax4.set_ylabel('Estados Visitados')
ax4.set_title('Eficiência: Estados vs Movimentos')
ax4.legend()
ax4.grid(True)

# Tempo vs Estados
ax5.scatter(bfs_states, bfs_time, label='BFS', color='blue', alpha=0.7)
ax5.scatter(dfs_states, dfs_time, label='DFS', color='red', alpha=0.7)
ax5.scatter(astar_states, astar_time, label='A*', color='green', alpha=0.7)
ax5.set_xlabel('Estados Visitados')
ax5.set_ylabel('Tempo (ms)')
ax5.set_title('Tempo vs Estados Visitados')
ax5.legend()
ax5.grid(True)

# Comparação da qualidade das soluções (menos movimentos = melhor)
ax6.bar([x-0.2 for x in shuffles], bfs_moves, width=0.2, label='BFS', color='blue', alpha=0.7)
ax6.bar([x for x in shuffles], dfs_moves, width=0.2, label='DFS', color='red', alpha=0.7)
ax6.bar([x+0.2 for x in shuffles], astar_moves, width=0.2, label='A*', color='green', alpha=0.7)
ax6.set_xlabel('Shuffles')
ax6.set_ylabel('Número de Movimentos')
ax6.set_title('Qualidade da Solução (Menos é Melhor)')
ax6.legend()
ax6.grid(True)

# Eficiência temporal (menos tempo = melhor)
ax7.bar([x-0.2 for x in shuffles], bfs_time, width=0.2, label='BFS', color='blue', alpha=0.7)
ax7.bar([x for x in shuffles], dfs_time, width=0.2, label='DFS', color='red', alpha=0.7)
ax7.bar([x+0.2 for x in shuffles], astar_time, width=0.2, label='A*', color='green', alpha=0.7)
ax7.set_xlabel('Shuffles')
ax7.set_ylabel('Tempo (ms)')
ax7.set_title('Eficiência Temporal (Menos é Melhor)')
ax7.legend()
ax7.grid(True)

plt.tight_layout()
plt.savefig("analise_detalhada.png", dpi=300, bbox_inches='tight')
print("Análise detalhada salva como 'analise_detalhada.png'")