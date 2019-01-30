struct line{
	bool ver;   //slope =inf.
	long double m, c;
};


line getLine(long double x1, long double y1, long double x2, long double y2) {
	line l;
	if(abs(x1-x2)<eps) {
		l.ver=1;
		l.m=-1;
		l.c=x1;
	} else{
		l.ver=0;
		l.m=(y2-y1)/(x2-x1);
		l.c=y1-l.m*x1;
	}
	return l;
}


//check if two lines are parallel
bool isParallel(line l1, line l2) {
	if(l1.ver!=l2.ver) return 0;
	if(abs(l1.m-l2.m)<eps) return 1;
	return 0;
}

struct point{
	long double x, y;
};

//intersection points of two lines(not parallel)
point lineIntersect(line l1, line l2) {
	if(l1.ver==0 && l2.ver==0) {
		long double x=(l2.c-l1.c)/(l1.m-l2.m);
		long double y=x*l1.m+l1.c;
		return {x, y};
	} else if(l1.ver==0 && l2.ver==1) {
		long double x=l2.c;
		long double y=l1.m*x+l1.c;
		return {x, y};
	} else{
		return lineIntersect(l2, l1);
	}
}


//get the 'symmetry' line of a set of PARALLEL lines, fail indicates there is no such line
line symmetryLine(vector<line> &v, bool &fail) {
	vector<long double>C;
	for(int i=0; i<sz(v); i++) {
		C.push_back(v[i].c);
	}
	sort(C.begin(), C.end());
	line l {0, -1, -1};
	fail=0;
	int n=sz(v);
	long double m=(C[0]+C[n-1])/2.0;
	for(int i=0; i<n; i++) {
		if(abs(m-C[i]-C[n-i-1]+m)>eps) {   //those two lines cannot be symmetric
			fail=1;
			return l;
		}
	}
	l.ver=v[0].ver;
	l.m=v[0].m;
	l.c=m;
	return l;
}
