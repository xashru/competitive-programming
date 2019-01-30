#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;



const int X=100000+5;
const int alp=26;
int G[X][alp];  //fill with -1
int O[X];  //which word is matched ending at state s
int P[X]; //how many words have this as their prefix
int C[X]; //how many words match with the given word exactly

int ctoi(char ch) {
	return ch-'a';
}

void go(vector<string> &v) {
	memset(G, -1, sizeof(G));
	int totState=1;
	for(int i=0; i<v.size(); i++) {
		string s=v[i];
		int state=0;
		for(int j=0; j<s.size(); j++) {
			int ch=ctoi(s[j]);
			if(G[state][ch]==-1) {
				G[state][ch]=totState;
				state=totState;
				totState++;
			} else{
				state=G[state][ch];
			}
			P[state]++;
		}
		O[state]=i;
		C[state]++;
	}
}


int match(string &s) {
	int state=0;
	for(int i=0; i<s.size(); i++) {
		int ch=ctoi(s[i]);
		if(G[state][ch]==-1) return 0;  //no state transition found
		state=G[state][ch];
	}

	return C[state];  // a prefix found (might not be entire word)
}


int main() {
	vector<string> v {"goku", "erza", "goten", "gogeta", "gohan", "gotenks", "err", "erya", "gohan", "gohan", 
		"gohan"};
	go(v);
	vector<string> q {"goku", "go", "got", "gote", "er", "gohan", "goh:"};
	for(int i=0; i<q.size(); i++) {
		cout<<match(q[i])<<endl;
	}
	return 0;
}
