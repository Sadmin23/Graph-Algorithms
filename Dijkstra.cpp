#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

#define MAX 100000
#define INF 999

vector<PII> adj[MAX];

int processed[MAX];
int dist[MAX];
int pre[MAX];

priority_queue<PII> q;

void init()
{
    for (int i = 0; i < MAX; i++)
    {
        processed[i] = 0;
        dist[i] = INF;
        pre[i] = -1;
    }
}
void dijkstra(int x)
{
    init();

    dist[x] = 0;

    q.push({0, x});

    while (!q.empty())
    {
        int a = q.top().second;
        q.pop();

        if (processed[a])
            continue;

        processed[a] = 1;

        for (auto u : adj[a])
        {
            int b = u.first, w = u.second;

            if (dist[a] + w < dist[b])
            {
                dist[b] = dist[a] + w;
                q.push({-dist[b], b});
            }
        }
    }
}
int main()
{
    freopen("B.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;

        adj[x].push_back({y, z});
        adj[y].push_back({x, z});
    }

    dijkstra(1);

    for (int i = 1; i <= n; i++)
        printf("%d: %d\n", i, dist[i]);

    dijkstra(2);

    for (int i = 1; i <= n; i++)
        printf("%d: %d\n", i, dist[i]);

    return 0;
}