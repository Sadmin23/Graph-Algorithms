#include <bits/stdc++.h>

using namespace std;

#define N 100

vector<int> adj[N];
string color[N];
int pre[N];
int d[N];

void BFS(int s)
{
    for (auto u : adj[s])
    {
        color[u] = "WHITE";
        d[u] = INT_MAX;
        pre[u] = -1;
    }

    color[s] = "GRAY";
    d[s] = 0;
    pre[s] = -1;

    queue<int> q;

    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto v : adj[u])
        {
            if (color[v] == "WHITE")
            {
                color[v] = "GRAY";
                d[v] = d[u] + 1;
                pre[v] = u;
                q.push(v);
            }
        }
        color[u] = "BLACK";
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