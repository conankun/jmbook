#include <iostream>
#include <vector>
using namespace std;
struct Bishops {
    int N, A, B;
    vector<vector<char>> grid;
    vector<vector<int>> adj;
    vector<int> a_matched, b_matched;
    vector<bool> visited;
    void input() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin>>grid[i][j];
            }
        }
    }
    inline bool valid(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N && grid[y][x] == '.';
    }
    void make_graph() {
        const int dx[] = {-1, 1};
        const int dy[] = {1, 1};
        int size[] = {0, 0};
        vector<vector<vector<int>>> diag(2, vector<vector<int>>(N, vector<int>(N, -1)));
        // 대각선 번호 추출.
        for (int k = 0; k < 2; k++) {
            int &num = size[k];
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (grid[i][j] == '.' && diag[k][i][j] == -1) {
                        int x = j, y = i;
                        while (valid(x,y)) {
                            diag[k][y][x] = num;
                            y += dy[k], x += dx[k];
                        }
                        num++;
                    }
                }
            }
        }
        // 이분 그래프 제작.
        A = size[0], B = size[1];
        adj = vector<vector<int>>(A, vector<int>(B, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '.') {
                    adj[diag[0][i][j]][diag[1][i][j]] = 1;
                }
            }
        }
    }

    bool dfs(int here) {
        if (visited[here]) return false;
        visited[here] = true;
        for (int b = 0; b < B; b++) {
            if (adj[here][b])
                if (b_matched[b] == -1 || dfs(b_matched[b])) {
                    // 증가 경로 찾음.
                    a_matched[here] = b;
                    b_matched[b] = here;
                    return true;
                }
        }
        return false;
    }
    int bipartite_matching() {
        a_matched = vector<int>(A, -1);
        b_matched = vector<int>(B, -1);
        int ret = 0;
        for (int start = 0; start < A; start++) {
            visited = vector<bool>(A, 0);
            if (dfs(start)) ++ret;
        }
        return ret;
    }
    int solve() {
        input();
        make_graph();
        return bipartite_matching();
    }
    Bishops(int N)
        : N(N), grid(N, vector<char>(N)) {}
};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--) {
        int n;
        cin>>n;
        Bishops bi(n);
        cout << bi.solve() << '\n';
    }
}
