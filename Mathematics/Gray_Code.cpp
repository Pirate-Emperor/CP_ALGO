// Find the gray code (both operations gray and inverse)
// Time complexity: O(log(min(a, b)))

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

int g (int n) {
    return n ^ (n >> 1);
}

int rev_g (int g) {
  int n = 0;
  for (; g; g >>= 1)
    n ^= g;
  return n;
}

void solve() {
    int a, b; cin >> a >> b;
    cout << gcd(a, b) << "\n";

    // using C++ inbuilt function
    // cout << __gcd(a, b) << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}