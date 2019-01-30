#include <vector>
using namespace std;

// n!
unsigned long long fact(int n) {
	unsigned long long f=1;
	for(int i=2;i<=n;i++) f*=i;
	return f;
}

//nPr
template<class T> long long perm(T n, T r) {
	if(r>n) return -1;
	long long p=1;
	for(T i=n;i>n-r;i--) p*=i;
	return p;
}

//binomial coefficient
vector<vector<long long>> binomial(long long n, long long mod=MOD){
	vector<vector<long long>> C;
	C.assign(n+5, vector<long long>(n+5, 0));
	for(int i=0; i <= n; i++){
		for(int j=0; j <= i; j++){
			if(j == 0 || j == i){
				C[i][j]=1;
			} else{
				C[i][j]=C[i-1][j-1] + C[i-1][j];
				C[i][j]%=mod;
			}
		}
	}
	return C;
}

//nCr
template<class T> long long comb(T n, T k) {
	if(k>n) re 0;
	if(k==0) return 1;
	long long res = 1;
	if ( k > n - k ) k = n - k;
	for (int i = 0; i < k; ++i) {
		res *= (n - i);
		res /= (i + 1);
	}
	return res;
}



//stirling's number of 2nd kind, number of ways to partition a n element set into k partitions
vector<vector<long long>> stirling(long long n, long long k) {
	vector<vector<long long>> v(n+1, vector<long long>(k+1, 0));
	for(long long i=0; i<=n; i++) {
		for(long long j=0; j<=k; j++) {
			if(i==0 && j==0) v[i][j]=1;
			else if(i*j==0) v[i][j]=0;
			else v[i][j]=j*v[i-1][j]+v[i-1][j-1];
		}
	}
	return v;
}