#include <iostream>
#include <vector>
using namespace std;
struct Picnic {
    vector<vector<bool>> adj;
    vector<bool> vis;
    int n;
    void input() {
        int m;
        cin>>m;
        while(m--) {
            int a,b;
            cin>>a>>b;
            adj[a][b] = 1;
            adj[b][a] = 1;
        }
    }
    int count(int here, int match) {
        if (match * 2 == n) {
            return 1;
        }
        int cnt = 0;
        for (int i = here + 1; i < n; i++) {
            if (vis[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (!vis[j] && adj[i][j]) {
                    vis[i] = true, vis[j] = true;
                    cnt += count(i, match + 1);
                    vis[i] = false, vis[j] = false;
                }
            }
        }
        return cnt;
    }

    int solve() {
        return count(-1, 0);
    }
    Picnic(int n) : n(n), adj(n, vector<bool>(n, 0)), vis(n) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        Picnic pic(n);
        pic.input();
        cout << pic.solve() << '\n';
    }
}
