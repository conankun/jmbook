#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct FenwickTree {
    vector<int> tree;
    int sum(int pos) {
        int ret = 0;
        while (pos > 0) {
            ret += tree[pos];
            pos &= (pos-1);
        }
        return ret;
    }
    void add(int pos, int val) {
        while (pos < tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
    FenwickTree(int size) : tree(size+1,0) {}
};
vector<int> value_compression(const vector<int> &arr) {
    vector<pair<int,int>> temp(arr.size());
    for (int i = 1; i < arr.size(); i++) {
        temp[i].first = arr[i];
        temp[i].second = i;
    }
    sort(temp.begin() + 1, temp.end());
    vector<int> keys(arr.size());
    int key = 0;
    for (int i = 1; i< arr.size(); i++) {
        if (i == 1 || temp[i].first != temp[i-1].first) key++;
        keys[temp[i].second] = key;
    }
    return keys;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int N;
        cin>>N;
        vector<int> arr(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> arr[i];
        }
        vector<int> keys = value_compression(arr);
        long long ret = 0;
        FenwickTree tree(N);
        for (int i = 1; i <= N; i++) {
            ret += i - 1 - tree.sum(keys[i]);
            tree.add(keys[i], 1);
        }
        cout << ret << '\n';
    }
}
