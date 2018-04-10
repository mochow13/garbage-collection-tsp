#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int, int> pii;
typedef vector<pair<int,int> > vpii;

#define MP make_pair
#define ms(x,y) memset (x, y, sizeof (x))
#define pb push_back
#define INF 1000000000000LL
#define MAX 100
#define debug cout<<"A"<<"\n"
#define prnt(a) cout<<a<<"\n"
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define FORr(i,a,b) for (int i=(a); i>=b; i--)
#define VecPrnt(v) FOR(J,0,v.size()) cout<<v[J]<<" "; cout<<endl
#define PrintPair(x) cout<<x.first<<" "<<x.second<<endl

struct info
{
	int u, v;
	double w;

	info(){}

	info(int u, int v, double w) : u(u), v(v), w(w) { }
};


vector<info> edges;
vector<int> graph[MAX];


class Approximation
{
	int parent[MAX];
	int n;
	double dist[MAX][MAX];

	void dfs(int u, int p)
	{
		preorder.pb(u);

		FOR(j,0,graph[u].size())
		{
			int v=graph[u][j];
			if(v==p) continue;

			dfs(v,u);
		}
	}

	static bool comp(info &a, info &b)
	{
		return a.w<b.w;
	}

	double distance(pii a, pii b)
	{
		ll ret=(a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
		return sqrt((double)ret);
	}

	void calcDistance(vpii &all)
	{
		FOR(i,0,all.size()-1)
		{
			FOR(j,i+1,all.size())
			{
				double d=distance(all[i],all[j]);
				edges.pb(info(i,j,d));
				dist[i][j]=dist[j][i]=d;
			}
		}
	}

	int find(int r)
	{
		if(parent[r]==r) return r;
		return parent[r]=find(parent[r]);
	}

	double Kruskal()
	{
		sort(edges.begin(),edges.end(),comp);

		int cnt=0;

		FOR(i,0,(int)edges.size())
		{
			int u=find(edges[i].u);
			int v=find(edges[i].v);

			if(u!=v)
			{
				parent[u]=v;
				cnt++;

				graph[edges[i].u].pb(edges[i].v);
				graph[edges[i].v].pb(edges[i].u);

				if(cnt==n-1) break;
			}
		}
	}

public:

	vector<int> preorder;

	double Walk()
	{
		double tour=0;
		dfs(0,-1);
		preorder.pb(0);

		FOR(i,0,preorder.size()-1)
		{
			tour+=dist[preorder[i]][preorder[i+1]];
		}

		return tour;
	}


	Approximation(int cities)
	{
		FOR(i,0,cities)
		{
			parent[i]=i;
			edges.clear();
		}
		n=cities;
		preorder.clear();
	}

	double getAnswer(vpii &all)
	{
		calcDistance(all);
		Kruskal();
		return Walk();
	}
};


int main()
{
	int n;
	vector<pii> Points;

    cin>>n;

    Points.resize(n);

    FOR(i,0,n)
    {
    	cin>>Points[i].first>>Points[i].second;
    }

    Approximation tsp(n);
    cout<<"Approximate cost: "; prnt(tsp.getAnswer(Points));
    cout<<"Path:"<<endl;

    // VecPrnt(tsp.preorder);

    FOR(i,0,tsp.preorder.size())
    {
    	cout<<Points[tsp.preorder[i]].first<<" "<<Points[tsp.preorder[i]].second<<endl;
    }

    return 0;
}

