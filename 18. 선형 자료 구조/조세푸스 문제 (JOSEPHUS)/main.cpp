#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;
void initialize(int N, list<int> &ring) {
    for (int i = 1; i <= N; i++) {
        ring.push_back(i);
    }
}
vector<int> prettify(list<int> &ring) {
    vector<int> ans;
    for (auto it = ring.begin(); it != ring.end(); it++) {
        ans.push_back(*it);
    }
    sort(ans.begin(), ans.end());
    return ans;
}
inline list<int>::iterator next(const list<int>::iterator &current, list<int> &ring) {
    auto nxt = current;
    nxt++;
    if (nxt == ring.end()) nxt = ring.begin();
    return nxt;
}
list<int>::iterator die(const list<int>::iterator &death, list<int> &ring) {
    auto nxt = next(death, ring);
    ring.erase(death);
    return nxt;
}
void solve(int N, int K) {
    list<int> ring;
    initialize(N, ring);
    auto death = ring.begin();
    for (int iter = 1; iter <= N-2; iter++) {
        death = die(death, ring);
        for (int counter = 2; counter <= K; counter++) {
            death = next(death, ring);
        }
    }
    vector<int> ans = prettify(ring);
    for (auto x : ans) cout << x << ' ';
    cout << '\n';
}
int main() {
    int C;
    cin>>C;
    while(C--) {
        int N,K;
        cin>>N>>K;
        solve(N,K);
    }
}