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

bool dfs_cycle(vector<vector<int>> *graph, vector<bool> *vis, vector<bool> *rec, int u,bool *cycle) {
	(*rec)[u]=true;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*cycle)) return true;
		if((*graph)[u][i]==0 || (*vis)[i]) continue;
		if((*rec)[i]) {
			(*cycle)=true;
			return true;
		}
		dfs_cycle(graph,vis,rec,i,cycle);
	}
	(*vis)[u]=true;
	(*rec)[u]=false;
	return false;
}

bool isCyclic(vector<vector<int>> graph) {
	vector<bool> vis, rec; // visited and recursion stack
	int n=graph.size();
	for(int i=0; i<n; i++) {
		vis.push_back(false);
		rec.push_back(false);
	}
	bool cycle=false;
	for(int i=0; i<n; i++) {
		if(!vis[i] && dfs_cycle(&graph, &vis, &rec, i,&cycle)) return true;
	}
	return false;
}

int main() {
	vvi graph {
		{0, 0, 0, 1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 1, 0, 1, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	cout<<isCyclic(graph);
	getchar();
	return 0;
}
