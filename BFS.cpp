#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

vector<int> adj[N];
string color[N];
int pre[N];
int d[N];

void BFS(int s)
{
    for (int u = 0; u < N; u++)
    {
        color[u] = "WHITE";
        d[u] = INF;
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
void Print_path(int s, int v)
{
    if (v == s)
        printf("%d", s);
    else if (pre[v] == -1)
        printf("No Path\n");
    else
    {
        Print_path(s, pre[v]);
        printf("%d", v);
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