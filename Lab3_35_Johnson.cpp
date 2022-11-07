#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
const int MAX = 999;

vector<PII> adj[MAX];

class edge
{
public:
    int u;
    int cost;
    edge()
    {
        this->u = 0;
        this->cost = 0;
    }
    edge(int x, int y)
    {
        this->u = x;
        this->cost = y;
    }
};
class Node1
{
public:
    edge data;
    Node1 *next;
    Node1(edge data)
    {
        this->data = data;
        this->next = NULL;
    }
};

void swap(int *x, int *y);

class BinHeap
{
    edge *harr;
    int capacity;
    int heap_size;

public:
    BinHeap(int capacity);
    void MinHeapify(int);

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i + 1); }
    int right(int i) { return (2 * i + 2); }
    edge top();
    edge pop();
    void Heapify(int i);
    void push(edge given);
    bool isempty();
    void swap(edge *x, edge *y)
    {
        edge temp = *x;
        *x = *y;
        *y = temp;
    }
};
BinHeap::BinHeap(int cap)
{
    this->capacity = cap;
    heap_size = 0;
    harr = new edge[cap];
}
edge BinHeap::top()
{
    return harr[0];
}
edge BinHeap::pop()
{
    if (heap_size <= 0)
        return {-1, -1};
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
    edge root = harr[0];
    harr[0] = harr[heap_size - 1];
    heap_size--;
    Heapify(0);
    return root;
}
void BinHeap::Heapify(int i)
{
    int l = left(i);
    int r = right(i);

    int smallest = i;
    if (l < heap_size && harr[l].cost < harr[i].cost)
    {
        smallest = l;
    }
    if (r < heap_size && harr[r].cost < harr[smallest].cost)
    {
        smallest = r;
    }
    if (smallest != i)
    {
        BinHeap::swap(&harr[i], &harr[smallest]);
        Heapify(smallest);
    }
}
void BinHeap::push(edge given)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    heap_size++;
    int i = heap_size - 1;
    harr[i] = given;
    while (i != 0 && harr[parent(i)].cost > harr[i].cost)
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}
bool BinHeap::isempty()
{
    if (heap_size <= 0)
        return true;
    else
        return false;
}

vector<int> Bellman_Ford(int &N, vector<vector<int>> edgelist)
{
    for (int i = 1; i <= N; i++)
    {
        edgelist.push_back({0, i, 0});
    }
    vector<int> d(N + 1, INT_MAX);
    d[0] = 0;
    while (true)
    {
        bool flag = false;
        for (auto e : edgelist)
        {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            if (d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                flag = true;
            }
        }
        if (!flag)
            break;
    }

    return d;
}
void Dijkstra(int x, vector<vector<int>> &path, int &N)
{
    BinHeap h(MAX);
    vector<int> visited(N + 1);

    path[x][x] = 0;

    h.push({0, x});

    while (!h.isempty())
    {
        int a = h.top().cost;
        h.pop();
        if (!visited[a])
        {
            visited[a] = true;
            for (auto u : adj[a])
            {
                int b = u.first;
                int w = u.second;
                if (path[x][a] + w < path[x][b])
                {
                    path[x][b] = path[x][a] + w;
                    h.push({-path[x][b], b});
                }
            }
        }
    }
}
signed main()
{
    freopen("K.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> edgelist;
    for (int i = 1; i <= M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edgelist.push_back({u, v, w});
    }
    vector<int> h = Bellman_Ford(N, edgelist);
    for (int i = 0; i < M; i++)
    {
        int u = edgelist[i][0];
        int v = edgelist[i][1];
        edgelist[i][2] += (h[u] - h[v]);
    }

    vector<vector<int>> path(N + 1, vector<int>(N + 1, INT_MAX));

    for (auto e : edgelist)
        adj[e[0]].push_back({e[1], e[2]});

    for (int i = 1; i <= N; i++)
        Dijkstra(i, path, N);

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (path[i][j] == INT_MAX)
                cout << -1 << " ";
            else
                cout << path[i][j] - (h[i] - h[j]) << " ";
        }
        cout << "\n";
    }
    return 0;
}
