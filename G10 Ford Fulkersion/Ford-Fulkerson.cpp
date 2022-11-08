#include <bits/stdc++.h>

using namespace std;

#define N 100
#define INF INT_MAX

int cap[N][N];
vector<int> adj[N];
int pre[N];

void init()
{
    for (int i = 0; i < N; i++)
    {
        pre[i] = -1;

        for (int j = 0; j < N; j++)
        {
            cap[i][j] = 0;
        }
    }
}
int bfs(int s, int t)
{
    for (int i = 0; i < N; i++)
        pre[i] = -1;

    pre[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty())
    {
        int cur = q.front().first;
        int flo = q.front().second;
        q.pop();

        for (auto v : adj[cur])
        {
            if (pre[v] == -1 && cap[cur][v])
            {
                pre[v] = cur;

                int flo2 = min(flo, cap[cur][v]);

                if (v == t)
                    return flo2;
                q.push({v, flo2});
            }
        }
    }

    return 0;
}
int maxflow(int s, int t)
{
    int flow = 0;
    int flow2;

    while (flow2 = bfs(s, t))
    {
        // cout << flow2 << "\n";

        flow += flow2;
        int cur = t;

        while (cur != s)
        {
            int previous = pre[cur];
            cap[previous][cur] -= flow2;
            cap[cur][previous] += flow2;
            cur = previous;
        }
    }

    return flow;
}
int main()
{
    init();

    freopen("I.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        adj[x].push_back(y);
        adj[y].push_back(x);
        cap[x][y] = z;
    }

    cout << maxflow(0, n - 1) << "\n";

    return 0;
}