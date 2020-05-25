#include <iostream>
#include <vector>
#define START_POINT (x == 0 && y == 0)
using namespace std;
void jlis(int x, int y, int last, int count, vector<vector<int>> &dp, const vector<int> &arr1, const vector<int> &arr2) {
    dp[x][y] = count;
    int n = arr1.size() - 1, m = arr2.size() - 1;
    for (int i = x + 1; i <= n; i++) {
        if ((START_POINT || arr1[i] > last) && (dp[i][y] < dp[x][y] + 1)) {
            jlis(i, y, arr1[i], dp[x][y] + 1, dp, arr1, arr2);
        }
    }
    for (int i = y + 1; i <= m; i++) {
        if ((START_POINT || arr2[i] > last) && (dp[x][i] < dp[x][y] + 1)) {
            jlis(x, i, arr2[i], dp[x][y] + 1, dp, arr1, arr2);
        }
    }
}
int solve(const vector<int> &arr1, const vector<int> &arr2) {
    int n = arr1.size() - 1, m = arr2.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(m+1, 0));
    jlis(0, 0, arr1[1], 0, dp, arr1, arr2);
    int ret = 0;
    for (int i = 0; i <= n; i++) for(int j = 0; j <= m; j++) ret = max(ret, dp[i][j]);
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int c;
    cin>>c;
    while(c--) {
        int n,m;
        cin>>n>>m;
        vector<int> arr1(n+1), arr2(m+1);
        for (int i = 1; i <= n; i++) cin>>arr1[i];
        for (int i = 1; i <= m; i++) cin>>arr2[i];
        cout << solve(arr1, arr2) << '\n';
    }
}
