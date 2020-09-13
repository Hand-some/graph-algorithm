def floyd():
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dis[i][k] != float('inf') and dis[k][j] != float('inf') and dis[i][k] + dis[k][j] < dis[i][j]:
                    dis[i][j] = dis[i][k] + dis[k][j]

