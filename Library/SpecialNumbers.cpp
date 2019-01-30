//bernoulli numbers  B(1) = -1/2
// used in power series sum
ll B[X];
ll ber(ll m) {
	if(B[m]!=-1) return B[m];
	ll r=0;
	if(m==0) r=1;
	for(ll k=0; k<m; k++) {
		ll r1=C[m][k];
		r1*=ber(k);
		r1%=MOD;
		r1*=modInv(m-k+1, MOD);
		r1%=MOD;
		r-=r1;
		r=mod(r, MOD);
	}
	B[m]=r;
	return r;
}

//bell number, number of partitions of a set with n elements
long long bell(int n) {
	if(n<=1) return 1;
	vector<long long> cur, pre;
	pre.push_back(1);
	for(int i=2; i<=n; i++) {
		cur.clear();
		cur.push_back(pre[pre.size()-1]);
		for(int j=1; j<i; j++) cur.push_back(cur[j-1]+pre[j-1]);
		pre=cur;
	}
	return cur[n-1];
}

//stirling number of the second kind, number of ways to partition a set of n elements into k non-empty subsets
vector<vector<long long>> stirling(int n, int k) {
	vector<vector<long long>> v(n+1, vector<long long>(k+1));
	v[0][0]=1;
	for(int i=1; i<=n; i++) {
		v[i][i]=1;
		v[i][0]=0;
	}
	for(int i=2; i<=n; i++) {
		int lim=min(k, i-1);
		for(int j=1; j<=lim; j++)
			v[i][j]=j*v[i-1][j]+v[i-1][j-1];
	}
	return v;
}