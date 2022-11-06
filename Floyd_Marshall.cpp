#include <bits/stdc++.h>

using namespace std;

#define MAX 100
#define INF 999

int adj[MAX][MAX];
int dist[MAX][MAX];

void init()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (i == j)
                adj[i][j] = 0;
            else
                adj[i][j] = INF;
        }
    }
}
void floyd_warshall(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dist[i][j] = adj[i][j];
        }
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
    }
}
int main()
{
    freopen("B.txt", "r", stdin);

    init();

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;

        cin >> x >> y >> z;

        adj[x][y] = z;
        adj[y][x] = z;
    }
    floyd_warshall(n);

    printf("3->4: %d\n", dist[3][4]);

    return 0;
}