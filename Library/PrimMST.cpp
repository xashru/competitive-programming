#define _CRT_SECURE_NO_WARNINGS
#include <cctype>
#include <climits>
#include <cmath>
#include <cstring>
#include <deque>
#include <fstream>
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
#include <random>

using namespace std;

#define sz(v) (int)v.size()
#define eps 1e-10
#define all(v) v.begin(), v.end() 
#define CLR(a) memset(a,0,sizeof(a))
#define SET(a) memset(a,-1,sizeof(a))
#define chk(a,k) ((bool)(a&(1<<(k))))
#define set0(a,k) (a&=(~(1<<(k))))
#define set1(a,k) (a|=(1<<(k)))
#define in(v, x) (find(all(v),x) != v.end()) 
#define re return
#define sum(v) accumulate(v.begin(),v.end(),(ld)0)
#define tr(v,it) for(auto it=v.begin();it != v.end();it++)
#define asrt(v) sort(v.begin(),v.end())
#define dsrt(v) sort(v.rbegin(),v.rend())
#define rev(v) reverse(v.begin(),v.end())
#define pi 3.1415926535897932384626433832795
#define MOD 1000000007
#define print(v) for (auto& i:v) cout<<i<<endl 
#define endl '\n'

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<string> vs;
typedef vector<vi> vvi;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<string> vs;
typedef vector<vi> vvi;


struct edge{
	ll u, c;
};

bool operator<(edge a, edge b) {
	re a.c>b.c;
}

const int M=10000+5;

vector<edge> E[M];
bool vis[M];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	freopen("Data/input.txt", "r", stdin);
	freopen("Data/output.txt", "w", stdout);
	int n, m;
	cin>>n>>m;
	for(int i=0; i<m; i++) {
		int u, v, c;
		cin>>u>>v>>c;
		edge e1 {v, c}, e2 {u, c};
		E[u].push_back(e1);
		E[v].push_back(e2);
	}
	ll res=0;
	priority_queue<edge> pq;
	for(int i=0; i<sz(E[1]); i++) {
		pq.push(E[1][i]);
	}
	vis[1]=1;
	while(!pq.empty()) {
		edge top=pq.top();
		pq.pop();
		if(vis[top.u]) continue;
		vis[top.u]=1;
		res+=top.c;
		for(int i=0; i<sz(E[top.u]); i++) {
			pq.push({E[top.u][i]});
		}
	}
	cout<<res;
	return 0;
}
