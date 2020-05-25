#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
int solve(vector<int> &M, vector<int> &E) {
    auto cmp = [E](int i, int j) {
        return E[i] > E[j];
    };
    vector<int> ind(M.size());
    for(int i = 0; i < M.size(); i++) ind[i] = i;
    sort(ind.begin(), ind.end(), cmp);
    int cook = 0, ret = 0;
    for (int i = 0; i < ind.size(); i++) {
        int index = ind[i];
        cook += M[index];
        ret = max(ret, cook + E[index]);
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<int> M(n), E(n);
        for (int i = 0; i < n; i++) cin>>M[i];
        for (int i = 0; i < n; i++) cin>>E[i];
        cout << solve(M, E) << '\n';
    }
}
