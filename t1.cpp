#include<bits/stdc++.h>
using namespace std;

struct g
{
	int p;
	int q;
};

int compare(const void * a, const void * b) 
{ 
    return ( *(int*)a < *(int*)b ); 
}

int comp(g a,g b)
{
	if(a.q!=b.q)return a.q < b.q;
	else
	{
		return a.p < b.p;
	}
} 

int main(void)
{
	int n;
	cin >> n;
	
	g *a = new g[n];
	
	for(int i=0;i<n;i++)
	{
		cin >> a[i].p >> a[i].q;
	}
	
	//qsort(a,n,sizeof(a[0]),compare);
	
	sort(a,a+n,comp);
	
	cout << endl;
	
	for(int i=0;i<n;i++)
	{
		cout << a[i].p << " " << a[i].q;
		cout << endl;
	}
	
	
	return 0;
}
