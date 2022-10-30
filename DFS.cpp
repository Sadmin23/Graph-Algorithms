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

void DFS_Visit(int v)
{
    color[v] = "GRAY";
    time = time + 1;
    d[v] = time;
    low[v] = d[v];

    for (auto w : adj[v])
    {
        if (color[w] == "WHITE")
        {
            pre[w] = v;
            DFS_Visit(w);
            if (low[w] >= d[v])
                ; // record articulation point
            if (low[w] < low[v])
                low[v] = low[w];
        }
        else if (pre[v] != w)
        {
            if (d[w] < low[v])
                low[v] = d[w];
        }
    }

    color[v] = "BLACK";
    time++;
    f[v] = time;
}
void DFS()
{
    for (int u = 0; u < N; u++)
    {
        color[u] = "WHITE";
        pre[u] = -1;
        low[u] = INF;
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