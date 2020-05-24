#include <iostream>
#include <limits>
#include <vector>
#define NIL RangeResult(MAX_INT, MIN_INT)
using namespace std;
const int MIN_INT = numeric_limits<int>::min();
const int MAX_INT = numeric_limits<int>::max();

int find_tree_size(int n) {
    int m=1;
    while(m < n) m *=2;
    return 2*m;
}
struct RangeResult {
private:
    int mn,mx;
    void setMin(int k) {
        mn = min(k, mn);
    }
    void setMax(int k) {
        mx = max(k, mx);
    }
public:
    RangeResult(int mn, int mx) : mn(mn),mx(mx) {}
    int getMin() {
        return mn;
    }
    int getMax() {
        return mx;
    }
    void update(int k) {
        setMin(k);
        setMax(k);
    }
    void update(RangeResult res) {
        setMin(res.getMin());
        setMax(res.getMax());
    }
};
struct SegTree {
private:
    int n;
    int tree_size;
    vector<RangeResult> tree;
    RangeResult query(int left, int right, int node, int node_left, int node_right) {
        if (right < node_left || node_right < left) return NIL;
        if (left <= node_left && node_right <= right) {
            return tree[node];
        }
        int mid = (node_left + node_right) >> 1;
        RangeResult ls = query(left, right, node << 1, node_left, mid);
        RangeResult rs = query(left, right, (node << 1) + 1, mid + 1, node_right);
        return RangeResult(min(ls.getMin(), rs.getMin()), max(ls.getMax(), rs.getMax()));
    }
    RangeResult update(int pos, int k, int node, int node_left, int node_right) {
        if (pos < node_left || pos > node_right) {
            return NIL;
        }
        if (node_left == node_right) {
            tree[node].update(k);
            return tree[node];
        }
        int mid = (node_left + node_right) >> 1;
        auto left_result = update(pos,k,node<<1, node_left, mid);
        auto right_result = update(pos, k, (node << 1) + 1, mid + 1, node_right);
        tree[node].update(left_result);
        tree[node].update(right_result);
        return tree[node];
    }
public:
    RangeResult query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }
    void update(int pos, int k) {
        update(pos, k, 1, 0, n-1);
    }
    SegTree(int size)
        : n(size), tree_size(find_tree_size(n)), tree(vector<RangeResult>(tree_size, NIL)) {}
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N, Q;
        cin >> N >> Q;
        SegTree tree(N);
        vector<int> height(N+1);
        for (int i = 0; i < N; i++) {
            cin >> height[i];
            tree.update(i, height[i]);
        }
        for (int i = 0; i < Q; i++) {
            int l,r;
            cin>>l>>r;
            auto res = tree.query(l,r);
            cout << res.getMax() - res.getMin() << '\n';
        }
    }
}
