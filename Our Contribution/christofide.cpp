#include <bits/stdc++.h>
using namespace std;

typedef vector <int> vi;

#define ll long long
#define MAX 100
#define INF 1e7
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define FORr(i,a,b) for (int i=(a); i>=b; i--)
#define pb push_back
#define VecPrnt(v) FOR(J,0,v.size()) cout<<v[J]<<" "; cout<<endl

int n, m, cost[MAX][MAX], prv[MAX];
bool visited[MAX];
ll d[MAX];
vi mst[MAX];

void FloydWarshall()
{
    FOR(i,0,n)
    {
        FOR(j,0,n)
        {
            FOR(k,0,n)
            {
                cost[j][k]=min(cost[j][k],cost[j][i]+cost[i][k]);
            }
        }
    }
}

int minKey()
{
	ll mini=INF;
	int minidx;
	for (int i=0; i<n; i++)
	{
		if (!visited[i] && d[i]<mini)
			mini=d[i], minidx=i;
	}
	return minidx;
}

ll Prim()
{
	FOR(i,0,n)
	{
		d[i]=INF;
		visited[i]=false;
		prv[i]=-1;
	}
	d[0]=0;
	
}

int main()
{
	// Nodes are indexed from 0
	// Truck at node 0

	cin>>n>>m; 

	// Initializing costs
	FOR(i,0,n)
	{
	    FOR(j,0,n)
	    {
	        if(i==j) cost[i][j]=0;
	        else cost[i][j]=INF;
	    }
	}

	int u, v, w;

	FOR(i,0,m)
	{
	    cin>>u>>v>>w;
	    u--, v--; // ensuring 0 based indexing
	    cost[u][v]=cost[v][u]=w;
	}

	FloydWarshall();
	Prim();



	return 0;
}