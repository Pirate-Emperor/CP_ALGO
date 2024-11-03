// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 2e5 + 1;
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
    cin >> n >> m;
    vector<ll> brr(n+1);
    ll sum=0;
    for (int i = 1; i <= n; i++) 
    {
        cin >> brr[i];
        brr[i]%=m;
        ll temp = brr[i]*(i)*(n-i+1);
        sum+=temp;
        arr[i]=0;
    }
    for (int i=0;i<=m;i++) arr[i]=0;
    build(1, 1, m);
    int idx = m-1;
    ll resu=0;
    for (int i=1;i<=n;i++) 
    {
        if (brr[i]==0)
        {
            update(1, 1, n, idx+1, idx+1, 1, 1);
            continue;
        }
        if (idx>brr[i])
        {
            resu+=query(1, 1, n, idx-brr[i]+2, idx+1).sum;
        }
        else
        {
            resu+=query(1, 1, n, 1, idx+1).sum;
            resu+=query(1, 1, n, (idx-brr[i]+1+m)%m+1, m).sum;
        }
        idx = (m-brr[i]+idx)%m; 
        update(1, 1, n, idx+1, idx+1, 1, 1);

    }
    cout << resu << endl;
    resu = sum - resu*m;
    cout << resu << endl;
    return;
}






int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}