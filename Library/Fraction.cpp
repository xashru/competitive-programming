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

struct frac{
	long long up, down;
};

frac operator+(frac a, frac b) {
	long long d=lcm(a.down, b.down);
	long long u=(d/a.down)*a.up+(d/b.down)*b.up;
	long long g=gcd(u, d);
	u/=g;
	d/=g;
	return {u, d};
}

frac operator-(frac a, frac b) {
	b.up*=-1;
	return a+b;
}

frac operator*(frac a, frac b) {
	long long d=a.down*b.down;;
	long long u=a.up*b.up;
	long long g=gcd(u, d);
	u/=g;
	d/=g;
	return {u, d};
}

frac operator/(frac a, frac b) {
	swap(b.down, b.up);
	return a*b;
}