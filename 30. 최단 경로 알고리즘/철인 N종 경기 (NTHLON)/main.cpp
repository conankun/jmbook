#include <iostream>
#include <string>
#include <vector>
#define IND(x) ((x) + 200)
#define MAXN 500
#define START IND(0)
#define GOAL IND(0)
#define N 401
using namespace std;
struct Edge {
    int a, b;
    Edge(int a, int b) : a(a), b(b) {}
};
const int INF = 1e9;
struct Nthlon {
    int M;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> dp;
    vector<bool> vis;
    void make_graph() {
        for (int here = -200; here <= 200; here++) {
            for (auto edge : edges) {
                int next = here + edge.a - edge.b;
                if (next >= -200 && next <= 200) {
                    adj[IND(here)][IND(next)] = min(adj[IND(here)][IND(next)], edge.a);
                }
            }
        }
    }
    void input() {
        for (int i = 0; i < M; i++) {
            int a,b; cin>>a>>b;
            edges.push_back(Edge(a,b));
        }
    }
    void relax(int here, int next, int dis) {
        dp[next] = min(dp[next], dis + adj[here][next]);
    }

    int find_min() {
        int dist = INF, ret = -1;
        for (int i = 0; i < N; i++) {
            if (dist > dp[i] && !vis[i]) {
                dist = dp[i], ret = i;
            }
        }
        return ret;
    }
    int dijkstra() {
        for (int i = 0; i < N; i++) relax(START, i, 0);
        for (int i = 0; i < N; i++) {
            int here = find_min();
            if (here == -1) break; vis[here] = true;
            for (int j = 0; j < N; j++) relax(here, j, dp[here]);
        }
        return dp[GOAL];
    }
    int solve() {
        input();
        make_graph();
        return dijkstra();
    }
    Nthlon(int M) : M(M), adj(MAXN, vector<int>(MAXN, INF)), dp(MAXN, INF), vis(MAXN, 0) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int M;
        cin>>M;
        Nthlon nt(M);
        auto res = nt.solve();
        cout << (res == INF ? "IMPOSSIBLE" : to_string(res)) << '\n';
    }
}
