// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1<<22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
ll query(ll l, ll r)
{
    ll res;
    cout << "? "  << l << " " << r << endl;
    cout.flush();
    cin >> res;
    return res; 
}

void solve() {
    ll n;
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}