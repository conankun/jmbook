#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define NIL -1
#define MAX_STATE 1<<25
#define N 5
#define CELL(x,y) (1 << ((y) * N + (x)))
using namespace std;
char cache[MAX_STATE];
vector<int> blocks;
void preprocess() {
    // L자 블럭
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            vector<int> cells;
            for (int dy = 0; dy < 2; dy++) {
                for (int dx = 0; dx < 2 ;dx++) {
                    cells.emplace_back(CELL(j + dx, i + dy));
                }
            }
            int square = cells[0] + cells[1] + cells[2] + cells[3];
            for (int k = 0; k < cells.size(); k++) {
                blocks.emplace_back(square - cells[k]);
            }
        }
    }
    // 일자 블럭
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j < N - 1) blocks.emplace_back(CELL(j, i) + CELL(j + 1, i));
            if (i < N - 1) blocks.emplace_back(CELL(j, i) + CELL(j, i + 1));
        }
    }
}
int get_state(const vector<string> &grid) {
    int ret = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == '#') ret += CELL(j, i);
        }
    }
    return ret;
}
char game(int state) {
    char &ret = cache[state];
    if (ret != NIL) return ret;
    ret = 0;
    for (int i = 0; i < blocks.size(); i++) {
        if (!(state & blocks[i])) {
            ret = !game(state | blocks[i]);
            if (ret) break;
        }
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    memset(cache, NIL, sizeof(char) * MAX_STATE);
    vector<string> grid(N);
    preprocess();
    while(C--) {
        for (int i = 0; i < N;i ++) cin>>grid[i];
        int state = get_state(grid);
        cout << (game(state) ? "WINNING" : "LOSING") << '\n';
    }
}
