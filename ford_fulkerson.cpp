#include<bits/stdc++.h>
using namespace std;

int V,E;

bool bfs(int **rGraph,int s,int t,int *parent)
{
    bool visited[V];
    memset(visited,0,sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v=0;v<V;v++)
        {
            if(!visited[v] && rGraph[u][v])
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];

}

int ford_fulkerson(int **graph,int s,int t)
{
    int u,v;
    int* parent = new int[V];

    for(int i=0;i<V;i++)
    {
        parent[i] = -1;
    }

    int** rGraph = new int*[V];
    for(int i=0;i<V;i++)
    {
        rGraph[i] = new int[V];
    }

    for(u=0;u<V;u++)
    {
        for(v=0;v<V;v++)
        {
            rGraph[u][v] = graph[u][v];
        }
    }

    int max_flow = 0;

    while(bfs(rGraph,s,t,parent))
    {
        int path_flow = INT_MAX;
        //finds bottleneck flow
        for(v=t;v!=s;v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow,rGraph[u][v]);
        }

        //updates residual graph with bottleneck flow
         for(v=t;v!=s;v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main(void)
{
    int v1,v2,w;

    cin >> V >> E;

    int **graph= new int*[V];
    for(int i=0;i<V;i++)
    {
        graph[i] = new int[V];
    }


    for(int i=0;i<V;i++)
    {
       for(int j=0;j<V;j++)
       {
           graph[i][j] = 0;
       }
    }


    for(int i=0;i<E;i++)
    {
        cin >> v1 >> v2 >> w;
        graph[v1][v2] = w;
    }

    cout << endl;
    cout << ford_fulkerson(graph,0,V-1) << endl;
}
