#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

vector<int> adj[N];
string color[N];
int pre[N];
int d[N];
int f[N];
int flag[N];
int timing;

vector<int> v;

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
    freopen("D.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    memset(flag, 0, sizeof(flag));

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

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " " << d[v[i]] << " " << f[v[i]] << "\n";
}