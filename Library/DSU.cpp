#include <vector>
#include <iostream>
using namespace std;

struct DSU{
	int N, connectedComponent=0, cycles=0;
	vector<int> P, R, C;  //parent,ranks,number of nodes with this parent
	DSU(int n) {
		P.assign(n+5, 0);
		R.assign(n+5, 0);
		C.assign(n+5, 0);
		for(int i=1; i<=n; i++) {
			makeSet(i);
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





void MAIN() {
	int n, m, u, v;
	cin>>n>>m;
	DSU dsu(n);
	for(int i=0; i<m; i++) {
		cin>>u>>v;
		dsu.mergeSet(u, v);
	}
	if(dsu.cycles==1 && dsu.connectedComponent==1) cout<<"FHTAGN!";
	else cout<<"NO";
}

int main() {
	MAIN();
	return 0;
}
