#include <algorithm>
#include <iostream>
#include <vector>
#define VC vector<char>
#define VVC vector<VC>
#define VB vector<bool>
#define VVB vector<VB>
using namespace std;
const int polys[4][3][2] = {
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {0, 1}, {1, 0}},
    {{0,0}, {-1,1}, {0,1}},
    {{0,0}, {0, 1}, {1, 1}}};

struct BoardCover {
    VVC grid;
    VVB vis;
    int H, W, empty, ans;
    void input() {
        for (int i = 1;i <= H; i++) for (int j = 1; j <= W; j++) {
            cin>>grid[i][j];
            if (grid[i][j] == '.') empty++;
        }
    }

    inline bool valid_cell(const int x, const int y) const {
        return (x > 0) && (x <= W) && (y > 0) && (y <= H) && grid[y][x] == '.' && !vis[y][x];
    }

    bool valid(int x, int y, int poly_num) {
        auto poly = polys[poly_num];
        bool valid = true;
        for (int j = 0; j < 3; j++) {
            auto tile = poly[j];
            int nx = x + tile[0], ny = y + tile[1];
            valid &= valid_cell(nx, ny);
        }
        return valid;
    }

    void set(int x, int y, int poly_num, int val) {
        auto poly = polys[poly_num];
        for (int j = 0; j < 3; j++) {
            auto tile = poly[j];
            int nx = x + tile[0], ny = y + tile[1];
            vis[ny][nx] = val;
        }
    }

    pair<int,int> next() {
        bool found = false;
        int y=1, x=1;
        for (int i = 1; i <= H; i++) {
            for (int j = 1; j <= W; j++) {
                if (grid[i][j] == '.' && !vis[i][j]) {
                    found = true, y = i, x = j;
                    break;
                }
            }
            if (found) break;
        }
        return {x, y};
    }

    int test = 0;
    void count(int covered) {
        if (covered == empty) {
            ans++;
            return;
        }

        auto tmp = next();
        int x = tmp.first, y = tmp.second;

        for (int i = 0; i < 4; i++) {
            if (valid(x, y, i)) {
                set(x, y, i, 1);
                count(covered + 3);
                set(x, y, i, 0);
            }
        }
    }
    int solve() {
        if (empty % 3) return 0;
        count(0);
        return ans;
    }
    BoardCover(int H, int W)
        : H(H), W(W), empty(0), ans(0), grid(H + 2, VC(W + 2, '#')), vis(H + 2, VB(W + 2, 0)){}
};
int main() {
    int C;
    cin>>C;
    while(C--) {
        int H, W;
        cin>>H>>W;
        BoardCover bc(H, W);
        bc.input();
        cout << bc.solve() << '\n';
    }
}
