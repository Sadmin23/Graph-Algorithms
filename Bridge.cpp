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
int flag[N];
int timing;

vector<pair<int, int>> bridge;

vector<int> v;

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

            if (low[w] > d[v])
                bridge.push_back({v, w});
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
    freopen("H.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;

        if (flag[x] == 0)
        {
            v.push_back(x);
            flag[x] = 1;
        }
        if (flag[y] == 0)
        {
            v.push_back(y);
            flag[y] = 1;
        }

        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    DFS();

    for (int i = 0; i < bridge.size(); i++)
        cout << bridge[i].first << " " << bridge[i].second << "\n";
}