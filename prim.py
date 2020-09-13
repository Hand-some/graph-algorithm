G = {} # node: [(node, dis), (node, dis), (node, dis)]

def prim():
    d = [float('inf' for i in range(n))]
    d[0] = 0
    ans = 0 # 最小生成数边权和
    for i in range(n):
        u = -1
        mymin = float('inf')
        for j in range(n):
            if vis[j] == False and d[j] < mymin:
                u = j
                mymin = d[j]
        if u == -1:
            return -1
        vis[u] = True
        ans += d[u]
        for j in range(len(G[u])):
            v = G[u][j][0]
            if vis[v] == False and G[u][j][1] < d[v]:
                d[v] = G[u][j][1]
    return ans