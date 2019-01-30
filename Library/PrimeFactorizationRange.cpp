bool v[X];
int len, sp[X];

void sieve(){
	for(int i=2; i < X; i+=2)	sp[i]=2;
	for(ll i=3; i < X; i+=2){
		if(!v[i]){
			sp[i]=i;
			for(ll j=i; (j*i) < X; j+=2){
				if(!v[j*i])	v[j*i]=true, sp[j*i]=i;
			}
		}
	}
}

vector <int> factorize(int k) {
	vector <int> ans;
	while(k>1) {
		ans.push_back(sp[k]);
		k/=sp[k];
	}
	return ans;
}