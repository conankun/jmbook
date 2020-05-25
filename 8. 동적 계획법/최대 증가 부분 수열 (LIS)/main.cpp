#include <iostream>
#include <vector>
using namespace std;
int main() {
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<int> arr(n+1);
        vector<int> dp(n+1, 0);
        for (int i = 1; i <= n; i++) cin >> arr[i];
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (arr[j] < arr[i]) dp[i] = max(dp[i], dp[j] + 1);
            }
            ans = max(ans, dp[i]);
        }
        cout << ans << '\n';
    }
}
