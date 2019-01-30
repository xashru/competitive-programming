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

void dfs_ap(vector<vector<int>> *graph, vector<bool> *vis, vector<int> *disc, vector<int> *low,
	vector<int> *parent, vector<bool> *ap, int u, int *time) {
	(*time)=(*time)+1;
	int children=0;
	(*vis)[u]=true;
	(*disc)[u]=(*low)[u]=*time;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*graph)[u][i]!=0 && !(*vis)[i]) {
			children++;
			(*parent)[i]=u;
			dfs_ap(graph, vis, disc, low, parent, ap, i, time);
			(*low)[u]=min((*low)[u], (*low)[i]);
			if((*parent)[u]==-1 && children >1) (*ap)[u]=true;
			if((*parent)[u]!=-1 && (*low)[i]>=(*disc)[u]) (*ap)[u]=true;
		} else if((*graph)[u][i]!=0 && i!=(*parent)[u]) (*low)[u]=min((*low)[u], (*disc)[i]);
	}
}

vector<bool> articulationPoints(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis, ap;
	vector<int> disc, low, parent;
	for(int i=0; i<n; i++) {
		vis.push_back(false);
		ap.push_back(false);
		disc.push_back(0);
		low.push_back(0);
		parent.push_back(-1);
	}
	int time=0;
	for(int i=0; i<n; i++) {
		if(!vis[i]) dfs_ap(&graph, &vis, &disc, &low, &parent, &ap, i, &time);
	}
	return ap;
}

void dfs_bridge(vector<vector<int>> *graph, vector<bool> *vis, vector<int> *disc, vector<int> *low,
	vector<int> *parent, vector<vector<int>> *bridge, int u, int *time) {
	(*vis)[u]=true;
	(*time)=(*time)+1;
	(*disc)[u]=(*low)[u]=*time;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*graph)[u][i]!=0 && !(*vis)[i]) {
			(*parent)[i]=u;
			dfs_bridge(graph, vis, disc, low, parent, bridge, i, time);
			(*low)[u]=min((*low)[u], (*low)[i]);
			if((*low)[i]>(*disc)[u]) (*bridge).push_back({u, i});
		} else if((*graph)[u][i]!=0 && i!=(*parent)[u]) (*low)[u]=min((*low)[u], (*disc)[i]);
	}
}

vector<vector<int>> bridges(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis;
	vector<int> disc, low, parent;
	vector<vector<int>>bridges;
	for(int i=0; i<n; i++) {
		vis.push_back(false);
		disc.push_back(0);
		low.push_back(0);
		parent.push_back(-1);
	}
	int time=0;
	for(int i=0; i<n; i++) {
		if(!vis[i]) dfs_bridge(&graph, &vis, &disc, &low, &parent, &bridges, i, &time);
	}
	for(int i=0; i<bridges.size(); i++) {
		cout<<bridges[i][0]<<" "<<bridges[i][1]<<endl;
	}
	return bridges;
}

struct edge{
	int u, v;
};

void dfs_bicon(vector<vector<int>> *graph, vector<bool> *vis, vector<int> *disc, vector<int> *low,
	vector<int> *parent, stack<edge> *edgeStack, vector<vector<edge>> *bicon, int u, int *time) {
	(*time)=(*time)+1;
	(*vis)[u]=true;
	(*disc)[u]=(*low)[u]=*time;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*graph)[u][i]!=0 && !(*vis)[i]) {
			(*parent)[i]=u;
			(*edgeStack).push({u, i});
			dfs_bicon(graph, vis, disc, low, parent, edgeStack, bicon, i, time);
			(*low)[u]=min((*low)[u], (*low)[i]);
			if((*low)[i]>=(*disc)[u]) {
				vector<edge> V;
				while(true) {
					edge top=(*edgeStack).top();
					(*edgeStack).pop();
					V.push_back(top);
					if(top.u==u && top.v==i) break;
				}
				(*bicon).push_back(V);
			}
		} else if((*graph)[u][i]!=0 && i!=(*parent)[u] && (*disc)[u]>(*disc)[i]) {
			(*edgeStack).push({u, i});
			(*low)[u]=min((*low)[u], (*disc)[i]);
		}
	}
}

vector<vector<edge>> biconnectedComponents(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis;
	vector<int> disc, low, parent;
	stack<edge> edgeStack;
	vector<vector<edge>> bicon;
	for(int i=0; i<n; i++) {
		vis.push_back(false);
		disc.push_back(0);
		low.push_back(0);
		parent.push_back(-1);
	}
	int time=0;
	for(int i=0; i<n; i++) {
		if(!vis[i]) dfs_bicon(&graph, &vis, &disc, &low, &parent, &edgeStack, &bicon, i, &time);
	}
	return bicon;
}

int main() {
	vector<vector<int>> graph {
		{0, 1, 1, 0, 0, 0, 0, 0},
		{1, 0, 1, 0, 1, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 1, 1},
		{0, 1, 0, 1, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 0, 0, 1},
		{0, 0, 0, 1, 0, 0, 1, 0},
	};
	print(articulationPoints(graph));
	biconnectedComponents(graph);
	bridges(graph);
	getchar();
	return 0;
}
