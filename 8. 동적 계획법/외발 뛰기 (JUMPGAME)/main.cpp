#include <iostream>
#include <vector>
using namespace std;
int solve(const vector<vector<int>> &mp) {
    int n = mp.size() - 1;
    vector<vector<int>> discovered(n + 1, vector<int>(n + 1, 0));
    discovered[1][1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int step = mp[i][j];
            if (i + step <= n) {
                discovered[i+step][j] = max(discovered[i+step][j], discovered[i][j]);
            }
            if (j + step <= n) {
                discovered[i][j + step] = max(discovered[i][j + step], discovered[i][j]);
            }
        }
    }
    return discovered[n][n];
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<vector<int>> mp(n + 1, vector<int>(n+1));
        for (int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) cin>>mp[i][j];
        cout << (solve(mp) ? "YES" : "NO") << '\n';
    }
}