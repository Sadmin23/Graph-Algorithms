#include<bits/stdc++.h>
#include<chrono>

using namespace std;

#define MAX 100000

typedef pair<int, int> PII;

vector<PII> V[MAX];

int cost[MAX], taken[MAX], INF=INT_MAX;

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
	void MinHeapify(int );

	int parent(int i) { return (i-1)/2; }
	int left(int i) { return (2*i + 1); }
	int right(int i) { return (2*i + 2); }
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
    if(heap_size<= 0)
        return {-1,-1};
    if (heap_size==1){
        heap_size--;
        return harr[0];
    }
    edge root = harr[0];
    harr[0]=harr[heap_size-1];
    heap_size--;
    Heapify(0);
    return root;
}
void BinHeap::Heapify(int i){
    int  l = left(i);
    int  r = right(i);

    int smallest= i;
    if(l<heap_size && harr[l].cost<harr[i].cost ){
        smallest=l;
    }
    if(r<heap_size && harr[r].cost<harr[smallest].cost){
        smallest=r;
    }
    if(smallest!=i){
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
    while(i != 0 && harr[parent(i)].cost > harr[i].cost)
    {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}
bool BinHeap::isempty(){
    if(heap_size<=0)
        return true;
    else
        return false;
}
int Binary_Prim(int s)
{
    for (int i=0; i<MAX; i++)
    {
        cost[i]=INF;
        taken[i]=0;       
    }

    BinHeap h(MAX);

    edge xyz;   xyz.u=s;    xyz.cost=0;

    h.push(xyz);
    cost[s]=0;
    int ans=0;

    while(!h.isempty())
    {
        edge x=h.top();
        h.pop();
        
        if (taken[x.u])
            continue;
        taken[x.u]=1;

        ans+=x.cost;

        for (PII v: V[x.u])
        {
            if (!taken[v.first] && v.second<cost[v.first])
            {
                edge z; z.u=v.first;    z.cost=v.second;
                h.push(z);
                cost[v.first]=v.second;
            }
        }
    }

    return ans;
}
bool operator<(edge A, edge B){
    return A.cost>B.cost;
}
int STL_Prim(int s)
{
    for (int i=0; i<MAX; i++)
    {
        cost[i]=INF;
        taken[i]=0;       
    }

    priority_queue<edge> PQ;
    
    cost[s]=0;
    edge z; z.u=s;  z.cost=0;
    PQ.push(z);
    int ans=0;


    while (!PQ.empty())
    {
        edge x=PQ.top();
        PQ.pop();

        if (taken[x.u])
            continue;

        taken[x.u]=1;

        ans+=x.cost;

        for (PII v: V[x.u])
        {
            if (!taken[v.first] && v.second<cost[v.first])
            {
                edge z; z.u=v.first;    z.cost=v.second;
                PQ.push(z);
                cost[v.first]=v.second;
            }
        }
    }
    return ans;
}
void printArray(edge arr[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        cout << arr[i].u << " "<<arr[i].cost<<"\n"; 
    printf("--X--\n");
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
            if(arr[j].cost>=pivot.cost)
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
int Array_Prim(int s){

    for (int i=0; i<MAX; i++)
    {
        cost[i]=INF;
        taken[i]=0;       
    }
    edge arr[MAX];

    cost[s]=0;

    int csize=0;
    arr[csize].u=s;    arr[csize].cost=0;
    csize++;

    int ans=0;

    while (csize>0)
    {
        quickSort(arr,0,csize-1);

        //printArray(arr,csize);

        edge x=arr[csize-1];
        csize--;

        if (taken[x.u])
            continue;

        taken[x.u]=1;
        
        ans+=x.cost;

        for (PII v: V[x.u]){
            if (!taken[v.first] && v.second<cost[v.first]){
                edge z; z.u=v.first;    z.cost=v.second;
                arr[csize]=z;
                csize++;
                cost[v.first]=v.second;
            }
        }               
    }
    return ans;
}
int main()
{
    freopen("B.txt","r",stdin);    

    int n, m;   cin>>n>>m;

    int s;

    for (int i=0; i<m; i++)
    {
        int a,b,c;  cin>>a>>b>>c;

        if (i==0)
            s=a;

        V[a].push_back({b,c});
        V[b].push_back({a,c});
    }

    auto start = std::chrono::high_resolution_clock::now();
    cout<<"Binary Heap:\n"<<"cost: "<<Binary_Prim(s)<<"\n";
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n";
   
    start = std::chrono::high_resolution_clock::now(); 
    cout<<"STL Heap:\n"<<"cost: "<<STL_Prim(s)<<"\n";
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n"; 

    start = std::chrono::high_resolution_clock::now(); 
    cout<<"Array:\n"<<"cost: "<<Array_Prim(s)<<"\n";
    elapsed = std::chrono::high_resolution_clock::now() - start;
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    cout<<"time: "<<microseconds<<"\n\n"; 

	return 0;
}
