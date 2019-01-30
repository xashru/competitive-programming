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

vector< vector<int>> scc(vector<vector<int>> &graph) {
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
 	scc(graph);
	getchar();
	return 0;
}
