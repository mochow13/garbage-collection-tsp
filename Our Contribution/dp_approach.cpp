#include <bits/stdc++.h>

#define MAX 20
#define INF 1e8

using namespace std;

int n, m, u, v, c, g[MAX][MAX];
string a, b;
int cnt=0, d[MAX][MAX], deg[MAX];
map<string,int> mapped;
int dp[(1<<MAX)+2], path[(1<<MAX)+2];
vector<string> rev;
vector<int> graph[MAX];
bool gone[MAX][MAX];
int extra[MAX]; // to calculate extra travel

void floydWarshall()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<n; k++)
            {
                d[j][k]=min(d[j][k],d[j][i]+d[i][k]);
            }
        }
    }
}

int go(int mask)
{
    if(mask==(1<<n)-1) return 0;
    if(dp[mask]!=-1) return dp[mask];
 
    int ret=INF;
 
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(!(mask&(1<<i)) && !(mask&(1<<j)))
            {
                int out=d[i][j]+go(mask|(1<<i)|(1<<j));

                if(ret>out)
                {
                	ret=out;
                	path[mask]=(mask|(1<<i)|(1<<j));
                }
            }
        }
    }
 
    return dp[mask]=ret;
}

void generate_combination(int mask)
{
	if(mask==(1<<n)-1) return;

	int nxt=path[mask];

	vector<int> edge;

	for(int i=0; i<n; i++)
	{
		if((mask&(1<<i))!=(nxt&(1<<i)))
		{
			// cout<<i<<endl;
			edge.push_back(i);
		}
	}

	cout<<rev[edge[0]]<<"---"<<rev[edge[1]]<<endl;
	// cout<<edge[0]<<" "<<edge[1]<<endl;

	extra[edge[0]]=edge[1];
	extra[edge[1]]=edge[0];

	generate_combination(path[mask]);
}

int main()
{
	// freopen("in1.txt","r",stdin);
	// freopen("in2.txt","r",stdin);
	freopen("in3.txt","r",stdin);

	cin>>n>>m; // number of nodes and edges

	rev.resize(n); // to hold road point names

	cin.ignore();

	memset(d,63,sizeof(d)); // initializing distance array
	memset(dp,-1,sizeof(dp)); // initializing dp array

	int opt_cost=0;

	for(int i=0; i<m; i++)
	{
		getline(cin,a);
		getline(cin,b);

		// we map the names to integer values for the sake of simplicity

		if(mapped.find(a)==mapped.end())
		{
			mapped[a]=cnt;
			rev[cnt]=a;
			cnt++;
		}

		if(mapped.find(b)==mapped.end())
		{
			mapped[b]=cnt;
			rev[cnt]=b;
			cnt++;
		}

		int u=mapped[a], v=mapped[b];


		cin>>g[u][v]>>c; // number of grabage bins and cost

		opt_cost+=c;
		g[v][u]=g[u][v];
		d[u][v]=d[v][u]=c;
		deg[u]++; deg[v]++; // calculating degree of each node

		graph[u].push_back(v);
		graph[v].push_back(u);

		cin.ignore();
	}

	floydWarshall();

	int mask=0;

	for(int i=0; i<n; i++)
	{
		if(deg[i]%2==0) 
		{
			mask|=(1<<i);
			// cout<<i<<endl;
		}
	}

	int out=go(mask);

	cout<<out<<endl;
	cout<<"Optimal cost: "<<opt_cost<<endl;
	cout<<"Extra Travel Between Nodes:"<<endl;

	generate_combination(mask);

	return 0;
}