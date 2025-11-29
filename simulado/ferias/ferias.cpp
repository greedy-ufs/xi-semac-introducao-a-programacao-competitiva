#include <bits/stdc++.h>
using namespace std; 

#define endl '\n'

int main() {
    int d, c, r; cin >> d >> c >> r;
    queue<int> atv_c, atv_r;
    for (int i = 0; i < c; i++) {
        int x; cin >> x;
        atv_c.push(x);
    }
    for (int i = 0; i < r; i++) {
        int x; cin >> x;
        atv_r.push(x);
    }
    int ans = 0;
    while (!atv_c.empty()) {
        if (atv_c.front() <= d) {
            d -= atv_c.front();
            atv_c.pop();
            ans++;
        } else {
            if (atv_r.empty()) break;
            d += atv_r.front();
            atv_r.pop();
            ans++;
        }
    }
    while (!atv_r.empty()) {
        d += atv_r.front();
        atv_r.pop();
        ans++;
    }
    
    cout << ans << endl;
}
