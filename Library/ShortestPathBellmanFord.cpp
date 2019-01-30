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

vector<int> bellmanFord(vector<vector<int>> graph, int s) {
	int INF=99999999;
	int nil=0;
	int n=graph.size();
	vector<int> dp;
	for(int i=0; i<n; i++) dp.push_back(i==s?0:INF);
	for(int k=0; k<n-1; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				if(graph[i][j]!=nil) {
					dp[j]=min(dp[j],dp[i]+graph[i][j]);
				}
			}
		}
	}
	bool f=false;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(graph[i][j]!=nil && dp[i]+graph[i][j]<dp[j]) {
				f=true;
			}
		}
	}

	return dp;
}

int main() {
	priority_queue<int> pq;
	vector<vector<int>> graph {
		{0, 6, 7, 0, 0},
		{0, 0, 8, 5, -4},
		{0, 0, 0, -3, 9},
		{0, -2, 0, 0, 0},
		{2, 0, 0, 7, 0},
	};
	print(bellmanFord(graph,0));
	getchar();
	return 0;
}
