#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

vector<int> adj[N];
string color[N];
int pre[N];
int d[N];
int f[N];
int timing;

void DFS_Visit(int u)
{
    color[u] = "GRAY";
    timing = timing + 1;
    d[u] = timing;

    for (auto v : adj[u])
    {
        if (color[v] == "WHITE")
        {
            pre[v] = u;
            DFS_Visit(v);
        }
    }

    color[u] = "BLACK";
    timing = timing + 1;
    f[u] = timing;
}
void DFS()
{
    for (int u = 0; u < N; u++)
    {
        color[u] = "WHITE";
        pre[u] = -1;
        f[u] = INF;
        d[u] = INF;
    }

    timing = 0;

    for (int u = 0; u < N; u++)
    {
        if (color[u] == "WHITE")
            DFS_Visit(u);
    }
}
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }
}