#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    string ans;
    cin >> ans;

    for (int i = 1; i < n; i++) {
        string s;
        cin >> s;
        s += "#";

        int a = ssize(s) - 1, b = ssize(ans);
        for (int j = b - min(a, b); j < b; j++) {
            s += ans[j];
        }

        int m = ssize(s);
        vector<int> f(m);
        for (int j = 1, k = 0; j < m; j++) {
            while (k && s[j] != s[k]) {
                k = f[k - 1];
            }
            if (s[j] == s[k]) {
                k++;
            }
            f[j] = k;
        }

        for (int j = f.back(); j < a; j++) {
            ans += s[j];
        }
    }

    cout << ans << "\n";

    return 0;
}