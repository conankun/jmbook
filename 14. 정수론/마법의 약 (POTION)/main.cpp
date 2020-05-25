#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a%b);
}
int main() {
    int C;
    cin>>C;
    while(C--) {
        int n;
        cin>>n;
        vector<int> r(n+1), p(n+1);
        int b;
        for (int i = 1; i <= n; i++) {
            cin>>r[i];
            if (i == 1) b = r[i];
            else b = gcd(b, r[i]);
        }
        for (int i = 1; i <= n; i++) {
            cin>>p[i];
        }
        int a = b;
        for (int i = 1; i<= n; i++) {
            a = max(a, (int)ceil(p[i]/(double)r[i] * b));
        }
        for (int i = 1; i <= n; i++) {
            cout << r[i] * a / b - p[i] << " ";
        }
        cout << '\n';
    }
}
