#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#define FAST_IO cin.tie(0);ios::sync_with_stdio(0)
#define SIZE(i,j) (i-j+1)
#define SQSUM(i,j) (psq[i] - psq[j-1])
#define SUM(i,j) (ps[i] - ps[j-1])
#define ROUNDUP(i,j) (2*(SUM(i,j) % SIZE(i,j)) > SIZE(i,j) ? 1 : 0)
#define MINIMIZER(i,j) ((int)(SUM(i,j)/SIZE(i,j)) + ROUNDUP(i,j))
#define ERR(i,j) (SQSUM(i,j) - 2 * MINIMIZER(i,j) * SUM(i,j) + SIZE(i,j) * MINIMIZER(i,j) * MINIMIZER(i,j))
using namespace std;
const int SUP = numeric_limits<int>::max();
int solve(const vector<int> &arr, int s) {
    int n = arr.size() - 1;
    vector<vector<int>> dp(s + 1, vector<int>(n+1, SUP));
    vector<int> ps(n + 1, 0);
    vector<int> psq(n+1, 0);
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i-1] + arr[i];
        psq[i] = psq[i-1] + arr[i]*arr[i];
    }
    dp[0][0] = 0;
    int ret = SUP;
    for (int k = 1; k <= s; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = i; j >= k; j--) {
                if (dp[k-1][j-1] != SUP) {
                    dp[k][i] = min(dp[k][i], dp[k - 1][j - 1] + ERR(i, j));
                }
            }
        }
        ret = min(ret, dp[k][n]);
    }
    return ret;
}
int main() {
    FAST_IO;
    int C;
    cin>>C;
    while(C--) {
        int n, s;
        cin>>n>>s;
        vector<int> arr(n+1);
        for (int i = 1; i <= n; i++) cin>>arr[i];
        sort(arr.begin() + 1, arr.end());
        cout << solve(arr, s) << '\n';
    }
}