#include<bits/stdc++.h>
using namespace std;

int V,E;

struct edge
{
    int src;
    int dst;
    int w;
};

edge *adj;
int *d;

bool bellman_ford(int src)
{
    d[src] = 0;

    for(int i=0;i<V-1;i++)
    {
        for(int j=0;j<E;j++)
        {
            int u = adj[j].src;
            int v = adj[j].dst;
            int w = adj[j].w;

            if(d[v]>d[u]+w)
            {
                d[v] = d[u]+w;
            }
        }
    }

    for(int j=0;j<E;j++)
    {
        int u = adj[j].src;
        int v = adj[j].dst;
        int w = adj[j].w;

        if(d[v]!=INT_MAX && d[v]>d[u]+w)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    cin >> V >> E;

    adj = new edge[E];
    d = new int[V];

    for(int i=0;i<V;i++)
    {
        d[i] = INT_MAX;
    }

    for(int i=0;i<E;i++)
    {
        cin >> adj[i].src >> adj[i].dst >> adj[i].w;
    }

    cout << endl;

    if(bellman_ford(0))
    {
        for(int i=0;i<V;i++)
        {
            cout << i << " " << d[i] << endl;
        }
    }

    else cout << "Graph contains negative cycle" << endl;
}
