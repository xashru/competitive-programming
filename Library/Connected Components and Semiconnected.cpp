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

void dfs_scc(vector<vector<int>> *graph, stack<int> *s, vector<bool> *vis, int u) {
	(*vis)[u]=true;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*graph)[u][i]==0 || (*vis)[i]) continue;
		dfs_scc(graph, s, vis, i);
	}
	(*s).push(u);
}

vector< vector<int>> scc(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis;
	stack<int> s;
	for(int i=0; i<n; i++) vis.push_back(false);
	vector<vector<int>> graphT;  //transpose graph
	for(int i=0; i<n; i++) {
		vector<int> tmp;
		for(int j=0; j<n; j++) {
			tmp.push_back(graph[j][i]);
		}
		graphT.push_back(tmp);
	}

	for(int i=0; i<n; i++) {
		if(!vis[i]) dfs_scc(&graph, &s, &vis, i);
	}

	for(int i=0; i<n; i++) vis[i]=false;
	vector<vector<int>> V;
	while(!s.empty()) {
		int top=s.top();
		s.pop();
		if(vis[top]) continue;
		stack<int> ss;
		dfs_scc(&graphT, &ss, &vis, top);
		vector<int> tmp;
		while(!ss.empty()) {
			int top=ss.top();
			ss.pop();
			tmp.push_back(top);
		}
		V.push_back(tmp);
	}
	return V;
}

bool isConnected(vector<vector<int>> graph, vector<int> v1, vector<int> v2) {
	for(int i=0; i<v1.size(); i++) {
		for(int j=0; j<v2.size(); j++) {
			if(graph[v1[i]][v2[j]]!=0) return true;
		}
	}
	return false;
}

void dfs_topo(vector<vector<int>> *graph, vector<bool> *vis, stack<int> *s, int u) {
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*vis)[i] || (*graph)[u][i]==0) continue;
		dfs_topo(graph, vis, s, i);
	}
	(*vis)[u]=true;
	(*s).push(u);
}

vector<int> toposort(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis;
	stack<int> s;
	for(int i=0; i<n; i++) vis.push_back(false);
	for(int i=0; i<n; i++) {
		if(vis[i]) continue;
		dfs_topo(&graph, &vis, &s, i);
	}
	vector<int> res;
	while(!s.empty()) {
		int top=s.top();
		s.pop();
		res.push_back(top);
	}
	re res;
}

bool isSemiconnected(vector<vector<int>> graph) {
	vector<vector<int>> v=scc(graph);
	int n=v.size();
	if(n==1) return true; // the whole graph is strongly connected so obviouslt its semiconnected
	vector<vector<int>> compoGraph; //component graph
	for(int i=0; i<n; i++) {
		vector<int> tmp;
		for(int j=0; j<n; j++) {
			if(i!=j && isConnected(graph, v[i], v[j])) tmp.push_back(1);
			else tmp.push_back(0);
		}
		compoGraph.push_back(tmp);
	}
	vector<int> topo=toposort(compoGraph);
	for(int i=0; i<topo.size()-1; i++) {
		if(compoGraph[topo[i]][topo[i+1]]==0) return false;
	}
	return true;
}

int main() {
	vvi graph {
		{0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 1, 0},
		{0, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 0, 0, 1, 0}
	};
	cout<<isSemiconnected(graph);
	getchar();
	return 0;
}
