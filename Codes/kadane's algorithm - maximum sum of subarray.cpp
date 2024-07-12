long long sum = 0, ans = 0;
for (auto& ai : a) {
	sum += ai;
	ans = max(ans, sum);
	sum = max(sum, 0);
}