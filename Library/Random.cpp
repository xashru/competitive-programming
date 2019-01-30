#include <vector>

using namespace std;

int dx[]={-1, 0, 1, 1, 1, 0, -1, -1};
int dy[]={1, 1, 1, 0, -1, -1, -1, 0};

int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};

int dnx[]={1, 2, 2, 1, -1, -2, -2, -1};
int dny[]={2, 1, -1, -2, -2, -1, 1, 2};

//minimum number of swaps required to convert start into finish
//finish is a permutation of start so they must have unique value and equal after sort
int minSwaps(vector<int> start, vector<int> finish) {
	int c=0;
	int n=start.size();
	while(start!=finish) {
		for(int i=0; i<n; i++) {
			if(start[i]!=finish[i]) {
				for(int j=0; j<n; j++) {
					if(finish[j]==start[i]) {
						swap(start[i], start[j]);
						c++;
						break;
					}
				}
			}
		}
	}
	return c;
}

void diagonalTraversal(vector<string> &v) {
	int row=v.size(), col=v[0].size();

	//top-right to bottom-left
	for(int i=0; i < row + col - 1; i++) {
		int z1=i < col?0:i - col + 1;
		int z2=i < row?0:i - row + 1;
		//start position for s and rev(s) in v
		//cout<<z1<<" "<<i-z1<<" "<<i-z2<<" "<<z2<<" ";
		string s="";
		for(int j=z1; j <= i-z2; j++) {
			s+=v[j][i-j];
		}
	}

	//top-left to bottom-right
	for(int i=0; i < row + col - 1; i++) {
		int c=0;
		int z1=i < col?0:i - col + 1;
		int z2=i < row?col-1:col-i+row-2;
		//	cout<<z1<<" "<<col-1-i+z1<<" "<<z2-col+1+i<<" "<<z2<<" ";
		string s="";
		for(int j=z1; col-1-i+j<=z2; j++) {
			s+=v[j][col-1-i+j];
		}
	}
}
template<class T> T mod(T a, T b) {
	return ((a%b)+b)%b;
}

// return a % b (positive value)
template<class T> T mod(T a, T b) {
	return ((a%b)+b)%b;
}

//x^n mod m
ll fast(ll x, ll n, ll m=LLONG_MAX) {
	ll res=1;
	while(n>0) {
		if(n%2==1){
			res=res*x;
			res%=m;
		}
		x=x*x;
		x%=m;
		n/=2;
	}
	re res;
}


//find x such that ax=1 (mod m)
ll modInv(ll a, ll m){
	ll b0=m, t, q;
	ll x0=0, x1=1;
	if(m == 1) return 1;
	while(a > 1) {
		q=a / m;
		t=m, m=a % m, a=t;
		t=x0, x0=x1 - q * x0, x1=t;
	}
	if(x1 < 0) x1+=b0;
	return x1;
}

int bcount(long long x){
	int r=0;
	for(; x; x&=(x-1)) r++;
	return r;
}

void rand() {
	std::random_device rd;     
	std::mt19937 rng(rd());   
	std::uniform_int_distribution<int> uni(min, max); 
	auto x=uni(rng);
}


//functor
struct cmpx {
	bool operator() (point a, point b) {
		if(a.x!=b.x) re a.x<b.x;
		re a.y<b.y;
	}
};

//rotate by 90 degree
vector<string> rot90(vector<string> &v) {
	int row=v.size(), col=v[0].size();
	vector<string> R;
	R.assign(col, string(row, '0'));
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; j++) {
			R[j][row-1-i]=v[i][j];
		}
	}
	return R;
}

//vertical flip
vector<string> flipv(vector<string> &v) {
	int row=v.size(), col=v[0].size();
	vector<string> R;
	R.assign(row, string(col, '0'));
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; j++) {
			R[i][j]=v[i][col-1-j];
		}
	}
	return R;
}

//horizontal flip
vector<string> fliph(vector<string> &v) {
	int row=v.size(), col=v[0].size();
	vector<string> R;
	R.assign(row, string(col, '0'));
	for(int i=0; i<row; i++) {
		for(int j=0; j<col; j++) {
			R[i][j]=v[row-1-i][j];
		}
	}
	return R;
}

//check if 2 strings are same under rotation/reflection etc
bool sameTransform(vector<string> &a, vector<string> b) {
	for(int i=0; i<4; i++) {
		if(b==a) return true;
		if(flipv(b)==a) return true;
		if(fliph(b)==a) return true;
		b=rot90(b);
	}
	return false;
}



//merge 2 vectors
void merge(vi &v1, vi &v2) {
	vi v;
	v1.push_back(INT_MAX), v2.push_back(INT_MAX);
	int p1=0, p2=0;
	for(int i=0; i<sz(v1)+sz(v2)-2; i++) {
		if(v1[p1]<=v2[p2]) {
			v[i]=v1[p1];
			v.push_back(v1[p1]);
			p1++;
		} else {
			v.push_back(v2[p2]);
			p2++;
		}
	}
}

//cost for going from (0,0) to (a,b) point for a chess knight
long long knightDistance(long long a, long long b) {
	a=abs(a);
	b=abs(b);
	if(a<b) swap(a, b);
	if(a==1 && b==0) re 3;
	if(a==2 && b==2) re 4;
	long long ans=max((a+1)/2, (a+b+2)/3);
	if(ans%2!=(a+b)%2) ans++;
	return ans;
}