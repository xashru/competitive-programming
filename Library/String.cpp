#include <vector>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

vector<string> split(string s, char delim) {
	vector<string> v;
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		v.push_back(item);
	}
	return v;
}

vector<int> splitI(string s, char delim) {
	vector<int> v;
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		v.push_back(stoi(item));
	}
	return v;
}

vector<int> split(string str) {
	istringstream iss(str);
	vector<int> v;
	string buf;
	stringstream ss(str);
	while(ss >> buf)
		v.push_back(stoi(buf));
	return v;
}

// generate all possible binary ('0' or '1') strings of length n
vector<string> getBinary(int n)
{
	string s="";
	for(int i=0; i<n; i++) s+="0";
	vector<string> v;
	v.push_back(s);
	queue<string> q;
	q.push("1");
	n=1<<n;
	n--;
	while(n--)
	{
		string s1=q.front();
		q.pop();
		string s3=s1;
		string s2=s1;
		q.push(s1.append("0"));
		q.push(s2.append("1"));
		s3.insert(0, s.substr(0, s.size()-s3.size()));
		v.push_back(s3);
	}
	return v;
}

// check if a character ch is present in s
bool present(string s, char ch) {
	int n=s.size();
	for(int i=0; i<n; i++) {
		if(s[i]==ch) return true;
	}
	return false;
}

// count number of occurance of substring sub in string str
int countSubstring(string str, string sub) {
	if(sub.length() == 0) return 0;
	int count=0;
	for(size_t offset=str.find(sub); offset != std::string::npos;
		offset=str.find(sub, offset + sub.length())){
		++count;
	}
	return count;
}

// replace ALL occurance of a substring in string s
void replaceAll(string &s, string sub, string rep) {
	size_t index=0;
	size_t n=sub.size(), m=rep.size();
	while(true) {
		index=s.find(sub, index);
		if(index == string::npos) break;
		s.replace(index, n, rep);
		index+=m;
	}
}
// to_string
string tos(int a) {
	stringstream ss;
	ss << a;
	string str=ss.str();
	return str;
}