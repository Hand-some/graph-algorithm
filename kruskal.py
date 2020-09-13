
E = [(0, 1, 4), (0, 4, 1), (0, 5, 2), (1, 2, 1), (1, 5, 3), (2, 3, 6), (2, 5, 5), (3, 4, 5), (3, 5, 4), (4, 5, 3)] # (u, v, cost)
n = 6
m = 10

father = [i for i in range(0, n)]

def findFather(x):
    a = x
    while(x != father[x]):
        x = father[x]
    while(a!= father[a]):
        z = a
        a = father[a]
        father[z] = x
    return x

def kruskal(n, m):
    ans = 0
    num_edge = 0
    E.sort(key=lambda edge: edge[2])
    for i in range(m):
        faU = findFather(E[i][0])
        faV = findFather(E[i][1])
        if faU != faV:
            father[faU] = faV
            ans += E[i][2]
            num_edge += 1
            if num_edge == n - 1:
                break
    if num_edge != n - 1:
        return -1
    else:
        return ans

print(kruskal(n, m))