#include <algorithm>
#include <iostream>
#include <vector>
#define solve(s,e) ans[r[s]][r[e]]
#define MAXN 500
#define INF 1000000000
using namespace std;
int dp[MAXN + 1][MAXN + 1]={-1};
int ans[MAXN + 1][MAXN + 1];
int delay[MAXN + 1];
int w[MAXN + 1];
int r[MAXN + 1];
void floyd(const int V) {
    for (int k = 1; k <= V; k++) {
        for (int i = 1; i <= V; i++) {
            if (dp[i][k] == INF) continue;
            for (int j = 1; j <= V; j++) {
                dp[i][j] = min(dp[i][k] + dp[k][j], dp[i][j]);
                ans[i][j] = min(dp[i][j] + delay[w[k]], ans[i][j]);
            }
        }
    }
}
void init() {
    for (int i = 1; i <= MAXN; i++) {
        dp[i][i] = 0, ans[i][i] = 0;
        for(int j = 1; j <= MAXN; j++) if (i != j) dp[i][j] = INF, ans[i][j] = INF;
    }
}
void sort(const int V) {
    vector<int> ind(V + 1);
    for (int i = 1; i <= V; i++) ind[i] = i;
    sort(ind.begin() + 1, ind.end(), [](int i, int j) {
        return delay[i] < delay[j];
    });
    for (int i = 1; i <= V; i++) w[i] = ind[i], r[ind[i]] = i;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    int V, E, T;
    cin >> V >> E;
    for (int i = 1; i <= V; i++) cin>>delay[i];
    sort(V);
    for (int i = 0; i < E; i++) {
        int a,b,c;
        cin>>a>>b>>c;
        ans[r[a]][r[b]] = dp[r[a]][r[b]] = min(dp[r[a]][r[b]], c);
        ans[r[b]][r[a]] = dp[r[b]][r[a]] = min(dp[r[b]][r[a]], c);
    }
    floyd(V);
    cin>>T;
    while(T--) {
        int s,e;
        cin>>s>>e;
        cout << solve(s,e) << '\n';
    }
}
