#include<bits/stdc++.h>
using namespace std;
#define INF INT_MAX

typedef pair<int,int> iPair;

vector<iPair> *adj;

int *parent;
int *key;

int V, E;

void add_edge(int u,int v,int w)
{
    adj[u].push_back(make_pair(v,w));
    adj[v].push_back(make_pair(u,w));
}

void mst_prim()
{
    priority_queue<iPair, vector<iPair>, greater<iPair> > pq;
    bool intMst[V];

    for(int i=0;i<V;i++)
    {
        intMst[i] = false;
    }

    int src = 0;
    key[src] = 0;
    pq.push(make_pair(0,src));

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        intMst[u] = true;

        //cout << u << endl;

        /*for(int i=0;i<V;i++)
        {
            cout << key[i] << endl;
        }*/

        for(vector<iPair> :: iterator it = adj[u].begin();it!=adj[u].end();it++)
        {
             //cout << "shit" << endl;

            if(!intMst[(*it).first] && key[(*it).first]>(*it).second)
            {
                //cout << "shit" << endl;
                key[(*it).first] = (*it).second;
                parent[(*it).first] = u;
                pq.push(make_pair(key[(*it).first],(*it).first));
            }
        }

    }
}

void print_adj_list()
{
    cout << endl;

    for(int i=0;i<V;i++)
    {
        // u v w
        for(vector<iPair> :: iterator it = adj[i].begin();it!=adj[i].end();it++)
        {
            cout << i << " " << (*it).first << " " << (*it).second << endl;
        }
    }
}

int main(void)
{
    int v1,v2,w;

    cin >> V >> E;

    adj = new vector<iPair>[V];
    parent = new int[V];

    key = new int[V];

    for(int i=0;i<V;i++)
    {
        key[i] = INF;
    }

    for(int i=0;i<V;i++)
    {
        parent[i] = -1;
    }

    for(int i=0;i<E;i++)
    {
        cin >> v1 >> v2 >> w;

        add_edge(v1,v2,w);
    }

    //print_shit();

    mst_prim();

    cout << endl;

    for(int i=0;i<V;i++)
    {
        cout << i << " " << parent[i] << " " << key[i] << endl;
    }
}
