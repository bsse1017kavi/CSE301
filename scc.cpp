#include<iostream>
#include<vector>
#include<stack>
using namespace std;

int V,E;

enum COLOR{WHITE,GRAY,BLACK};

vector<int> *adj;
int *prev;
COLOR *color;
stack<int> topo;
int *d;
int *f;
int time = 0;

vector<vector<int> > components;

void dfsUtils(int u,vector<int> &items)
{
    color[u] = GRAY;
    time++;
    d[u] = time;
    items.push_back(u);

    for(vector<int>::iterator it = adj[u].begin();it!=adj[u].end();it++)
    {
        int v = (*it);
        if(color[v]==WHITE)
        {
            prev[v] = u;
            //items.push_back(v);
            dfsUtils(v,items);
        }
    }

    color[u] = BLACK;
    time++;
    f[u] = time;
    topo.push(u);
}

void dfs()
{
    vector<int> items;

    for(int i=0;i<V;i++)
    {
        if(color[i]==WHITE)
        {
            dfsUtils(i,items);
        }
    }

}

void transpose()
{
    vector<int> *trans = new vector<int>[V];
    for(int i=0;i<V;i++)
    {
        for(vector<int>::iterator it = adj[i].begin();it!=adj[i].end();it++)
        {
            int v = (*it);
            trans[v].push_back(i);
        }
    }

    adj = trans;

    for(int i=0;i<V;i++)
    {
        color[i] = WHITE;
        d[i] = 0;
        f[i] = 0;
        prev[i] = -1;
    }
}

int scc()
{
    transpose();
    int c = 0;

    while(!topo.empty())
    {
        int v = topo.top();
        topo.pop();

        if(color[v]==WHITE)
        {
            vector<int> items;
            dfsUtils(v,items);
            c++;
            components.push_back(items);
        }
    }

    return c;
}

int main(void)
{
    int v1,v2;

    cin >> V >> E;

    adj = new vector<int>[V];
    color = new COLOR[V];
    d = new int[V];
    f = new int[V];
    prev = new int[V];

    for(int i=0;i<V;i++)
    {
        color[i] = WHITE;
        d[i] = 0;
        f[i] = 0;
        prev[i] = -1;
    }

    for(int i=0;i<E;i++)
    {
        cin >> v1 >> v2;
        adj[v1].push_back(v2);
    }

    dfs();

    cout << endl;

    cout << scc() << endl;

    cout << endl;

    for(vector<vector<int> >::iterator it = components.begin();it!=components.end();it++)
    {
        for(vector<int>::iterator it1 = (*it).begin();it1!=(*it).end();it1++)
        {
            cout << (*it1) << " ";
        }

        cout << endl;
    }

    return 0;
}
