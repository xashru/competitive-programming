struct DSU{
	int N, connectedComponent=0, cycles=0;
	vector<int> P, R, C;  //parent,ranks,number of nodes with this parent

	DSU() {

	}

	DSU(int n) {
		P.assign(n+5, 0);
		R.assign(n+5, 0);
		C.assign(n+5, 0);
	}

	void makeAll(int n) {
		for(int i=1; i<=n; i++) {
			P[i]=i;
			connectedComponent++;
			C[i]=1;
		}
	}

	void makeSet(int n) {
		P[n]=n;
		connectedComponent++;
		C[n]=1;
	}

	int findSet(int n) {
		if(P[n]!=n) P[n]=findSet(P[n]);
		return P[n];
	}

	void mergeSet(int a, int b) {
		int px=findSet(a), py=findSet(b);
		if(px==py) {
			cycles++;
			return;
		}
		if(R[px]>R[py]){
			P[py]=px;
			C[px]+=C[py];
			C[py]=0;
		} else {
			P[px]=py;
			C[py]+=C[px];
			C[px]=0;
		}
		if(R[px]==R[py]) R[py]++;
		connectedComponent--;
	}
};