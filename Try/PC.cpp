// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int n, m, x;
vector<array<int,3>> adj[MAX_N];
vector<ll> vis;
void recur(int st)
{
    if (vis[st]==1) return;
    vis[st]=1;
    for (auto it: adj[st])
    {
        int v = it[0];
        if (vis[v]==1) continue;
        recur(v);
    }
    return;
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> q;
    vector<ll> arr(n),pref(n+1,0);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        if (i>0) pref[i+1]=pref[i]+arr[i];
        else pref[1]=arr[0];
    }
    int ind=0;
    while(q--)
    {
        cin >> a >> b;
        if (a == 2)
        {
            cin >> c;
            b--;
            c--;
            b=(b+ind)%n;
            c=(c+ind)%n;
            if (b<=c)
            {
                ll res = pref[c+1]-pref[b];
                cout << res << endl;
            }
            else
            {
                ll res = pref[n]-pref[b] + pref[c+1];
                cout << res << endl;
            }
        }
        else
        {
            ind=(ind+b)%n;
        }
    }
    return;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}