#include <iostream>
#include <vector>
#define MOD 201
#define IND(k) ((k) % MOD)
using namespace std;
struct Food {
    int cost, val;
};
int solve(const vector<Food> &arr, int budget) {
    vector<int> dp(201, -1);
    int ret = 0;
    dp[0] = 0;
    for (int j = 1; j <= budget; j++) {
        int mx = 0;
        for (auto food : arr) {
            if (j - food.cost >= 0) {
                mx = max(mx, dp[IND(j - food.cost)] + food.val);
            }
        }
        dp[IND(j)] = mx;
    }
    for (int i = 0; i <= 200; i++) {
        if (ret < dp[i]) ret = dp[i];
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n,m;
        cin>>n>>m;
        m/=100;
        vector<Food> arr(n);
        for (int i = 0; i < n; i++) {
            cin>>arr[i].cost>>arr[i].val;
            arr[i].cost /= 100;
        }
        cout << solve(arr, m) << '\n';
    }
}
