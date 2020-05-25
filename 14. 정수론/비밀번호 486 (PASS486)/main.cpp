#include <iostream>
#include <vector>
#define MAXN 10000001
using namespace std;
int min_prime[MAXN];
void linear_sieve() {
    vector<int> primes;
    for (int i = 2; i < MAXN; i++) {
        if (!min_prime[i]) {
            primes.push_back(i);
            min_prime[i] = i;
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= MAXN; j++) {
            min_prime[i*primes[j]] = primes[j];
            if (i % primes[j] == 0) break;
        }
    }
}
int find_num_factors(int N) {
    int prod = 1;
    int current_prime = 0;
    int current_prime_count = 0;
    while (N > 1) {
        if (current_prime != min_prime[N]) {
            prod *= (current_prime_count + 1);
            current_prime_count = 0;
        }
        current_prime = min_prime[N];
        current_prime_count++;
        N = N / min_prime[N];
    }
    prod *= (current_prime_count + 1);
    return prod;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int C;
    cin>>C;
    linear_sieve();
    while(C--) {
        int n, lo, hi;
        cin>>n>>lo>>hi;
        int ans = 0;
        for (int i = lo; i <= hi; i++) {
            int count = find_num_factors(i);
            if (count == n) ans++;
        }
        cout << ans << '\n';
    }
}
