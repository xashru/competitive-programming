#include <set>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define eps 1e-10


struct point{
	long double x, y;
};

bool operator<(point a, point b) {
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}

struct cmpx {
	bool operator() (point a, point b) {
		if(a.x!=b.x) return a.x<b.x;
		return a.y<b.y;
	}
};

struct cmpy {
	bool operator() (point a, point b) {
		if(a.y!=b.y) return a.y<b.y;
		return a.x<b.x;
	}
};

long double calc(vector<point> &v) {
	sort(v.begin(), v.end());
	long double h=1e50;
	set<point, cmpx> curx;
	set<point, cmpy> cury;
	for(int i=0; i<v.size(); i++)  {
		for(auto it=curx.begin(); it!=curx.end();) {
			long double dx=v[i].x-it->x;
			if(dx>=h) {
				cury.erase(*it);
				curx.erase(it++);
			} else {
				break;
			}
		}

		point lo={v[i].x, v[i].y-h-eps}, hi={v[i].x, v[i].y+h+eps};
		auto i1=cury.upper_bound(lo), i2=cury.upper_bound(hi);
		while(i1!=cury.end() && i1!=i2) {
			long double dx=v[i].x-i1->x, dy=v[i].y-i1->y;
			long double d=sqrtl(dx*dx+dy*dy);
			h=min(h, d);
			i1++;
		}
		curx.insert(v[i]);
		cury.insert(v[i]);
	}
	return h;
}

int main() {
	long double n, x, s=0;
	cin>>n;
	vector<point> v;
	for(int i=1; i<=n; i++) {
		cin>>x;
		s+=x;
		v.push_back({i, s});
	}
	long double r=calc(v);
	cout<<(round(r*r));
	return 0;
}