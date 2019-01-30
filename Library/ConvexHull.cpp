#include <vector>
#include <algorithm>
using namespace std;

struct point{
	long long x, y;
};

bool operator<(point a, point b) {
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

bool isCCW(point a, point b, point c) {
	return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x)>0;
}

vector<point> convexHull(vector<point> &P) {
	sort(P.begin(), P.end());
	vector<point> L, U;
	int n=P.size();
	for(int i=0; i<n; i++) {
		while(L.size()>=2 && !isCCW(L[L.size()-2], L[L.size()-1], P[i])) {
			L.pop_back();
		}
		L.push_back(P[i]);
	}
	for(int i=n-1; i>=0; i--) {
		while(U.size()>=2 && !isCCW(U[U.size()-2], U[U.size()-1], P[i])) {
			U.pop_back();
		}
		U.push_back(P[i]);
	}
	L.pop_back();
	L.insert(L.end(), U.begin(), U.end());
	L.pop_back();
	return L;
}
