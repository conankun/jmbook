#include <cstring>
#include <iostream>
#include <vector>
#define MAXN 100
#define MOD 10000000
#define COUNT(t, b) ((t) + (b) - 1)
using namespace std;
int cache[MAXN + 1][MAXN + 1], n;
int poly(const int k, const int t) {
    if (k == 0) {
        return cache[k][t] = 1;
    }
    int &ret = cache[k][t];
    if (ret) return ret;
    for (int b = 1; b <= k; b++) {
        ret += COUNT(t, b) * poly(k - b, b);
        ret %= MOD;
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        memset(cache, 0, sizeof(int) * (MAXN + 1) * (MAXN + 1));
        cin>>n;
        int sum = 0;
        for (int i = 1; i <= n; i++) sum += poly(n - i, i);
        sum %= MOD;
        cout << sum << '\n';
    }
}
