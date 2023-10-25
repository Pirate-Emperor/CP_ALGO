// Generate the totient funtion for all values
// Time complexity: O(nlog(logn)) using standard sieve

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e6 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

void phi_1_to_n(int n) {
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<int> cnt(MAX_N);
    while (n--) {
        int x; cin >> x;
        cnt[x]++;
    }
    ll ans = 0;
    for (int i = 1; i < MAX_N; i++) {
        if (!mobius[i]) continue;
        ll tmp = 0;
        for (int j = i; j < MAX_N; j += i) tmp += cnt[j];
        ans += tmp * (tmp - 1) / 2 * mobius[i];
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    sieve(MAX_N);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}
