#include <vector>

using namespace std;

// delete first occurance of x in v
template<class T> void delFirst(vector<T> &v, T x) {
	auto it=find(v.begin(), v.end(), x);
	if(it != v.end()) {
		v.erase(it);
	}
}

// delete all occurance of x in v
template<class T> void delAll(vector<T> &v, T x) {
	v.erase(remove(v.begin(), v.end(), x), v.end());
}

// delete all duplicates in v
template<class T> void delDup(vector<T> &v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
}
