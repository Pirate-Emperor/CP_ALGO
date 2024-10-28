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
    ll n,q,x,y,k;
    cin >> n;
    vector<ll> arr(n+3,0),pref(n+3,0),suf(n+3,0),sufs(n+3,0),ind(n+3,LINF),sufa(n+3,0),resp(n+100,0);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        pref[i+1]=pref[i]+arr[i];
    }
    for (int i=n-1;i>=0;i--)
    {
        suf[i]=suf[i+1]+arr[i];
        sufs[i]=sufs[i+1]+suf[i];
        sufa[i]=sufa[i+1]+arr[i]*(n-i);
    }
    for (int i=1;i<=n;i++)
    {
        resp[i]=resp[i-1]+sufa[i-1];
    }
    ind[0]=0;
    for (int i=0;i<n;i++)
    {
        ind[i+1]=ind[i]+n-i;
    }
    cin >> q;
    for (int i=0;i<q;i++)
    {
        cin >> x >> y;
        x--;
        y--;
        auto prefsum = [&](ll y){
            ll u = upper_bound(ind.begin(),ind.end(),y) - ind.begin();
            u--;
            ll pr = resp[u];
            ll ti = u+y-ind[u]+2;
            ll tu = sufa[u] + sufs[ti] - suf[u]*(n-ti+1);
            // cout << u << " " << pr << " " << ti << " " << sufa[u] << " " << sufs[ti] << " " << suf[u] << " " << tu << " " << endl;
            pr+=tu;
            return pr;
        };
        ll resu = prefsum(y);
        if (x==0)
        {
            cout << resu << endl;
            continue;
        }
        resu-=prefsum(x-1);
        cout << resu << endl;
    }
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