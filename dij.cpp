#include<bits/stdc++.h>
using namespace std;

#define INF INT_MAX
typedef pair<int,int> iPair;

int V,E;

vector<iPair> *adj;

vector<int> d;

void dij(int src)
{
	for(int i=0;i<V;i++)
	{
		d.push_back(INF);
	}
	
	priority_queue<iPair,vector<iPair>,greater<iPair> > pq;
	
	d[src] = 0;
	pq.push(make_pair(0,src));
	
	while(!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		
		for(int i=0;i<V;i++)
		{
			for(vector<iPair> :: iterator it=adj[u].begin();it!=adj[u].end();it++)
			{
				int v = (*it).first;
				int w = (*it).second;
				
				if(d[v]>d[u]+w)
				{
					d[v] = d[u]+w;
					pq.push(make_pair(d[v],v));
				}
			}
		}
	}
}

int main(void)
{
	int v1,v2,w;	
	
	cin >> V >> E;
	
	adj = new vector<iPair>[V];
	
	for(int i=0;i<E;i++)
	{
		cin >> v1 >> v2 >> w;
		adj[v1].push_back(make_pair(v2,w));
		adj[v2].push_back(make_pair(v1,w)); 
	}
	
	cout << endl;
	
	/*for(int i=0;i<V;i++)
	{
		for(vector<iPair> :: iterator it=adj[i].begin();it!=adj[i].end();it++)
		{
			cout << i << " " << (*it).first << " " << (*it).second << endl; 
		}
	}*/
	
	dij(0);
	
	for(int i=0;i<V;i++)
	{
		cout << i << " " << d[i] << endl;
	}
}
