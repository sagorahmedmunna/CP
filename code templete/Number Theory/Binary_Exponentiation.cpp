int BinExp(long long a, long long b, int mod) {
	int ans = 1;
	while (b) {
		if (b & 1) ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}