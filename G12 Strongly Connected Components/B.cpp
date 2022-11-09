#include <bits/stdc++.h>

using namespace std;

//freopen("inputa.txt","r",stdin);

struct node
{
    vector<int> adj[1005];
    string colour[1005];
    int pre[1005];
    int tme;
    int low[1005];
    int d[1005], f[1005];    
};
struct edgetype{
    int s,f;
    string type;
};
typedef struct edgetype edgetype;
vector<edgetype> edges;

int flag[1005]={0};vector<int> vertex;

struct order{
    int l, r;
};

typedef struct node node;
typedef struct order order;

order ssc[1005];

node a1,b1;

struct coll{
    int a, b;
};

typedef struct coll coll;

coll inp[100];

struct triple{
    int v, f, flag;
};

typedef struct triple triple;

vector<triple> xyz;

void transpose(int m){
    for (int i=0; i<m; i++){
        int x=inp[i].a;
        int y=inp[i].b;
        b1.adj[y].push_back(x);
    }
}
void dfs_visit(int u)
{
    a1.tme++;   a1.d[u]=a1.tme;
    a1.colour[u]="GRAY";
    a1.low[u]=a1.d[u];

    for (auto v:a1.adj[u])
    {
        if (a1.colour[v]=="WHITE")
        {
            edges.push_back({u,v,"Tree edge"});
            a1.pre[v]=u;
            dfs_visit(v);

            if (a1.low[v]<a1.low[u])
                a1.low[u]=a1.low[v];
        }
                else if (a1.colour[v]=="GRAY")
            edges.push_back({u,v,"Back edge"});
        if (a1.d[v]<a1.low[u])
            a1.low[u]=a1.d[v];
    }

    a1.colour[u]="BLACK";   a1.tme++;
    a1.f[u]=a1.tme;

}
void dfs()
{
    for (int i=0; i<vertex.size(); i++)
    {
        int u=vertex[i];    a1.colour[u]="WHITE";
        a1.d[u]=INT_MAX;    a1.f[u]=INT_MAX;
        a1.low[u]=INT_MAX;                
        a1.pre[u]=-1;
    }
    a1.tme=0;

    for (int i=0; i<vertex.size(); i++)
    {
        int u=vertex[i];

        if (a1.colour[u]=="WHITE")
            dfs_visit(u);
    }
}
bool comp(triple a, triple b)
{
    return a.f>b.f;
}
void dfs_visit2(int u)
{
    b1.tme++;   b1.d[u]=b1.tme;
    b1.colour[u]="GRAY";
    b1.low[u]=b1.d[u];

    for (auto v:b1.adj[u])
    {
        if (b1.colour[v]=="WHITE")
        {
            b1.pre[v]=u;
            dfs_visit2(v);

            if (b1.low[v]<b1.low[u])
                b1.low[u]=b1.low[v];
        }
        if (b1.d[v]<b1.low[u])
            b1.low[u]=b1.d[v];
    }

    b1.colour[u]="BLACK";   b1.tme++;
    b1.f[u]=b1.tme;

}
void dfs2()
{
    for (int i=0; i<xyz.size(); i++)
    {
        int u=xyz[i].v;    b1.colour[u]="WHITE";
        b1.d[u]=INT_MAX;    b1.f[u]=INT_MAX;
        b1.low[u]=INT_MAX;                
        b1.pre[u]=-1;
    }
    b1.tme=0;

    for (int i=0; i<xyz.size(); i++)
    {
        int u=xyz[i].v;

        if (b1.colour[u]=="WHITE")
            dfs_visit2(u);
    }
}
int main()
{
    freopen("inputb.txt","r",stdin);
    freopen("outputb.txt","w",stdout);    

    int n, m; cin>>n>>m;

    for (int i=0; i<m; i++)
    {
        int x, y;   cin>>x>>y;

        if (!flag[x])
        {
            vertex.push_back(x);
            flag[x]=1;
        }
        if (!flag[y])
        {
            vertex.push_back(y);
            flag[y]=1;
        }

        inp[i].a=x; inp[i].b=y;
        a1.adj[x].push_back(y);
    }

    dfs();

    for (int i=0; i<vertex.size(); i++){
        int u=vertex[i];
        xyz.push_back({u,a1.f[u],0});
    }

    sort(xyz.begin(),xyz.end(),comp);

    transpose(m);   dfs2();

    int u=vertex[0];

    ssc[0].l=b1.d[u];   ssc[0].r=b1.f[u];   int k=1;

    for (int i=1; i<vertex.size(); i++){
        u=vertex[i];    int x,y,p,q,flag;

        for (int j=0; j<k; j++){
            flag=0;
            x=ssc[j].l; y=ssc[j].r;
            p=b1.d[u]; q=b1.f[u];

            if (p<x && q>y){
                flag=1; ssc[j].l=p;
                ssc[j].r=q; break;
            }
            else if (p>x && q<y){
                flag=1; break;
            }
        }
        if (q<x || p>y && flag==0){
            ssc[k].l=p;
            ssc[k].r=q;
            k++;
        }
    }

    vector<int> components[k];

    for (int i=0; i<vertex.size(); i++){
        int u=vertex[i];
        for (int j=0; j<k; j++){
            if (b1.d[u]>=ssc[j].l && b1.f[u]<=ssc[j].r)
                components[j].push_back(u);
        }
    }
    for (int i=0; i<k; i++){
        printf("%d:", i+1);

        for (int j=0; j<components[i].size(); j++)
            printf(" %d", components[i][j]);

        puts("");
    }

    return 0;
}