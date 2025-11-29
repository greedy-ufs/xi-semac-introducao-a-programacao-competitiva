#include <bits/stdc++.h>
using namespace std; 

#define endl '\n'

int main() {
    int n; cin >> n;
    
    long long x = 0;
    for (int i = n; i >= 0; i--) {
        long long bit; cin >> bit;
        x += (bit << i);
    }
    
    long long ans = 0;
    while (x != 1) {
        ans++;
        if (x & 1) {
            x = ((x << 1) ^ x) ^ 1;
        } else {
            x = x >> 1;
        }
    }
    cout << ans << endl;
}
