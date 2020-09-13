G = {} # node: [(node, dis), (node, dis), (node, dis)]

def dijkstra(G, start):
    vis = [False for i in range(n)]
    d = [float('inf') for i in range(n)]
    d[start] = 0
    for i in range(n):
        u = -1
        mymin = float('inf')
        for j in range(n): # 找到未访问节点中d[]最小的d[u]
            if vis[j] == False and d[j] < mymin:
                u = j
                mymin = d[j]
        if u == -1:
            return
        vis[u] = True
        for j in range(len(G[u])):
            v = G[u][j][0]
            if vis[v] == False and d[u] + G[u][j][1] < d[v]:
                d[v] = d[u] + G[u][j][1]
    return d

# n - node num   m - edge num
n, m = map(int, input().split())

for i in range(n):
    G[i] = []
for i in range(m):
    u, v, dis = map(int, input().strip().split())
    
    G[u - 1].append((v - 1, dis))
    G[v - 1].append((u - 1, dis))
print(dijkstra(G, 0))