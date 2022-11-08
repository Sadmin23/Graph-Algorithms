#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
typedef pair<PII, int> PI2;
typedef pair<int, PII> PI3;

#define MAX 100
#define INF INT_MAX

int movex[4] = {1, -1, 0, 0};
int movey[4] = {0, 0, 1, -1};

int matrix[3][3];
vector<PI2> adj[MAX][MAX];

int processed[MAX][MAX];
int dist[MAX][MAX];
int pre[MAX][MAX];

priority_queue<PI3> q;

void init()
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            processed[i][j] = 0;
            dist[i][j] = INF;
            pre[i][j] = -1;
        }
    }
}
void dijkstra(int x, int y)
{
    init();

    dist[x][y] = 0;

    q.push({0, {x, y}});

    while (!q.empty())
    {
        int a1 = q.top().second.first;
        int a2 = q.top().second.second;

        q.pop();

        if (processed[a1][a2])
            continue;

        processed[a1][a2] = 1;

        for (auto u : adj[a1][a2])
        {
            int b1 = u.first.first;
            int b2 = u.first.second;

            int w = u.second;

            if (dist[a1][a2] + w < dist[b1][b2])
            {
                dist[b1][b2] = dist[a1][a2] + w;
                q.push({-dist[b1][b2], {b1, b2}});
            }
        }
    }
}
bool check(int x, int y, int n)
{
    if (x >= 0 && x < n && y >= 0 && y < n)
        return true;
    return false;
}
int main()
{
    freopen("L.txt", "r", stdin);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int a;
            cin >> a;
            matrix[i][j] = a;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int x = i + movex[k];
                int y = j + movey[k];

                if (check(x, y, 3))
                {
                    int w = abs(matrix[i][j] - matrix[x][y]);

                    adj[i][j].push_back({{x, y}, w});

                    // cout << i << "," << j << " -> " << x << "," << y << " = " << w << "\n";
                }
            }
        }
    }

    dijkstra(0, 0);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << dist[i][j] << " ";

        puts("");
    }

    return 0;
}