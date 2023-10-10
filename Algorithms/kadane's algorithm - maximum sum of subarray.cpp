for (auto& i : a) {
    sum += i;
    ans = max(ans, sum);
    sum = max(sum, 0);
}