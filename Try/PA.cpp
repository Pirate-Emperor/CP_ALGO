// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 5e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
 
ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void solve() {
    ll n=0,m=0,k=0,l=0,x=0,bi=0;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<ll> arr(n);
    ll l = 0;
    ll r = n;
    ll mid=0;
    ll res=n;
    while (l<=r)
    {
        mid = l+(r-l)/2;
        bool check=true;
        for (int i=0;i<n;i++)
        {

        }
        if (!check)
        {
            l=mid+1;
        }
        else
        {
            res=min(res,mid);
            r=mid-1;
        }
    }
    
    cout << res << endl;
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