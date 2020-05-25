#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define START 0
#define END (N-1)
using namespace std;
const int INF = 1e9;
struct Edge {
    int s, e, c;
    Edge (int s, int e, int c) : s(s), e(e), c(c) {}
    bool operator<(const Edge &edge) const {
        return c < edge.c;
    }
};
struct TPath {
    int N, M;
    vector<vector<Edge>> adj;
    void input() {
        for (int i = 0; i < M; i++) {
            int a,b,c;
            cin>>a>>b>>c;
            adj[a].push_back(Edge(a,b,c));
            adj[b].push_back(Edge(b,a,c));
        }
    }
    bool has_path(int lo, int hi) {
        vector<bool> vis(N, 0);
        queue<int> qu;
        qu.push(START); vis[START] = 1;
        while (!qu.empty()) {
            int here = qu.front(); qu.pop();
            if (here == END) return true;
            for (auto tmp : adj[here]) {
                int next = tmp.e, cost = tmp.c;
                if (lo <= cost && cost <= hi && !vis[next]) {
                    qu.push(next); vis[next] = true;
                }
            }
        }
        return false;
    }
    int two_pointer() {
        int ans = INF;
        int hi = 0;
        for (int lo = 0; lo <= 1000; lo++) {
            for (; hi <= 1000 && lo <= hi; hi++) {
                if (has_path(lo, hi)) {
                    ans = min(hi-lo, ans);
                    break;
                }
            }
        }
        return ans;
    }
    int solve() {
        input();
        return two_pointer();
    }
    TPath(int N, int M) : N(N), M(M), adj(N) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N, M;
        cin>>N>>M;
        TPath tp(N, M);
        cout << tp.solve() << '\n';
    }
}
