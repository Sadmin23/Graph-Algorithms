#include <bits/stdc++.h>

using namespace std;

#define MAX 100000
#define INF 999

int dist[MAX];

struct edge
{
    int u;
    int v;
    int w;
};

typedef struct edge edge;

vector<edge> edgelist;

void init(int n)
{
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
}
void bellman_ford(int x, int n)
{
    init(n);

    dist[x] = 0;

    for (int i = 1; i <= n - 1; i++)
    {
        for (auto e : edgelist)
        {
            int a, b, c;

            a = e.u;
            b = e.v;
            c = e.w;

            dist[b] = min(dist[b], dist[a] + c);
        }
    }
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

    bellman_ford(1, n);

    for (int i = 1; i <= n; i++)
        printf("%d: %d\n", i, dist[i]);

    return 0;
}