#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define N 3
#define MAX_STATE 999999
#define NUM(x) ((x) == '.' ? 0 : (x) == 'o' ? 1 : 2)
#define CHAR(x) ((x) == 1 ? 'o' : 'x')
#define NIL -1
using namespace std;
// 지금 수를 두는 사람이 지면 0, 비기면 1, 이기면 2
int cache[MAX_STATE];
inline int get_state(const vector<string> &grid) {
    int ret = 0, unit = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int now = NUM(grid[i][j]);
            ret += unit * now, unit *= 3;
        }
    }
    return ret;
}
inline int get_turn(const vector<string> &grid) {
    int cnt[] = {0, 0, 0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cnt[NUM(grid[i][j])]++;
        }
    }
    return cnt[1] >= cnt[2] ? 2 : 1;
}

inline bool is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}
inline bool has_win(const vector<string> &grid, const int x, const int y) {
    const int dx[] = {0, 1, 1, 1};
    const int dy[] = {1, 0, 1, -1};
    char ch = grid[y][x];
    if (ch == '.') return false;
    for (int k = 0; k < 4; k++) {
        int nx = x, ny = y;
        bool win = true;
        for (int iter = 0; iter < N - 1; iter++) {
            nx += dx[k], ny += dy[k];
            if (!is_valid(nx, ny) || grid[ny][nx] != ch) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
    return false;
}

// 지금 수를 두는 사람이 지면 0, 비기면 1, 이기면 2
inline int get_result(const vector<string> &grid, int turn) {
    int cnt[] = {0, 0, 0};
    int winner = NIL;
    for (int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cnt[NUM(grid[i][j])]++;
            if (has_win(grid, j, i)) {
                winner = NUM(grid[i][j]);
            }
        }
    }
    if (cnt[1] + cnt[2] == N * N) {
        return winner == NIL ? 1 : (winner == turn ? 2 : 0);
    }
    return winner == NIL ? NIL : (winner == turn ? 2 : 0);
}
int dp(vector<string> &grid) {
    int state = get_state(grid), &ret = cache[state];
    if (ret != NIL) return ret;
    int turn = get_turn(grid), res = get_result(grid, turn);
    if (res != NIL) {
        ret = res;
        return ret;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '.') {
                grid[i][j] = CHAR(turn);
                ret = max(ret, 2 - dp(grid));
                grid[i][j] = '.';
            }
        }
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    memset(cache, -1, sizeof(int) * MAX_STATE);
    int C;
    cin>>C;
    while(C--) {
        vector<string> grid(N);
        for (int i = 0; i < N; i++) cin>>grid[i];
        int result = dp(grid);
        if (!result) cout << CHAR(get_turn(grid) == 2 ? 1 : 2);
        else if (result == 1) cout << "TIE";
        else cout << CHAR(get_turn(grid));
        cout << '\n';
    }
}
