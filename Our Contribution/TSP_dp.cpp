#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ms(x,y) memset (x, y, sizeof (x))
#define INF 100000000
#define MAX 20
#define FOR(i,a,b) for (int i=(a); i<(b); i++)
#define FORr(i,a,b) for (int i=(a); i>=b; i--)

ll cost[MAX][MAX], memo[1<<MAX][MAX];
int n, m, u, v, w, lastpos;

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

ll call(int mask, int last)
{
    if(mask==((1<<n)-1)) 
    {
        // returning to the base
        return cost[last][0]; 
    }

    // memorization
    if(memo[mask][last]!=-1) return memo[mask][last]; 

    ll ret=INF;

    for(int i=0; i<n; i++)
    {
        if(!(mask & (1<<i)))
        {
            int newmask=(mask|(1<<i));
            int newlast=i;

            // calling next states
            ll out=cost[last][i]+call(newmask,newlast); 

            ret=min(ret,out);
        }
    }

    return memo[mask][last]=ret;
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

    FOR(i,0,m)
    {
        cin>>u>>v>>w;
        u--, v--; // ensuring 0 based indexing
        cost[u][v]=cost[v][u]=w;
    }

    FloydWarshall();

    FOR(i,0,n)
    {
        FOR(j,i+1,n)
        {
            cout<<i<<" "<<j<<" "<<cost[i][j]<<endl;
        }
    }

    ms(memo,-1); // clearing memory

    int mask=1, start_node=0;

    ll ans=call(mask,start_node);

    cout<<"Cost: "<<ans<<endl;

    return 0;
}