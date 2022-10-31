#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

vector<int> adj[N];
string color[N];
int pre[N];
int d[N];
int f[N];
int low[N];
int time;

void DFS_Visit(int u)
{
    color[u] = "GRAY";
    time = time + 1;
    d[u] = time;

    for (auto v : adj[u])
    {
        if (color[v] == "WHITE")
        {
            pre[v] = u;
            DFS_Visit(v);
        }
    }

    color[u] = "BLACK";
    time = time + 1;
    f[u] = time;
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

    time = 0;

    for (int u = 0; u < N; u++)
    {
        if (color == "WHITE")
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