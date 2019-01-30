#include <string> 
#include <iostream>
using namespace std;

long long M=999999999999353,b=31;
const int X=100000+5;
long long B[X], H[X];                                                                              

long long myHash(string &s) {
	long long h=0;
	for(int i=0; i<s.size(); i++) {
		h=(h*b+s[i])%M;
	}
	return h;
}


bool match(string &s, string &p) {
	B[0]=1;
	for(long long i=1; i<X; i++) {
		B[i]=(B[i-1]*b)%M;
	}
	H[0]=s[0];
	for(int i=1; i<s.size(); i++) {
		H[i]=(H[i-1]*b+s[i])%M;
	}
	long long hp=myHash(p);
	int k=p.size();
	for(int i=0; i+k-1<s.size(); i++) {
		if(H[i+k-1]==(hp+H[i]*B[k])%M) {
			cout<<i<<endl;
		}
	}
	return false;
}

int main() {
	while(!cin.eof()) {
		int n;
		cin>>n;
		string s,p;
		cin>>s>>p;
		match(s,p);
		cout<<endl;
	}
	return 0;
}
