#include <vector>
#include <iostream>
using namespace std;

template<class T> vector<vector<T>> mult(vector<vector<T>> A, vector<vector<T>> B, long long mod=LLONG_MAX) {
	int n=A[0].size();
	int m=A.size();
	int p=B[0].size();
	vector<vector<T>> ans(m, vector<T>(p));
	if(A[0].size()!=B.size()) return ans;
	for(int i=0; i < m; i++){
		for(int j=0; j < p; j++){
			for(int k=0; k < n; k++){
				ans[i][j]+=A[i][k] * B[k][j];
				ans[i][j]%=mod;
			}
		}
	}
	return ans;
}

template<class T> vector<vector<T>> pow(vector<vector<T>> A, long long n, long long mod=LLONG_MAX) {
	int r=A.size();
	int c=A[0].size();
	vector<vector<T>> ans(r, vector<T>(c));
	for(int i=0; i<r; i++)
		for(int j=0; j<c; j++)
			ans[i][j]=i==j?1:0;
	while(n>0) {
		if(n%2!=0) ans=mult(ans, A, mod);
		A=mult(A, A, mod);
		n/=2;
	}
	return ans;
}