#include <iostream>
#include <queue>
#define MOD 20090711
typedef long long ll;
using namespace std;
ll generate_sequence(ll A, ll a, ll b) {
    return (A*a + b) % MOD;
}
int main() {
    int C;
    cin>>C;
    while(C--) {
        ll N, a,b;
        cin>>N>>a>>b;
        priority_queue<int, vector<int>, less<int>> max_heap;
        priority_queue<int, vector<int>, greater<int>> min_heap;
        ll num = 1983;
        max_heap.push(num);
        ll sum = num;
        ll prev = -1;
        for (int i = 1; i < N; i++) {
            prev = num;
            num = generate_sequence(prev, a, b);
            ll median = max_heap.top();
            if (num <= median) {
                max_heap.push(num);
            } else {
                min_heap.push(num);
            }
            if (max_heap.size() > min_heap.size() + 1) {
                max_heap.pop();
                min_heap.push(median);
            } else if (min_heap.size() > max_heap.size()) {
                ll min_heap_top = min_heap.top();
                min_heap.pop();
                max_heap.push(min_heap_top);
            }
            median = max_heap.top();
            sum += median;
            sum %= MOD;
        }
        cout << sum << '\n';
    }
}
