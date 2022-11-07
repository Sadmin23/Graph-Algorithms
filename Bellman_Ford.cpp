#include <bits/stdc++.h>

using namespace std;

#define MAX 100
#define INF INT_MAX

int dist[MAX];
int pre[MAX];

struct edge
{
    int u;
    int v;
    int w;
};

typedef struct edge edge;

vector<edge> edgelist;

void init(int s, int n)
{
    for (int i = 1; i <= n; i++)
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

    for (int i = 1; i <= n - 1; i++)
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
int main()
{
    freopen("A.txt", "r", stdin);

    int n, m;

    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, z;

        cin >> x >> y >> z;

        edgelist.push_back({x, y, z});
        edgelist.push_back({y, x, z});
    }

    if (bellman_ford(1, n))
    {
        for (int i = 1; i <= n; i++)
            printf("%d: %d\n", i, dist[i]);
    }

    return 0;
}