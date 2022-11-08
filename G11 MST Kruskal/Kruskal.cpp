#include <bits/stdc++.h>

using namespace std;

#define MAX 100000

int parent1[MAX];
int rank1[MAX];

class edge
{
    public:
        int u;
        int v;
        int w;
        edge()
        {
            u=0;
            v=0;
            w=0;
        }
        edge(int x, int y, int z)
        {
            u=x;
            v=y;
            w=z;
        }
};
class Node
{
public:
	edge data;
	Node *next;
	Node(edge data)
	{
		this->data = data;
		this->next = NULL;
	}
};

vector<edge> edgelist;
edge edgearr[MAX];

bool cmp(edge a, edge b)
{
    return a.w<b.w;
}
void Init1()
{
    for (int i=0; i<MAX; i++)
        parent1[i]=-1;
}
int find1(int x)
{
    if (parent1[x]==-1)
        return x;
    return find1(parent1[x]);
}
void unite1(int a, int b)
{
    int x=find1(a);
    int y=find1(b);

    if (x!=y)
        parent1[x]=y;
}
int NaiveDSU()
{
    Init1();

    sort(edgelist.begin(),edgelist.end(),cmp);

    int ans=0;

    for (auto xyz:edgelist)
    {
        int w=xyz.w;
        int x=xyz.u;
        int y=xyz.v;

        if (find1(x)!=find1(y))
        {
            unite1(x,y);
            ans+=w;
        }
    }
    return ans;
}
int find2(int x)
{
    if (parent1[x]==-1)
        return x;
    return parent1[x]=find2(parent1[x]);
}
void unite2(int a, int b)
{
    int x=find2(a);
    int y=find2(b);

    if (x!=y)
        parent1[x]=y;
}
int DSU_pathcomp()
{
    Init1();

    sort(edgelist.begin(),edgelist.end(),cmp);

    int ans=0;

    for (auto xyz:edgelist)
    {
        int w=xyz.w;
        int x=xyz.u;
        int y=xyz.v;

        if (find2(x)!=find2(y))
        {
            unite2(x,y);
            ans+=w;
        }
    }
    return ans;
}
void Init2()
{
    for (int i=0; i<MAX; i++)
    {
        parent1[i]=-1;
        rank1[i]=1;
    }
}
int find3(int x)
{
    if (parent1[x]==-1)
        return x;
    return find3(parent1[x]);
}
void unite3(int a, int b)
{
    int x=find3(a);
    int y=find3(b);

    if (x!=y)
    {
        if (rank1[x]<rank1[y])
        {
            parent1[x]=y;
            rank1[y]+=rank1[x];
        }
        else
        {
            parent1[y]=x;
            rank1[x]+=rank1[y];
        }
    }
}
int DSU_unionrank()
{
    Init2();

    sort(edgelist.begin(),edgelist.end(),cmp);

    int ans=0;

    for (auto xyz:edgelist)
    {
        int w=xyz.w;
        int x=xyz.u;
        int y=xyz.v;

        if (find3(x)!=find3(y))
        {
            unite3(x,y);
            ans+=w;
        }
    }
    return ans;
}
void swap(edge *x, edge *y)
{
        edge t = *x;
        *x = *y;
        *y = t;
}
int partition(edge arr[], int low, int high)
{
        edge pivot = arr[high];
        int i=low-1;
        for (int j=low; j<=high-1; j++)
        {
            if(arr[j].w<pivot.w)
            {
                i++;
                swap(&arr[i],&arr[j]);
            }
        }
        swap(&arr[i+1],&arr[high]);
        return (i+1);
}
void quickSort(edge arr[], int low, int high)
{
    if (low<high)
    {
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}
int NaiveDSU2(int m)
{
    Init1();

    quickSort(edgearr,0,m-1);

    int ans=0;

    for (auto xyz:edgelist)
    {
        int w=xyz.w;
        int x=xyz.u;
        int y=xyz.v;

        if (find1(x)!=find1(y))
        {
            unite1(x,y);
            ans+=w;
        }
    }
    return ans;
}
int DSU_pathcomp2(int m)
{
    Init1();

    quickSort(edgearr,0,m-1);

    int ans=0;

    for (auto xyz:edgelist)
    {
        int w=xyz.w;
        int x=xyz.u;
        int y=xyz.v;

        if (find2(x)!=find2(y))
        {
            unite2(x,y);
            ans+=w;
        }
    }
    return ans;
}
int DSU_unionrank2(int m)
{
    Init2();

    quickSort(edgearr,0,m-1);

    int ans=0;

    for (auto xyz:edgelist)
    {
        int w=xyz.w;
        int x=xyz.u;
        int y=xyz.v;

        if (find3(x)!=find3(y))
        {
            unite3(x,y);
            ans+=w;
        }
    }
    return ans;
}
int main()
{
    freopen("B.txt","r",stdin);

    int n, m;   cin>>n>>m;

    for (int i=0; i<m; i++)
    {
        int a,b,c;  cin>>a>>b>>c;

        edgelist.push_back({a,b,c});
        edgearr[i].u=a;
        edgearr[i].v=b;
        edgearr[i].w=c;       
    }
    cout<<"DSU STL:\n";
    auto start = std::chrono::high_resolution_clock::now();
    cout<<"cost: "<<NaiveDSU()<<"\n";
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n";

    cout<<"DSU Path Compression STL:\n";
    start = std::chrono::high_resolution_clock::now();
    cout<<"cost:"<<DSU_pathcomp()<<"\n";
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n";
 
    cout<<"DSU Union Rank STL:\n";    
    start = std::chrono::high_resolution_clock::now();
    cout<<"cost:"<<DSU_unionrank()<<"\n";
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n";

    cout<<"DSU Array:\n";
    start = std::chrono::high_resolution_clock::now();
    cout<<"cost:"<<NaiveDSU2(m)<<"\n"; 
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n";

    cout<<"DSU Path Compression Array:\n";
    start = std::chrono::high_resolution_clock::now();
    cout<<"cost:"<<DSU_pathcomp2(m)<<"\n";
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n";

    cout<<"DSU Union Rank Array:\n";
    start = std::chrono::high_resolution_clock::now();
    cout<<"cost:"<<DSU_unionrank2(m)<<"\n";
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n";
    

    return 0;
}
