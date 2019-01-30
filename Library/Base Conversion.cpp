#include <iostream>
#include <string>

using namespace std;

//base <10, change (n[i]-'0') to approate decoding for higher base
long long toDecimal(string n, long long b){
	long long result=0;
	long long multiplier=1;
	for(int i=sz(n) - 1; i >= 0; i--) {
		result+=(long long)(n[i]-'0') * multiplier;
		multiplier*=b;
	}
	return result;
}


template<class T> string fromDecimal(T n, int b) {
   string chars="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   string result="";
   while(n>0) {
      result=chars[n%b] + result;
      n/=b;
   }
   return result;
}
