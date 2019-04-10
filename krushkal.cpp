#include<bits/stdc++.h>
using namespace std;

int V,E;

struct edge
{
    int src;
    int dst;
    int w;
};

struct subset
{
    int parent;
    int rank;
};

edge *edges, *result;

int fin(subset *s,int i)
{
    if(s[i].parent != i)
    {
        s[i].parent = fin(s,s[i].parent);
    }

    return s[i].parent;
}

void uni(subset *s,int x,int y)
{
    int xRoot = fin(s,x);
    int yRoot = fin(s,y);

    if(s[xRoot].rank>s[yRoot].rank)
    {
        s[yRoot].parent = xRoot;
    }

    else if(s[xRoot].rank<s[yRoot].rank)
    {
        s[xRoot].parent = yRoot;
    }

    else
    {
        s[yRoot].parent = xRoot;
        s[xRoot].rank++;
    }
    
}

int comp(edge a,edge b)
{
    return a.w < b.w;
}

void krushkal()
{
    int i =0;
    int e =0;

    sort(edges,edges+E,comp);

    subset *s = new subset[V];

    for(int i=0;i<V;i++)
    {
        s[i].rank = 0;
        s[i].parent = i;
    }


    while(e < V-1)
    {
        edge new_edge = edges[i++];

        int x = fin(s,new_edge.src);
        int y = fin(s,new_edge.dst);

        //cout << new_edge.src << " " << new_edge.dst << " " << x << " " << y <<  endl;

        if(x!=y)
        {
            result[e++] = new_edge;
            uni(s,x,y);
        }

    }

}

void print_result()
{
    cout << endl;

    for(int i=0;i<V-1;i++)
    {
        cout << result[i].src << " " << result[i].dst << " " << result[i].w << endl;
    }
}


int main(void)
{
    cin >> V >> E;

    edges = new edge[E];
    result = new edge[V];

    for(int i=0;i<E;i++)
    {
        cin >> edges[i].src >> edges[i].dst >> edges[i].w;
    }

    cout << endl;


    krushkal();

    print_result();
}
