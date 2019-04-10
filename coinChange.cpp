#include<iostream>
using namespace std;

int n,m;

int *cost;

int **dp;

int c(int i,int am)
{
	if(i>=n)
	{
		if(am==m) return 1;
		else return 0;
	}
	
	if(dp[i][am]!=-1) return dp[i][am];
	
	int val1 = 0,val2 = 0;
	
	if(am+cost[i]<=m)
	{
		val1 = c(i,am+cost[i]);
	}
	
	val2 = c(i+1,am);
	
	return dp[i][am] = val1 + val2;
}

int main(void)
{
	cin >> n >> m;	
	
	cost = new int[n];
	
	for(int i=0;i<n;i++)
	{
		cin >> cost[i];
	}
	
	dp = new int*[n];
	for(int i=0;i<n;i++)
	{
		dp[i] = new int[m+1];
	}
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			dp[i][j] = -1;
		}
	}	
		
	cout << c(0,0) << endl;
	
	return 0;
}
