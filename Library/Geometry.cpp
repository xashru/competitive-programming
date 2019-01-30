#include <vector>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

struct point{
	long double x, y;
};

bool operator<(point a, point b) {
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

point operator+(point a, point b) {
	return {a.x+b.x, a.y+b.y};
}

point operator-(point a, point b) {
	return {a.x-b.x, a.y-b.y};
}

long double operator*(point a, point b) {
	return a.x*b.x+a.y*b.y;
}

long double operator^(point a, point b) {
	return a.x*b.y-a.y*b.x;
}

// distance from C to AB line, if isSegment is true then AB is a segment not line
long double linePointDist(point &A, point &B, point &C, bool isSegment){
	long double dist=((B-A)^(C-A)) / sqrtl((B-A)*(B-A));
	if(isSegment){
		long double dot1=(C-B)*(B-A);
		if(dot1 > 0) return sqrtl((B-C)*(B-C));
		long double dot2=(C-A)*(A-B);
		if(dot2 > 0)return sqrtl((A-C)*(A-C));
	}
	return abs(dist);
}

long double polygonArea(vector<point> &p) {
	long double area=0;
	int N=p.size();
	for(int i=1; i<N-1; i++){
		long double x1=p[i].x - p[0].x;
		long double y1=p[i].y - p[0].y;
		long double x2=p[i+1].x - p[0].x;
		long double y2=p[i+1].y - p[0].y;
		long double cross=x1*y2 - x2*y1;
		area+=cross;
	}
	return abs(area/(long double)2.0);
}

long double dist(point p1, point p2) {
	return sqrtl((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

// closest pair using line sweep
long double closestPair(vector<point> &v) {
	sort(v.begin(), v.end());
	set<point> s;
	set<point>::iterator it;
	s.insert(v[0]);
	long double m=1e100;
	int n=v.size();
	for(int i=1; i<n; i++) {
		point p=v[i];
		for(it=s.begin(); it!=s.end();) {
			point p1=*it;
			if(p.x-p1.x>m) s.erase(it++);
			else {
				m=min(m, dist(p, p1));
				it++;
			}
		}
		s.insert(p);
	}
	return m;
}

// intersection point of AB ad CD line
point lineIntersect(point A, point B, point C, point D) {
	long double a1=B.y-A.y;
	long double b1=A.x-B.x;
	long double c1=a1*A.x+b1*A.y;

	long double a2=D.y-C.y;
	long double b2=C.x-D.x;
	long double c2=a2*C.x+b2*C.y;

	long double det=a1*b2 - a2*b1;
	if(abs(det) <eps){
		return {-999999, -9999999};
	} else{
		long double x=(b2*c1 - b1*c2)/det;
		long double y=(a1*c2 - a2*c1)/det;
		return {x, y};
	}
}

// polar angle of the given point
long double  polarAngle(point p) {
	if(fabs(p.x) <= eps && fabs(p.y) <= eps) return -1.0;
	if(fabs(p.x) <= eps) return (p.y > eps?1.0:3.0) * acos(0);
	long double  theta=atan(1.0 * p.y / p.x);
	if(p.x > eps) return(p.y >= -eps?theta:(4 * acos(0) + theta));
	return(2 * acos(0) + theta);
}

// returns true iff p is inside poly.
bool pointInPoly(point &p, vector<point> &poly) {
	int n=poly.size();
	long double  ang=0.0;
	for(int i=n - 1, j=0; j < n; i=j++) {
		point v {poly[i].x - p.x, poly[i].y - p.y};
		point w {poly[j].x - p.x, poly[j].y - p.y};
		long double  va=polarAngle(v);
		long double  wa=polarAngle(w);
		long double  xx=wa - va;
		if(va < -0.5 || wa < -0.5 || fabs(fabs(xx) - 2 * acos(0)) < eps) {
			ang+=2 * acos(0);
			continue;
		}
		if(xx < -2 * acos(0)) ang+=xx + 4 * acos(0);
		else if(xx > 2 * acos(0)) ang+=xx - 4 * acos(0);
		else ang+=xx;
	}
	return(ang * ang >= 1.0);
}
