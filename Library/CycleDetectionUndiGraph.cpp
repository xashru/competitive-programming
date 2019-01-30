bool isCyclicUtil(vector<vector<int>> &graph, int v, vector<bool> visited, int parent){
	visited[v]=true;
	int n=graph.size();
	for(int i=0; i<n; i++) {
		if(graph[v][i]==1) {
			if(!visited[i]){
				if(isCyclicUtil(graph, i, visited, v)) {
					return true;
				}
			} else if(i!=parent) {
				return true;
			}
		}
	}
	return false;
}

// we MUST add both i-j and j-i as edge
bool isCyclic(vector<vector<int>> &graph) {
	int n=graph.size();
	vector<bool> visited(n, 0);
	for(int u=0; u < n; u++) {
		if(!visited[u]) {
			if(isCyclicUtil(graph, u, visited, -1)){
				return true;
			}
		}
	}
	return false;
}