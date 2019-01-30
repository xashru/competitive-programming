
// count number of set bits(1) in n
int popCount(int i) {
	i=i - ((i >> 1) & 0x55555555);
	i=(i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

//ietarte through all K-element subset of N element set
void iterate(int N, int K) {
	int k=-1;
	int s=(1 << k) - 1;
	while(!(s & 1 << 5)){
		// s has K elements
		int lo=s & ~(s - 1);
		int lz=(s + lo) & ~s;
		s|=lz;
		s&=~(lz - 1);
		if(lo==0) break;
		s|=(lz / lo / 2) - 1;
	}
}