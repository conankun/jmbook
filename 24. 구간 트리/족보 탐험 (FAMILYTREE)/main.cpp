#include <iostream>
#include <vector>
#define NIL -1
using namespace std;

struct SegTree {
private:
    vector<int> tree;
    int n;
    int update(int pos, int k, int node, int node_left, int node_right) {
        if (pos < node_left || pos > node_right) {
            return tree[node];
        }
        if (node_left == node_right) {
            tree[node] = k;
            return tree[node];
        }
        int mid = (node_left + node_right) >> 1;
        int left = update(pos, k, node << 1, node_left, mid);
        int right = update(pos, k, (node << 1) + 1, mid + 1, node_right);
        tree[node] = max(left, right);
        return tree[node];
    }
    int query(int left, int right, int node, int node_left, int node_right) const {
        if (right < node_left || left > node_right) {
            return NIL;
        }
        if (left <= node_left && node_right <= right) {
            return tree[node];
        }
        int mid = (node_left + node_right) >> 1;
        int left_res = query(left, right, node << 1, node_left, mid);
        int right_res = query(left, right, (node<<1) + 1, mid + 1, node_right);
        return max(left_res, right_res);
    }
public:
    void update(int pos, int k) {
        update(pos,k,1,0,n-1);
    }
    int query(int left, int right) const {
        return query(left, right, 1, 0, n-1);
    }
    SegTree(int size) : n(size), tree(size * 4, -1) {}
};

void get_post_number(int here, int depth, vector<int> &post_num, vector<int> &depths, const vector<vector<int>> &adj) {
    static int counter = 0;
    depths[here] = depth;
    for (int there : adj[here]) {
        get_post_number(there, depth + 1, post_num, depths, adj);
    }
    post_num[here] = ++counter;
}
void flatten_tree(int here, vector<pair<int,int>> &loc, vector<int> &arr, const vector<vector<int>> &adj) {
    loc[here].first = arr.size();
    for (int i = 0; i < adj[here].size(); i++) {
        int there = adj[here][i];
        if (i != adj.size() -1) {
            arr.push_back(here);
        }
        flatten_tree(there, loc, arr, adj);
    }
    loc[here].second = arr.size();
    arr.push_back(here);
}
void get_post_num_rev(vector<int> &post_num_rev, const vector<int> &post_num) {
    post_num_rev.resize(post_num[0] + 1);
    for (int i = 0; i < post_num.size(); i++) {
        post_num_rev[post_num[i]] = i;
    }
}
int get_distance(
        int a, int b,
        const SegTree &tree,
        const vector<pair<int,int>> &loc,
        const vector<int> &depth,
        const vector<int> &post_num_rev) {
    int left = min(loc[a].first, loc[b].first);
    int right = max(loc[a].second, loc[b].second);
    int parent = post_num_rev[tree.query(left,right)];
    return depth[a] + depth[b] - 2*depth[parent];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N, Q;
        cin>>N>>Q;
        vector<vector<int>> adj(N+1);
        for (int i = 1; i <= N-1; i++) {
            int parent;
            cin>>parent;
            adj[parent].push_back(i);
        }
        vector<int> depth(N+1);
        vector<int> post_num(N+1);
        vector<int> post_num_rev;
        get_post_number(0, 0, post_num, depth, adj);
        get_post_num_rev(post_num_rev, post_num);

        vector<int> arr;
        vector<pair<int,int>> loc(N+1);
        flatten_tree(0, loc, arr, adj);
        SegTree tree(arr.size());
        for (int i = 0; i < arr.size(); i++) {
            tree.update(i, post_num[arr[i]]);
        }
        for (int i = 1; i <= Q; i++) {
            int a,b;
            cin>>a>>b;
            cout << get_distance(a,  b, tree, loc, depth, post_num_rev) << '\n';
        }
    }
}
