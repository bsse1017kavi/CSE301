#include<bits/stdc++.h>
using namespace std;

int V,E;

struct subset
{
	int parent;
	int rank;
};

struct edge
{
	int src;
	int dst;
};

subset *s;
edge *edges;

int find(int i)
{
	if(s[i].parent!=i)
	{
		s[i].parent = find(s[i].parent);
	}
	
	return s[i].parent;
}

void uni(int x,int y)
{
	int xRoot = find(x);
	int yRoot = find(y);
	
	if(s[xRoot].rank > s[yRoot].rank)
	{
		s[yRoot].parent = s[xRoot].parent;
	}
	
	else if(s[xRoot].rank < s[yRoot].rank)
	{
		s[xRoot].parent = s[yRoot].parent;
	}
	
	else
	{
		s[yRoot].parent = s[xRoot].parent;
		s[xRoot].rank++;
	}
}

void make_comp()
{
	for(int i=0;i<E;i++)
	{
		edge next_edge = edges[i];
		
		int x = find(next_edge.src);
		int y = find(next_edge.dst);
		
		if(x!=y)
		{
			uni(x,y);
		}
	}
}

int main(void)
{
	int c = 0;	
	
	cin >> V >> E;
	
	s = new subset[V];
	edges = new edge[E];
	int *cnt = new int [V];
	
	for(int i=0;i<V;i++)
	{
		s[i].parent = i;
		s[i].rank = 0;
		cnt[i] = 0;
	}
	
	for(int i=0;i<E;i++)
	{
		cin >> edges[i].src >> edges[i].dst;
	}
	
	make_comp();
	
	/*for(int i=0;i<V;i++)
	{
		cnt[s[i].parent]++;
		//cout << s[i].parent << " ";
	}*/
	
	//cout << endl;
	
	for(int i=0;i<V;i++)
	{
		//if(cnt[i]>0) c++;
		if(i==find(i))c++;
	}
	
	cout << c << endl;
}
