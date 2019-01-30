#include <queue>
#include <vector>
#include <string>
#include <iostream>
#define CLR(a) memset(a,0,sizeof(a))
#define SET(a) memset(a,-1,sizeof(a))
using namespace std;


const int X=2000000+5;  //total length of words
const int alp=62;  //total number of possible alphabets
int G[X][alp];  //fill with -1
int F[X];
vector<int>O[X];  //output function

int ctoi(char ch) {
	if(ch>='a' && ch<='z') return ch-'a';
	else if(ch>='0' && ch<='9') return 26+ch-'0';
	return 36+ch-'A';
}

void go(vector<string> &v, int G[][alp], vector<int> O[]) {
	memset(G, -1, sizeof(G));
	int totState=1;
	for(int i=0; i<v.size(); i++) {
		string s=v[i];
		int state=0;
		for(int j=0; j<s.size(); j++) {
			int ch=ctoi(s[j]);
			if(G[state][ch]!=-1) {
				state=G[state][ch];
			} else{
				G[state][ch]=totState;
				state=totState;
				totState++;
			}
		}
		O[state].push_back(i);
	}
	for(int i=0; i<alp; i++) {
		if(G[0][i]==-1) G[0][i]=0;
	}
}

void fail(int G[][alp], vector<int> O[], int F[]) {
	queue<int> q;
	for(int i=0; i<alp; i++) {
		if(G[0][i]!=0) {
			int s=G[0][i];
			q.push(s);
			F[s]=0;
		}
	}
	while(!q.empty()) {
		int top=q.front();
		q.pop();

		for(int i=0; i<alp; i++) {
			if(G[top][i]!=-1) {
				int s=G[top][i];
				q.push(s);
				int state=F[top];
				while(G[state][i]==-1) state=F[state];
				F[s]=G[state][i];
				if(G[F[s]][i]!=s) {   //avoid adding words that are prefix of another word
					for(int j=0; j<O[F[s]].size(); j++) {
						O[s].push_back(O[F[s]]   [j]);
					}
				}
			}
		}
	}
}

bool ok[1005];  //whether match found for word i

void match(string s, int G[][alp], int F[], vector<int> O[]) {
	int state=0;
	for(int i=0; i<s.size(); i++) {
		int ch=ctoi(s[i]);
		while(G[state][ch]==-1) state=F[state];
		state=G[state][ch];
		if(O[state].size()!=0) {
			for(int j=0; j<O[state].size(); j++) {
				//cout<<i<<" "<<O[state][j]<<endl;
				ok[O[state][j]]=1;
			}
		}
	}
}



int main() {
	string s, x;
	cin>>s;
	int totWords;
	cin>>totWords;
	vector<string> v;
	while(totWords--) {
		cin>>x;
		v.push_back(x);
	}

	SET(G);
	go(v, G, O);
	fail(G, O, F);
	match(s, G, F, O);

	return 0;
}
