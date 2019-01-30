#include <string>
#include <algorithm>
using namespace std;




void fail(string &s, int F[]) {
	F[0]=-1;
	F[1]=0;
	int pos=2, c=0;
	while(pos<=s.size()) {
		if(s[pos-1]==s[c]) {
			c++;
			F[pos]=c;
			pos++;
		} else if(c>0) {
			c=F[c];
		} else{
			F[pos]=0;
			pos++;
		}
	}
}

void match(string &s, string &w, int F[]) {
	int m=0, i=0;
	while(m+i<s.size()) {
		if(s[m+i]==w[i]) {
			if(i==w.size()-1) {   //complete match
				m=m+i-F[i];
				i=max(F[i], 0);
			} else{
				i++;
			}
		} else{
			if(F[i]>-1) {
				m=m+i-F[i];
				i=F[i];
			} else{
				m++;
				i=0;
			}
		}
	}
}


