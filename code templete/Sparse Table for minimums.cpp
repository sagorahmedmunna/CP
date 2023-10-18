const int N = 2e5 + 10;
const int LOG = 18;
int table[N][LOG];
int a[N];
int n;

void sparse() {
    for (int i = 0; i < n; i++) table[i][0] = a[i];
    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            table[i][j] = min(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    int log = __lg(r - l + 1);
    return min(table[l][log], table[r - (1 << log) + 1][log]);
}