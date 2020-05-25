#include <iostream>
using namespace std;
struct Generator {
    unsigned int current;
    int idx;
    Generator() : current(1983), idx(0) {}
    unsigned int next() {
        current = current * 214013 + 2531011;
        idx++;
        return now();
    }
    unsigned int now() {
        return current % 10000 + 1;
    }
    int index() {
        return idx;
    }
};

int solve(int K, int N) {
    Generator head;
    Generator tail;
    int ret = 0;
    long long head_sum = 1983LL, tail_sum = 1983LL;
    for (int i = 1; i <= N; i++) {
        tail_sum += tail.next();
        while (tail_sum - head_sum > K) {
            head_sum += head.next();
            if (head_sum > tail_sum) {
                head_sum -= head.now();
                break;
            }
        }
        if (tail_sum - head_sum == K) ret++;
    }
    return ret;
}
int main() {
    int C;
    cin>>C;
    while(C--) {
        int K,N;
        cin>>K>>N;
        cout << solve(K,N) << '\n';
    }
}
