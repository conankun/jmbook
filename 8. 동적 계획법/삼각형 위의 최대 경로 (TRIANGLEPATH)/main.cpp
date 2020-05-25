#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<vector<int>> arr(n+1, vector<int>(n+1));
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= i; j++) {
                cin>>arr[i][j];
            }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + arr[i][j];
                if (i == n && ans < dp[i][j]) ans = dp[i][j];
            }
        }
        cout << ans << '\n';
    }
}
