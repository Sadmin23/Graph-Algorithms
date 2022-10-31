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
int timing;

vector<int> arti_pt;

void DFS_Visit(int v)
{
    color[v] = "GRAY";
    timing = timing + 1;
    d[v] = timing;
    low[v] = d[v];

    for (auto w : adj[v])
    {
        if (color[w] == "WHITE")
        {
            pre[w] = v;
            DFS_Visit(w);

            if (low[w] >= d[v])
                arti_pt.push_back(v);
            if (low[w] < low[v])
                low[v] = low[w];
        }
    }

    color[v] = "BLACK";
    timing = timing + 1;
    f[v] = timing;
}
void DFS()
{
    for (int u = 0; u < N; u++)
    {
        color[u] = "WHITE";
        pre[u] = -1;
        f[u] = INF;
        d[u] = INF;
        low[u] = INF;
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