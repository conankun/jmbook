#include <iostream>
#include <vector>
#define BLACK(i,j) (((i) + (j)) % 2 == 0)
#define NIL -1
#define EMPTY '.'
using namespace std;
struct TrapCard {
    vector<vector<char>> grid;
    vector<vector<int>> node, adj;
    vector<int> a_matched, b_matched;
    vector<bool> a_chosen, b_chosen, visited;
    int H, W, N, M, total;
    void input() {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                cin>>grid[i][j];
                if (grid[i][j] == EMPTY) total++;
            }
        }
    }
    inline bool valid(int x, int y) {
        return x >= 0 && x < W && y >= 0 && y < H && grid[y][x] == EMPTY;
    }
    void make_graph() {
        int n = 0, m = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (grid[i][j] != EMPTY) continue;
                if (BLACK(i,j)) {
                    node[i][j] = n++;
                } else {
                    node[i][j] = m++;
                }
            }
        }
        N = n, M = m;
        adj = vector<vector<int>>(n, vector<int>(m, 0));
        const int dx[] = {0, 0, 1, -1};
        const int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (!BLACK(i,j) || grid[i][j] != EMPTY) continue;
                for (int k = 0; k < 4; k++) {
                    int ny = i + dy[k], nx = j + dx[k];
                    if (valid(nx, ny)) {
                        adj[node[i][j]][node[ny][nx]] = 1;
                    }
                }
            }
        }
    }
    bool dfs(int here) {
        if (visited[here]) return false;
        visited[here] = true;
        for (int i = 0; i < M; i++) {
            if (adj[here][i]) {
                int next = b_matched[i];
                if (next == NIL || dfs(next)) {
                    a_matched[here] = i;
                    b_matched[i] = here;
                    return true;
                }
            }
        }
        return false;
    }
    int bipartite() {
        a_matched = vector<int>(N, NIL), b_matched = vector<int>(M, NIL);
        int ret = 0;
        for (int i = 0; i < N; i++) {
            visited = vector<bool>(N, 0);
            if (dfs(i)) ret++;
        }
        return ret;
    }
    void find_independent_set() {
        a_chosen = vector<bool>(N, 1), b_chosen = vector<bool>(M, 0);
        for (int i = 0; i < M; i++) if (b_matched[i] == NIL) b_chosen[i] = 1;
        while (true) {
            bool updated = false;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (a_chosen[i] && b_chosen[j] && adj[i][j]) {
                        a_chosen[i] = false;
                        b_chosen[a_matched[i]] = true;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
    };
    void print(int mvc) {
        cout << total - mvc << '\n';
        find_independent_set();
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (grid[i][j] != EMPTY) cout << '#';
                else if (BLACK(i,j)) {
                    if(a_chosen[node[i][j]]) cout << '^';
                    else cout << '.';
                } else {
                    if (b_chosen[node[i][j]]) cout << '^';
                    else cout << '.';
                }
            }
            cout << '\n';
        }
    }
    void solve() {
        input();
        make_graph();
        print(bipartite());
    }
    TrapCard(int H, int W) : total(0), H(H), W(W), grid(H, vector<char>(W)), node(H, vector<int>(W)){}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int H, W;
        cin>>H>>W;
        TrapCard tc(H, W);
        tc.solve();
    }
}
