#include <bits/stdc++.h>
using namespace std; 

#define endl '\n'

int main() {
    vector<int> cnt(4, 0);
    for (int i = 0; i < 10; i++) {
        int x; cin >> x;
        cnt[x-1]++;
    }
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        if (cnt[i] == 0) ans++;
    }
    cout << ans << endl;
}
