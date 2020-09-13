from queue import Queue
G = {} # node: [(node, dis), (node, dis), (node, dis)]
d = []

def spfa(s):
    inq = [False for i in range(n)]
    num = [0 for i in range(n)]
    d = [float('inf') for i in range(n)]
    q = Queue()
    q.put(s)
    inq[s] = True
    num[s] += 1
    d[s] = 0
    while(q.empty() != True):
        u = q.get()
        inq[u] = False
        for j in range(len(G[u])):
            v = G[u][j][0]
            dis = G[u][j][1]

            # 松弛
            if d[u] + dis < d[v]:
                d[v] = d[u] + dis
                if inq[v] != True:
                    q.put(v)
                    inq[v] = True
                    num[v] += 1
                    if num[v] >= n:
                        return False
    return True, d

n, m = map(int, input().split())

for i in range(n):
    G[i] = []
for i in range(m):
    u, v, dis = map(int, input().strip().split())
    
    G[u - 1].append((v - 1, dis))
    G[v - 1].append((u - 1, dis))
print(spfa(0))