#include<bits/stdc++.h>
using namespace std;

#define INF 9999

int V,E;

int **adj;

int **d;

void floyd_warshall()
{
    for(int k=0;k<V;k++)
    {
        for(int i=0;i<V;i++)
        {
            for(int j=0;j<V;j++)
            {
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
}

int main(void)
{
    int v1,v2,w;

    cin >> V >> E;

    adj = new int*[V];
    d = new int*[V];

    for(int i=0;i<V;i++)
    {
        adj[i] = new int[V];
        d[i] = new int[V];
    }

    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            if(i!=j)
            {
                adj[i][j] = INF;
                d[i][j] = INF;
            }

            else
            {
                adj[i][j] = 0;
                d[i][j] = 0;
            }
        }
    }

    for(int i=0;i<E;i++)
    {
        cin >> v1 >> v2 >> w;

        adj[v1][v2] = w;
        d[v1][v2] = w;
    }

    floyd_warshall();

    cout << endl;

    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            //cout << i << " " << j << " " << d[i][j] << endl;
            cout << d[i][j] << "\t\t";
        }

        cout << endl;
    }
}
