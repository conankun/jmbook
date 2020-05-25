#include <iostream>
#include <vector>
using namespace std;
typedef vector<pair<int,int>> vpii;
typedef vector<vpii> vvpii;
const int INF = 1e9;
const string text[2] = {"INFINITY", "UNREACHABLE"};
string bellmanford(const int V, const vvpii &adj, int mul) {
    vector<int> cnt(V, 0);
    vector<int> dp(V, INF);
    dp[0] = 0; cnt[0] = 1;
    bool is_infinity = false;
    for (int t = 1; t <= 2*V; t++) {
        for (int here = 0; here < V; here++) {
            if (dp[here] == INF) continue;
            for (int j = 0; j < adj[here].size(); j++) {
                int next = adj[here][j].first, cost = adj[here][j].second;
                if (dp[next] > dp[here] + cost) {
                    if (t >= V && next == 1) is_infinity = true;
                    dp[next] = dp[here] + cost;
                    cnt[next]++;
                }
            }
        }
    }
    if (!cnt[1]) return text[1];
    if (is_infinity) return text[0];
    return to_string(dp[1] * mul);
}

vvpii rev(const int V, const vvpii &adj) {
    vvpii ret(adj);
    for (int i = 0; i < V; i++) for (int j = 0; j < ret[i].size(); j++) ret[i][j].second *= -1;
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int V, W;
        cin>>V>>W;
        vvpii adj(V);
        for (int i = 0; i < W; i++) {
            int a,b,c;
            cin>>a>>b>>c;
            adj[a].push_back({b,c});
        }
        auto res1 = bellmanford(V, adj, 1);
        auto res2 = bellmanford(V, rev(V, adj), -1);
        if (res1 == text[1] || res2 == text[1]) cout << text[1];
        else cout << res1 << " " << res2;
        cout << '\n';
    }
}