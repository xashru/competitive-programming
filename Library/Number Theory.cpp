#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<class T> T gcd(T a, T b) {
	if(a<b) {
		swap(a, b);
	}
	T t;
	while(b>0) {
		t=a%b;
		a=b;
		b=t;
	}
	return a;
}

template<class T> T lcm(T a, T b) {
	T l=a/gcd(a, b);
	return l*b;
}

template<class T> T gcdL(vector<T> & v){
	int l=v.size();
	if(l==1) return v[0];
	T g=gcd(v[0], v[1]);
	for(int i=1; i<l-1; i++) {
		g=gcd(g, gcd(v[i], v[i+1]));
	}
	return g;
}

template<class T> T lcmL(vector<T> & v) {
	T l=v[0];
	int L=v.size();
	for(int i=0; i<L; i++) {
		l=l*v[i]/gcd(l, v[i]);
	}
	return l;
}

template <class T> bool prime(T n) {
	if(n<=1) return false;
	if(n<=3) return true;
	if(n%2==0) return false;
	long long m=floorl(sqrtl(n));
	for(long long i=3; i<=m; i++) {
		if(n%i==0) return false;
	}
	return true;
}

template<class T> vector<bool> sieve(T n) {
	vector<bool> prime;
	for(T i=0; i<=n; i++) {
		prime.push_back(true);
	}
	prime[0]=false;
	prime[1]=false;
	long long m=sqrtl(n);
	for(T i=2; i<=m; i++) {
		if(prime[i]) {
			for(T k=i*i; k<=n; k+=i) {
				prime[k]=false;
			}
		}
	}
	return prime;
}

template<class T> vector<T> sieveList(T n) {
	vector<T> primes;
	if(n<=1) return primes;
	vector<bool> prime;
	for(T i=0; i<=n; i++) {
		prime.push_back(true);
	}
	prime[0]=false;
	prime[1]=false;
	long long m=sqrtl(n);
	for(T i=2; i<=m; i++) {
		if(prime[i]) {
			for(T k=i*i; k<=n; k+=i) {
				prime[k]=false;
			}
		}
	}
	primes.push_back(2);
	for(int i=3; i<=n; i+=2) {
		if(prime[i]) primes.push_back(i);
	}
	return primes;
}

template<class T> vector<T> factor(T n) {
	vector<T> v;
	while(n%2==0) {
		v.push_back(2);
		n/=2;
	}
	long long m=sqrtl(n);
	for(T i=3; i<=m; i+=2) {
		while(n%i==0) {
			v.push_back(i);
			n/=i;
		}
	}
	if(n>2) {
		v.push_back(n);
	}
	return v;
}

// no of integers between two double values
long long inBetween(long double a, long double b) {
	a=ceill(a)==floorl(a)?a-1:floor(a);
	b=ceill(b)==floorl(b)?b+1:ceil(b);
	long long r=b-a-1;
	return r>=0?r:0;
}

// if a i a subset of b
bool subset(vector<int> a, vector<int> b) {
	sort(b.begin(), b.end());
	int n=a.size();
	for(int i=0; i<n; i++) {
		if(!binary_search(b.begin(), b.end(), a[i])) return false;
	}
	return true;
}

// count number of divisors given prime factorization of a number
int countDivisors(vector<int> factors) {
	sort(factors.begin(), factors.end());
	int p=1;
	int c=1;
	for(int i=1; i<factors.size(); i++) {
		if(factors[i]==factors[i-1]) c++;
		else {
			p*=(c+1);
			c=1;
		}
	}
	return p*(c+1);
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
template<class T> T extendedEuclid(T a, T b, T &x, T &y) {
	T xx=0;
	y=0;
	T yy=1;
	x=1;
	while(b) {
		T q=a/b;
		T t=b; b=a%b; a=t;
		t=xx; xx=x-q*xx; x=t;
		t=yy; yy=y-q*yy; y=t;
	}
	return a;
}

// return a % b (positive value)
template<class T> T mod(T a, T b) {
	return ((a%b)+b)%b;
}

// finds all solutions to ax = b (mod n)
template<class T> vector<T> modularLinearEquationSolver(T a, T b, T n) {
	T x, y;
	vector<T> solutions;
	T d=extendedEuclid(a, n, x, y);
	if(!(b%d)) {
		x=mod(x*(b/d), n);
		for(int i=0; i < d; i++)
			solutions.push_back(mod(x + i*(n/d), n));
	}
	return solutions;
}

// computes b such that ab=1 (mod n), returns -1 on failure
template<class T> T modInverse(T a, T n) {
	T x, y;
	T d=extendedEuclid(a, n, x, y);
	if(d > 1) return -1;
	return mod(x, n);
}

// Chinese remainder theorem(special case) : find z such that
// z % x = a, z % y = b.  Here, z is unique modulo M = lcm(x,y).
// Return (z,M).  On failure, M = -1.
template<class T> vector<T> CRT(T x, T a, T y, T b) {
	T s, t;
	T d=extendedEuclid(x, y, s, t);
	if(a%d != b%d) return {0, -1};
	return {mod(s*b*x+t*a*y, x*y)/d, x*y/d};
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
// failure, M = -1.  Note that we do not require the a[i]'s
// to be relatively prime.
template<class T> vector<T> CRT(const vector<T> &x, const vector<T> &a) {
	vector<T> ret={a[0], x[0]};
	for(int i=1; i < x.size(); i++) {
		ret=CRT(ret[1], ret[0], x[i], a[i]);
		if(ret[1] == -1) break;
	}
	return ret;
}

// computes x and y such that ax + by=c; on failure, x=y=-1
template<class T> void linearDiophantine(T a, T b, T c, T &x, T &y) {
	T d=gcd(a, b);
	if(c%d) {
		x=-1;
		y=-1;
	} else {
		x=c/d*modInverse(a/d, b/d);
		y=(c-a*x)/b;
	}
}