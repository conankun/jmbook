#include <algorithm>
#include <iostream>
#include <vector>
#define SQ(x) ((x) * (x))
using namespace std;
struct Circle {
    int x, y, r, ind;
    Circle(int x, int y, int r) : x(x), y(y), r(r) {}
    Circle() {}
    // c 가 현재 원에 포함되는지 확인
    bool inside(Circle c) {
        return SQ(c.x - x) + SQ(c.y - y) < r * r && r > c.r;
    }
    bool operator<(const Circle &c) const {
        return r < c.r;
    }
};
struct Fortress {
    int N;
    vector<Circle> circles;
    vector<vector<int>> adj;
    int ans, root;
    void input() {
        for (int i = 0; i < N; i++) {
            cin>>circles[i].x>>circles[i].y>>circles[i].r;
            circles[i].ind = i;
        }
    }
    void make_graph() {
        // 반지름 순으로 정렬
        sort(circles.begin(), circles.end());
        // i를 포함하는 가장 작은 원 j를 찾는다.
        for (int i = 0; i < N; i++) {
            if (!circles[i].ind) root = i;
            for (int j = i + 1; j < N; j++) {
                if (circles[j].inside(circles[i])) {
                    adj[j][i] = 1; break;
                }
            }
        }
    }
    // here 의 서브트리중 가장 깊은 깊이를 반환.
    int find(int here) {
       vector<int> depths;
       for (int next = 0; next < N; next++) {
           if (adj[here][next]) {
               depths.emplace_back(find(next));
           }
       }
       // 리프이면 서브트리의 최대 깊이는 depth.
       if (depths.empty()) return 1;
       // O(n) 만에 가장 깊이가 큰 두 점을 고를 수 있지만 귀찮으므로 그냥 정렬한다.
       sort(depths.begin(), depths.end());
       if (depths.size() == 1) ans = max(ans, depths.front());
       else ans = max(ans, depths.back() + depths[depths.size() - 2]);
       return depths.back() + 1;
    }
    void solve() {
        input();
        make_graph();
        find(root);
        cout << ans << '\n';
    }
    Fortress(int N) : ans(0), N(N), circles(N), adj(N, vector<int>(N, 0)) {}
};
int main() {
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        Fortress ft(N);
        ft.solve();
    }
}