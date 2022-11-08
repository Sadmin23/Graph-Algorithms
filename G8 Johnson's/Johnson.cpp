#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

#define MAX 100
#define INF INT_MAX

int wei[MAX][MAX];
vector<PII> adj[MAX];

int dist[MAX];
int pre[MAX];
int flag[MAX];

int processed[MAX];
int dist2[MAX];

int sd[MAX][MAX];

priority_queue<PII> q;

struct edge
{
    int u;
    int v;
    int w;
};

vector<int> v;

typedef struct edge edge;

vector<edge> edgelist;

void init2()
{
    for (int i = 0; i < MAX; i++)
    {
        processed[i] = 0;
        dist2[i] = INF;
    }
}
void dijkstra(int x)
{
    init2();

    dist2[x] = 0;

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

            if (dist2[a] + w < dist2[b])
            {
                dist2[b] = dist2[a] + w;
                q.push({-dist2[b], b});
            }
        }
    }
}
void init(int s, int n)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        pre[i] = -1;
    }

    dist[s] = 0;
}
void relax(int u, int v, int w)
{
    if (dist[v] > dist[u] + w)
    {
        dist[v] = dist[u] + w;
        pre[v] = u;
    }
}
bool bellman_ford(int x, int n)
{
    init(x, n);

    for (int i = 0; i < n - 1; i++)
    {
        for (auto e : edgelist)
        {
            int a, b, c;

            a = e.u;
            b = e.v;
            c = e.w;

            relax(a, b, c);
        }
    }
    for (auto e : edgelist)
    {
        int a, b, c;

        a = e.u;
        b = e.v;
        c = e.w;

        if (dist[b] > dist[a] + c)
            return false;
    }

    return true;
}
void Johnson(int m)
{
    int n = v.size();

    for (int i = 0; i < v.size(); i++)
        edgelist.push_back({n, v[i], 0});

    if (!bellman_ford(0, v.size()))
    {
        cout << "Negative weight cycle\n";
        return;
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            edge e = edgelist[i];

            int a = e.u;
            int b = e.v;
            int c = e.w;

            wei[a][b] = wei[a][b] + dist[a] - dist[b];

            c = wei[a][b];

            adj[a].push_back({b, c});
        }
        for (int i = 0; i < n; i++)
        {
            dijkstra(i);

            for (int j = 0; j < n; j++)
                // printf("%d ", dist2[j]);
                printf("%d ", dist2[j]);

            puts("");
        }
    }
}
int main()
{
    freopen("K.txt", "r", stdin);

    int n, m;

    cin >> n >> m;

    memset(flag, 0, sizeof(flag));

    for (int i = 0; i < m; i++)
    {
        int x, y, z;

        cin >> x >> y >> z;

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

        wei[x][y] = z;

        edgelist.push_back({x, y, z});
    }

    Johnson(m);

    return 0;
}