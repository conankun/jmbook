#include <algorithm>
#include <iostream>
#include <vector>
#define NIL -1
#define BETTER(bf, now) ((bf) == -1 || (now) < (bf))
using namespace std;
typedef pair<int,int> pii;
struct FireTrucks {
    int V, E, n, m;
    vector<vector<int>> adj;
    vector<int> fire, stn;
    void input() {
        for (int i = 0; i < E; i++) {
            int a,b,c;
            cin>>a>>b>>c;
            adj[a][b] = c;
            adj[b][a] = c;
        }
        for (int i = 0; i < n; i++) cin>>fire[i];
        for (int i = 0; i < m; i++) {
            cin>>stn[i];
            adj[0][stn[i]] = 0;
        }
    }
    int solve() {
        vector<int> dp(V + 1, -1);
        vector<int> covered(V+1, false);
        int here = 0;
        dp[0] = 0;
        for (int i = 0; i < V; i++) {
            covered[here] = true;
            int next = here, mx = -1;
            for (int j = 1; j <= V; j++) {
                if (adj[here][j] != NIL && BETTER(dp[j], dp[here] + adj[here][j])) {
                    dp[j] = dp[here] + adj[here][j];
                }
                if (!covered[j] && (mx == NIL || (dp[j] != -1 && mx > dp[j]))) mx = dp[j], next = j;
            }
            here = next;
        }
        int sum = 0;
        for (int f : fire) {
            sum += dp[f];
        }
        return sum;
    }
    FireTrucks(int V, int E, int n, int m) : V(V), E(E), n(n), m(m), adj(V + 1, vector<int>(V + 1, -1)), fire(n), stn(m) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int V, E, n, m;
        cin>>V>>E>>n>>m;
        FireTrucks ft(V, E, n, m);
        ft.input();
        cout << ft.solve() << '\n';
    }
}
