#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

#define inf -1
#define NIL -1

struct edge
{
    int fr,to,w;

    bool operator<(edge e) const
    {
        return w > e.w;
    }
};

int v,e;
edge *edges;
vector<int> *adj;

int *p;
int *key;

int **out;

priority_queue<edge> q;

void mst_prim(int s)
{
    int u;
    edge temp;

    key[s] = 0;

    while(!q.empty())
    {
        temp = q.top();
        q.pop();
        u = temp.fr;

        for(vector<int> :: iterator it = adj[u].begin();it!=adj[u].end();it++)
        {

        }
    }
}

int main(void)
{
    int w,e1,e2;

    cin >> v >> e;

    p = new int[v];
    key = new int[v];

    adj = new vector<int>[v];

    out = new int*[v];

    for(int i=0;i<v;i++)
        out[i] = new int[v];

    /*for(int i=0;i<v;i++)
        for(int j=0;j<v;j++)
            out[i][j]=0;*/

    memset(out,0,sizeof(out));

    edges = new edge[e];

    for(int i=0;i<v;i++)
    {
        p[i] = NIL;
        key[i] = inf;
    }

    for(int i=0;i<e;i++)
    {
        cin >> e1 >> e2 >> w;

        edges[i].fr = e1;
        edges[i].to = e2;
        edges[i].w = w;
        adj[e1].push_back(e2);
        q.push(edges[i]);
    }

    cout << endl;

    while(!q.empty())
    {
        cout << q.top().w << " ";
        q.pop();
    }

    cout << endl;
}
