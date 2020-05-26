#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct Traversal {
    vector<int> post, in;
    int N;
    void input() {
        for (int i = 0; i < N; i++) {
            cin>>post[i];
        }
        for (int i = 0; i < N; i++) {
            cin>>in[i];
        }
    }
    void traverse(const vector<int> &post, const vector<int> &in) {
        int n = post.size(), m = in.size();
        if (!n || !m) return;
        int here = post[0];
        auto p = find(in.begin(), in.end(), here);
        int L = p - in.begin();
        // 왼쪽 서브트리
        traverse(vector<int>(post.begin() + 1, post.end()), vector<int>(in.begin(), p));
        // 오른쪽 서브트리
        traverse(vector<int>(post.begin() + 1 + L, post.end()), vector<int>(p + 1, in.end()));
        cout << here << ' ';
    }
    void solve() {
        input();
        traverse(post, in);
    }
    Traversal(int N) : N(N), post(N), in(N) {}
};
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        Traversal ts(N);
        ts.solve();
        cout << '\n';
    }
}