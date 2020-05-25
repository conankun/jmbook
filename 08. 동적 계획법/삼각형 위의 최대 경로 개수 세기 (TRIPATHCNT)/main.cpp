#include <iostream>
#include <vector>
using namespace std;
int solve(const vector<vector<int>> &arr) {
    int n = arr.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n+1, 0));
    vector<vector<int>> cnt(n + 1, vector<int>(n+1, 1));
    int mx = 0, mx_cnt = 0;
    cnt[1][1] = 1;
    dp[1][1] = arr[1][1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dp[i-1][j-1] > dp[i-1][j]) {
                dp[i][j] = dp[i-1][j-1] + arr[i][j];
                cnt[i][j] = cnt[i-1][j-1];
            } else if(dp[i-1][j-1] < dp[i-1][j]) {
                dp[i][j] = dp[i-1][j] + arr[i][j];
                cnt[i][j] = cnt[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j-1] + arr[i][j];
                cnt[i][j] = cnt[i-1][j-1] + cnt[i-1][j];
            }

            if (mx < dp[i][j]) {
                mx = dp[i][j];
                mx_cnt = 0;
            }
            if (i == n && dp[i][j] == mx) {
                mx_cnt += cnt[i][j];
            }
        }
    }
    return mx_cnt;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<vector<int>> arr(n + 1, vector<int>(n+1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                cin>>arr[i][j];
            }
        }
        cout << solve(arr) << '\n';
    }
}