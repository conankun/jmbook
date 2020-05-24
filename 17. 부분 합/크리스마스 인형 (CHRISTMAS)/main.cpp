#include <iostream>
#include <vector>
#define MOD 20091101
using namespace std;
void solve(int N, int K, const vector<int> &arr) {
    vector<int> count(K, 0);
    vector<int> mod_last_index(K, -1);
    vector<int> mx(N + 1, 0);
    count[0] = 1;
    mod_last_index[0] = 0;
    int sum = 0;
    int ans1 = 0;
    int ans2 = 0;
    for (int i = 1; i <= N; i++) {
        sum += arr[i];
        sum %= K;
        int mod = sum % K;
        {
            // problem 1
            ans1 += count[mod];
            ans1 %= MOD;
            count[mod]++;
        }
        if (mod_last_index[mod] != -1) {
            // problem 2
            int cnt = mx[mod_last_index[mod]] + 1;
            ans2 = max(ans2, cnt);
            mx[i] = cnt;
        }
        mx[i] = max(mx[i-1], mx[i]);
        mod_last_index[mod] = i;
    }
    cout << ans1 << ' ' << ans2 << '\n';
}
int main() {
    int T;
    cin>>T;
    while(T--) {
        int N,K;
        cin>>N>>K;
        vector<int> arr(N + 1);
        for (int i = 1; i <= N; i++) cin>>arr[i];
        solve(N,K, arr);
    }
}