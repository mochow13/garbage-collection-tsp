#include <bits/stdc++.h>
#include <random>
#include <iostream>

using namespace std;

int main() {

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 20.0);

    int i=0;

    while(i<10)
    {
		int n, m;

		n=dist(mt);
		m=dist(mt);

		if(m>(n*(n+1))/2 || m<n-1) continue;

		cout<<n<<" "<<m<<" "<<endl;

		int j=0;

		while(true)
		{
			int u=i;
			int v=dist(mt);

			if(edges[make_pair(u,v)]) continue;

			

			cout<<u<<" "<<v<<endl;
		}

		i++;
	}
}