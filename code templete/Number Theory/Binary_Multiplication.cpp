int BinMul(long long a, long long b, long long mod) {
	int ans = 0;
	while (b) {
		if (b & 1) ans = (ans + a) % mod;
		a = (a + a) % mod;
		b >>= 1;
	}
	return ans;
}