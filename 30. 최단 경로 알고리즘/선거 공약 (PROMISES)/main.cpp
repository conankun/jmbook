#include <iostream>
#include <vector>
#define MAKE(s,e,c) dp[s][e] = min(dp[s][e], c); dp[e][s] = min(dp[e][s], c);
using namespace std;
const int INF = 1e9;
struct Promise {
    vector<vector<int>> dp;
    int V, M, N;
    void floyd() {
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
    }
    void input() {
        for (int i = 0; i < M; i++) {
            int a,b,c;
            cin>>a>>b>>c;
            MAKE(a, b, c);
        }
        for (int i = 0 ; i < V; i++) dp[i][i] = 0;
    }
    bool update(int s, int e, int c) {
        if (dp[s][e] <= c) return false;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dp[i][j] > dp[i][s] + c + dp[e][j]) {
                    dp[i][j] = dp[i][s] + c + dp[e][j];
                }
                if (dp[i][j] > dp[i][e] + c + dp[s][j]) {
                    dp[i][j] = dp[i][e] + c + dp[s][j];
                }
            }
        }
        return true;
    }
    int query() {
        int cnt = 0;
        for (int t = 0; t < N; t++) {
            int s,e,c;
            cin>>s>>e>>c;
            cnt += !update(s,e,c);
        }
        return cnt;
    }
    int solve() {
        input();
        floyd();
        return query();
    }
    Promise(int V,int M, int N) : V(V), M(M), N(N), dp(V, vector<int>(V, INF)) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int V,M,N;
        cin>>V>>M>>N;
        Promise p(V, M, N);
        cout << p.solve() << '\n';
    }
}