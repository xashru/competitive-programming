#include <cctype>
#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <ratio>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <valarray>

using namespace std;

#define sz(v) v.size()
#define pb(x) push_back(x)
#define eps 1e-10
#define re return
#define sum(v) accumulate(v.begin(),v.end(),0)
#define asrt(v) sort(v.begin(),v.end())
#define dsrt(v) sort(v.rbegin(),v.rend())
#define rev(v) reverse(v.begin(),v.end())
#define pi 3.1415926535897932384626433832795
#define print(v) for (auto& i:v) cout<<i<<endl 

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<string> vs;
typedef vector<vector<int>> vvi;


int findFlow(vector<vector<int>> *graph, int s, int t) {
	int INF=99999999;
	int n=(*graph).size();
	vector<int> par, vis;
	for(int i=0; i<n; i++) {
		par.push_back(-1);
		vis.push_back(0);
	}
	queue<int> q;
	q.push(s);
	bool f=false;
	while(!q.empty()) {
		int top=q.front();
		q.pop();
		if(top==t) {
			f=true;
			break;
		}
		for(int i=0; i<n; i++) {
			if((*graph)[top][i]>0 && !vis[i]) {
				q.push(i);
				par[i]=top;
				vis[i]=1;
			}
		}
	}
	if(!f) return 0;
	int to=t;
	int cap=INF;
	while(to!=s) {
		int from=par[to];
		cap=min(cap, (*graph)[from][to]);
		to=from;
	}
	to=t;
	while(to!=s) {
		int from=par[to];
		(*graph)[from][to]-=cap;
		(*graph)[to][from]+=cap;
		to=from;
	}
	return cap;
}

int maxFlow(vector<vector<int>> graph, int s, int t) {
	int flow=0;
	while(true) {
	int x=findFlow(&graph, s, t);
		if(x==0) break;
		flow+=x;
	}
	return flow;
}


int main() {
	vector<vector<int>> graph {
		{0, 16, 0, 13, 0, 0},
		{0, 0, 12, 0, 0, 0},
		{0, 0, 0, 9, 0, 20},
		{0, 4, 0, 0, 14, 0},
		{0, 0, 7, 0, 0, 4},
		{0, 0, 0, 0, 0, 0},
	};
	cout<<maxFlow(graph,0,5)<<endl;
	getchar();
	return 0;
}
