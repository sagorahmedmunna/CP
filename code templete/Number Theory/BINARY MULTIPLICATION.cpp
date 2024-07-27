int BinMul(long long a, long long b, long long mod) {
	int res = 0;
	while (b) {
		if (b & 1) res = (res + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return res;
}