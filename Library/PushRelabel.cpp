#include <cmath>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;

struct edge {
	int from, to, cap, flow, index;
	edge(int from, int to, int cap, int flow, int index) :
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};

//To obtain the actual flow values, look at all edges with capacity > 0 (0 capacity edges are residual edges).
struct pushRelabel {
	int N;
	vector<vector<edge>> G;
	vector<ll> excess;
	vector<int> dist, active, count;
	queue<int> Q;
	pushRelabel(int N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}
	void addEdge(int from, int to, int cap) {
		G[from].push_back(edge(from, to, cap, 0, G[to].size()));
		if(from == to) G[from].back().index++;
		G[to].push_back(edge(to, from, 0, 0, G[from].size() - 1));
	}
	void enqueue(int v) {
		if(!active[v] && excess[v] > 0) {
			active[v]=true; Q.push(v);
		}
	}
	void push(edge &e) {
		int x=int(min(excess[e.from], ll(e.cap - e.flow)));
		if(dist[e.from] <= dist[e.to] || x == 0) return;
		e.flow+=x;
		G[e.to][e.index].flow-=x;
		excess[e.to]+=x;
		excess[e.from]-=x;
		enqueue(e.to);
	}
	void gap(int k) {
		for(int v=0; v < N; v++) {
			if(dist[v] < k) continue;
			count[dist[v]]--;
			dist[v]=max(dist[v], N+1);
			count[dist[v]]++;
			enqueue(v);
		}
	}
	void relabel(int v) {
		count[dist[v]]--;
		dist[v]=2*N;
		for(int i=0; i < G[v].size(); i++)
			if(G[v][i].cap - G[v][i].flow > 0)
				dist[v]=min(dist[v], dist[G[v][i].to] + 1);
		count[dist[v]]++;
		enqueue(v);
	}
	void discharge(int v) {
		for(int i=0; excess[v] > 0 && i < G[v].size(); i++) push(G[v][i]);
		if(excess[v] > 0) {
			if(count[dist[v]] == 1)
				gap(dist[v]);
			else
				relabel(v);
		}
	}
	ll maxFlow(int s, int t) {
		count[0]=N-1;
		count[N]=1;
		dist[s]=N;
		active[s]=active[t]=true;
		for(int i=0; i < G[s].size(); i++) {
			excess[s]+=G[s][i].cap;
			push(G[s][i]);
		}
		while(!Q.empty()) {
			int v=Q.front();
			Q.pop();
			active[v]=false;
			discharge(v);
		}
		ll totflow=0;
		for(int i=0; i < G[s].size(); i++) totflow+=G[s][i].flow;
		return totflow;
	}
};
