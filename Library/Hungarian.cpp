#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Hungarian{
	int N;
	ll inf=LLONG_MAX;
	vector<vector<ll>> cost;
	int n, max_match;
	vector<ll> lx, ly, xy, yx, slack, slackx, prev;
	vector<bool> S, T;
	Hungarian(int N) : N(N), cost(N, vector<ll>(N)), lx(N, 0), ly(N, 0), xy(N), yx(N), slack(N), slackx(N),
		prev(N), S(N), T(N) {}

	void initLabels() {
		n=N;
		for(int x=0; x < n; x++)
			for(int y=0; y < n; y++)
				lx[x]=max(lx[x], cost[x][y]);
	}

	void augment() {
		if(max_match == n) return;
		int x, y, root;
		vector<ll> q(N);
		int wr=0, rd=0;
		for(int i=0; i<N; i++) {
			S[i]=false, T[i]=false, prev[i]=-1;
		}
		for(x=0; x < n; x++) {
			if(xy[x] == -1) {
				q[wr++]=x;
				root=x;
				prev[x]=-2;
				S[x]=true;
				break;
			}
		}
		for(y=0; y < n; y++) {
			slack[y]=lx[root] + ly[y] - cost[root][y];
			slackx[y]=root;
		}
		while(true) {
			while(rd < wr) {
				x=q[rd++];
				for(y=0; y < n; y++)
					if(cost[x][y] == lx[x] + ly[y] && !T[y]){
						if(yx[y] == -1) break;
						T[y]=true;
						q[wr++]=yx[y];
						addToTree(yx[y], x);
					}
				if(y < n) break;
			}
			if(y < n) break;
			updateLabels();
			wr=rd=0;
			for(y=0; y < n; y++)
				if(!T[y] && slack[y] == 0){
					if(yx[y] == -1) 	{
						x=slackx[y];
						break;
					} else{
						T[y]=true;
						if(!S[yx[y]]){
							q[wr++]=yx[y];
							addToTree(yx[y], slackx[y]);
						}
					}
				}
			if(y < n) break;
		}
		if(y < n) {
			max_match++;
			for(int cx=x, cy=y, ty; cx != -2; cx=prev[cx], cy=ty)	{
				ty=xy[cx];
				yx[cy]=cx;
				xy[cx]=cy;
			}
			augment();
		}
	}

	void updateLabels() {
		ll x, y, delta=inf;
		for(y=0; y < n; y++) {
			if(!T[y])
				delta=min(delta, slack[y]);
		}
		for(x=0; x < n; x++) {
			if(S[x]) lx[x]-=delta;
		}
		for(y=0; y < n; y++){
			if(T[y]) ly[y]+=delta;
		}
		for(y=0; y < n; y++) {
			if(!T[y])
				slack[y]-=delta;
		}
	}

	void addToTree(int x, int prevx){
		S[x]=true;
		prev[x]=prevx;
		for(int y=0; y < n; y++) {
			if(lx[x] + ly[y] - cost[x][y] < slack[y]) {
				slack[y]=lx[x] + ly[y] - cost[x][y];
				slackx[y]=x;
			}
		}
	}

	ll hungarian() {
		ll ret=0;
		max_match=0;
		for(int i=0; i<N; i++) {
			xy[i]=-1, yx[i]=-1;
		}
		initLabels();
		augment();
		for(int x=0; x < n; x++) {
			ret+=cost[x][xy[x]];
		}
		return ret;
	}
};