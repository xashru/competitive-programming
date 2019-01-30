//adjacency list form
bool isBipartite(vector<int> E[], int n) {
	vector<int> vis(n+5, -1);
	for(int i=0; i<=n; i++) {
		if(vis[i]!=-1) continue;
		queue<int> q;
		q.push(i);
		vis[i]=0;
		bool f=true;
		while(!q.empty()) {
			int x=q.front();
			q.pop();
			for(int i=0; i<E[x].size(); i++) {
				int v=E[x][i];
				if(vis[v]!=-1) {
					if(vis[x]==vis[v]) {
						f=false;
						break;
					}
				} else  {
					vis[v]=vis[x]==0?1:0;
					q.push(v);
				}
			}
			if(!f) return false;;
		}
	}
	return true;
}


//adjacency matrix form
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