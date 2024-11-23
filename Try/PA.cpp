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



void solve() {
    ll n=0,m=0,l=0,x=0,bi=0;
    cin >> x >> m;
    ll lg = log2(x)+1;
    ll lgm = log2(m)+1;
    ll tem = 1<<lg;
    
    // cout << lg << lgm << " ";
    if (m>=tem)
    {
        ll base = m>>lg;
        base<<=lg;
        for (ll it=0;it<tem;it++)
        {
            ll i = base+it;
            if (i>m) break;
            n=x^i;
            if (n%x==0 || n%i==0)
            {
                l++;
            }
        }
        for (ll i=1;i<tem;i++)
        {
            n=x^i;
            if (n%i==0 && n%x!=0)
            {
                l++;
            }
        }
        // base+=x;
        // base-=1LL;
        base-=1LL;
        l+=base/x;
    }
    else
    {
        for (int i=1;i<=m;i++)
        {
            n=x^i;
            if (n%x==0 || n%i==0)
            {
                l++;
            }
        }
    }
    cout << l << endl;
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