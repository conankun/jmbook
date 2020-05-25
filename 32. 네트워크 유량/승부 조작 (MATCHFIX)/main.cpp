#include <iostream>
#include <queue>
#include <vector>
#define SOURCE 0
#define SINK 1
#define EDGE_IND(x) ((x) + 2)
#define VERTEX_IND(y) ((y) + 2 + M)
#define SIZE N + M + 2
#define NIL -1
using namespace std;
const int INF = 1e9;
struct MatchFix {
    int N, M, ans, cnt;
    vector<int> wins;
    vector<vector<int>> res;
    void update_graph(int win) {
        res[VERTEX_IND(0)][SINK] = 0;
        for (int i = 1; i < N; i++) {
            res[VERTEX_IND(i)][SINK] = win - 1 - wins[i];
        }
    }
    void update_graph() {
        for (int i = 0; i < N; i++) {
            res[VERTEX_IND(i)][SINK]++;
        }
    }
    void input() {
        for (int i = 0; i < N; i++) {
            cin>>wins[i];
        }
        update_graph(wins[0]);
        for (int i = 0; i < M; i++) {
            int a,b;
            cin>>a>>b;
            if (a > b) swap(a, b);
            if (!a) cnt++;
            res[SOURCE][EDGE_IND(i)] = 1;
            res[EDGE_IND(i)][VERTEX_IND(a)] = 1;
            res[EDGE_IND(i)][VERTEX_IND(b)] = 1;
        }
    }
    int augment(int node, int min_weight, const vector<int> &parent) {
        if (node == SOURCE) return min_weight;
        else if(parent[node] != NIL) {
            int p = parent[node], f = augment(p, min(min_weight, res[p][node]), parent);
            res[p][node] -= f, res[node][p] += f;
            return f;
        }
        return 0;
    }
    bool bfs() {
        vector<int> vis(SIZE, false);
        vector<int> parent(SIZE, NIL);
        queue<int> qu;
        qu.push(SOURCE), vis[SOURCE] = 1;
        bool found = 0;
        while (!qu.empty()) {
            int here = qu.front(); qu.pop();
            if (here == SINK) {
                found = 1; break;
            }
            for (int next = 0; next < SIZE; next++) {
                if (res[here][next] > 0 && !vis[next]) {
                    qu.push(next); vis[next] = 1, parent[next] = here;
                }
            }
        }
        if (found) ans += augment(SINK, INF, parent);
        return found;
    }
    void flow() {
        while(bfs());
    }

    bool is_first_rank(int win) {
        for (int i = 1; i < N; i++) {
            if (wins[i] >= win) return false;
        }
        return true;
    }

    int solve() {
        input();
        update_graph(wins[0]);
        for (int win = wins[0]; win <= wins[0] + cnt; win++) {
            flow();
            update_graph();
            if (ans == M && is_first_rank(win)) return win;
        }
        return -1;
    }
    MatchFix(int N, int M)
        : cnt(0), ans(0), N(N), M(M), wins(N), res(M + N + 2, vector<int>(M + N + 2, 0)) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N, M;
        cin>>N>>M;
        MatchFix mf(N, M);
        cout << mf.solve() << '\n';
    }
}
