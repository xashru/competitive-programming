#include <vector>
#include <queue>
#include <stack>
using namespace std;

// utility function in max BPM
bool bpm(vector< vector<bool>> &graph, int u, vector<bool>&seen, vector<int> &matchL, vector<int> &matchR) {
	int n=graph[0].size();
	for(int v=0; v < n; v++) {
		if(!graph[u][v] || seen[v]) continue;
		seen[v]=true;
		if((matchR)[v] == -1 || bpm(graph, matchR[v], seen, matchL, matchR)) {
			matchL[u]=v;
			matchR[v]=u;
			return true;
		}
	}
	return false;
}

// returns maximum number of matching in bipartite graph
int maximumBipartiteMatching(vector< vector<bool>> &graph) {
	int m=graph.size();
	if(m==0) return 0;
	int n=graph[0].size();
	if(n==0) return 0;
	vector<int> matchL(m, -1), matchR(n, -1);
	int count=0;
	for(int i=0; i < m; i++) {
		vector<bool> seen;
		for(int k=0; k<n; k++) seen.push_back(false);
		if(bpm(graph, i, seen, matchL, matchR)) count++;
	}
	return count;
}

// check whether the given graph is 2-colorable
bool isBipartite(vector<vector<int>> mat) {
	int n=mat.size();
	vector<int> vis;
	for(int i=0; i<n; i++) vis.push_back(-1);
	for(int i=0; i<n; i++) {
		if(vis[i]!=-1) continue;
		queue<int> q;
		q.push(i);
		vis[i]=0;
		bool f=true;
		while(!q.empty()) {
			int x=q.front();
			q.pop();
			for(int i=0; i<n; i++) {
				if(mat[x][i]==1 && vis[i]!=-1) {
					if(vis[x]==vis[i]) {
						f=false;
						break;
					}
				}
				if(mat[x][i]==1 && vis[i]==-1) {
					vis[i]=vis[x]==0?1:0;
					q.push(i);
				}
			}
			if(!f) return false;;
		}
	}
	return true;
}

// number of connected components in a undirected graph
int connectedCompononents(vector<vector<int>> mat) {
	int n=mat.size();
	int c=0;
	vector<bool> vis;
	for(int i=0; i<n; i++) vis.push_back(false);
	for(int i=0; i<n; i++) {
		if(vis[i]) continue;
		queue<int> q;
		q.push(i);
		vis[i]=true;
		c++;
		while(!q.empty()) {
			int x=q.front();
			q.pop();
			for(int j=0; j<n; j++) {
				if(mat[x][j]==0) continue;
				if(vis[j]) continue;
				q.push(j);
				vis[j]=true;
			}
		}
	}
	return c;
}

// utility function in toposort
void dfs_topo(vector<vector<int>> *graph, vector<bool> *vis, stack<int> *s, int u) {
	(*vis)[u]=true;
	int n=(*graph).size();
	for(int i=n-1; i>=0; i--) {
		if((*vis)[i] || (*graph)[u][i]==0) continue;
		dfs_topo(graph, vis, s, i);
	}
	(*s).push(u);
}

// topological ordering of a graph
vector<int> toposort(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis;
	stack<int> s;
	for(int i=0; i<n; i++) vis.push_back(false);
	for(int i=n-1; i>=0; i--) {
		if(vis[i]) continue;
		dfs_topo(&graph, &vis, &s, i);
	}
	vector<int> res;
	while(!s.empty()) {
		int top=s.top();
		s.pop();
		res.push_back(top);
	}
	return res;
}

// number of simple paths from u to v in DAG, requires toposort function
int numPaths(vector<vector<int>> graph, int u, int v) {
	vector<int> topo=toposort(graph);
	queue<int> s;
	s.push(u);
	vector<int> counts;
	int n=graph.size();
	for(int i=0; i<n; i++) counts.push_back(0);
	int ind=0;
	for(int i=0; i<topo.size(); i++) {
		if(topo[i]==u) {
			ind=i;
			break;
		}
	}
	counts[topo[ind]]=1;
	for(int i=ind; i<n; i++) {
		int node=topo[i];
		if(node==v) return counts[node];
		for(int j=i+1; j<n; j++) {
			if(graph[node][topo[j]]!=0) counts[topo[j]]+=counts[node];
		}
	}
	return 0;
}

// helper function for isCyclic
bool dfs_cycle(vector<vector<int>> *graph, vector<bool> *vis, vector<bool> *rec, int u, bool *cycle) {
	(*rec)[u]=true;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*cycle)) return true;
		if((*graph)[u][i]==0 || (*vis)[i]) continue;
		if((*rec)[i]) {
			(*cycle)=true;
			return true;
		}
		dfs_cycle(graph, vis, rec, i, cycle);
	}
	(*vis)[u]=true;
	(*rec)[u]=false;
	return false;
}

// check whether the graph is cyclic
bool isCyclic(vector<vector<int>> graph) {
	vector<bool> vis, rec; 
	int n=graph.size();
	for(int i=0; i<n; i++) {
		vis.push_back(false);
		rec.push_back(false);
	}
	bool cycle=false;
	for(int i=0; i<n; i++) {
		if(!vis[i] && dfs_cycle(&graph, &vis, &rec, i, &cycle)) return true;
	}
	return false;
}

// helper function for scc
void dfs_scc(vector<vector<int>> *graph, stack<int> *s, vector<bool> *vis, int u) {
	(*vis)[u]=true;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*graph)[u][i]==0 || (*vis)[i]) continue;
		dfs_scc(graph, s, vis, i);
	}
	(*s).push(u);
}

// returns all strongly connected components of a graph
vector<vector<int>> scc(vector<vector<int>> graph) {
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

// helper function for articulation points
void dfs_ap(vector<vector<int>> *graph, vector<bool> *vis, vector<int> *disc, vector<int> *low,
	vector<int> *parent, vector<bool> *ap, int u, int *time) {
	int children=0;
	(*vis)[u]=true;
	(*time)=(*time)+1;
	(*disc)[u]=(*low)[u]=*time;
	int n=(*graph).size();
	for(int i=0; i<n; i++) {
		if((*graph)[u][i]!=0 && !(*vis)[i]) {
			children++;
			(*parent)[i]=u;
			dfs_ap(graph, vis, disc, low, parent, ap, i, time);
			(*low)[u]=min((*low)[u], (*low)[i]);
			if((*parent)[u]==-1 && children >1) (*ap)[u]=true; // root with more than 2 children
			if((*parent)[u]!=-1 && (*low)[i]>=(*disc)[u]) (*ap)[u]=true;
		} else if((*graph)[u][i]!=0 && i!=(*parent)[u]) (*low)[u]=min((*low)[u], (*disc)[i]);
	}
}

// detect all articulation points in an undirected graph
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

// helper function for bridges
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

// detect all bridge edges in the graph
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
	}	return bridges;
}

// for biconnectedComponents
struct edge{
	int u, v;
};

// required for biconnectedComponents
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

// returns all biconnected components of the graph as different set of edges
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

// for mst
struct edge{
	int u, v, c;
};

bool operator<(edge a, edge b) {
	return a.c>b.c;
}

int mst_kruskal(vector<vector<int>> graph) {
	int n=graph.size();
	vector<int>rank;
	for(int i=0; i<n; i++) rank.push_back(i);
	priority_queue<edge> pq;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			if(graph[i][j]!=0) {  //change 0 with sentinnel value
				edge e={i, j, graph[i][j]};
				pq.push(e);
			}
		}
	}
	int cost=0;
	vector<edge> V;
	while(!pq.empty()) {
		edge top=pq.top();
		pq.pop();
		int u=top.u, v=top.v, c=top.c;
		if(rank[u]==rank[v]) continue;
		int r1=min(rank[u], rank[v]), r2=max(rank[u], rank[v]);
		for(int i=0; i<n; i++) {
			if(rank[i]==r2) rank[i]=r1;
		}
		cost+=c;
		V.push_back(top);
		if(V.size()==n-1) break;
	}
	return cost;
}

int mst_prim(vector<vector<int>> graph) {
	int n=graph.size();
	vector<bool> vis;
	for(int i=0; i<n; i++) vis.push_back(false);
	int cost=0;
	vector<edge> V;
	priority_queue<edge> pq;
	vis[0]=true;
	for(int i=0; i<n; i++) {
		if(graph[0][i]!=0) {
			edge e={0, i, graph[0][i]};
			pq.push(e);
		}
	}
	while(!pq.empty()) {
		edge top=pq.top();
		pq.pop();
		int v=top.v, c=top.c;
		if(vis[v]) continue;
		vis[v]=true;
		cost+=c;
		V.push_back(top);
		if(V.size()==n-1) break;
		for(int i=0; i<n; i++) {
			if(graph[v][i]!=0 && !vis[i]) {
				edge e={v, i, graph[v][i]};
				pq.push(e);
			}
		}
	}
	return cost;
}

// single source shortest paths bellman-ford
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
					dp[j]=min(dp[j], dp[i]+graph[i][j]);
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

// maximum flow
int maxFlow(vector<vector<int>> graph, int s, int t) {
	int flow=0;
	while(true) {
		int x=findFlow(&graph, s, t);
		if(x==0) break;
		flow+=x;
	}
	return flow;
}

// floyd-warshall
vector<vector<int>> all_pair(vector<vector<int>> graph) {
	int n=graph.size();
	int nil=-1, inf=99999999;
	vector<vector<int>> dist;
	for(int i=0; i<n; i++) {
		vector<int> t;
		for(int j=0; j<n; j++) {
			if(i==j) t.push_back(0);
			else if(graph[i][j]!=nil) t.push_back(graph[i][j]);
			else t.push_back(inf);
		}
		dist.push_back(t);
	}

	for(int k=0; k<n; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<n; j++) {
				dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
			}
		}
	}
	return dist;
}