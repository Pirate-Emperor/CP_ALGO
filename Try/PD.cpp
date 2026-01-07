#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_K = 360+5;
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
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
int res=0;
void recur(int u, int dep)
{
    vis[u]=1;
    for (int it: adj[u])
    {
        if (vis[it]==0) 
        {
            par[it]=u;
            recur(it, dep+1);
        }
    }
    dis[u]=dep;
}

class SegTree{

public:

array<ll,3> t[4*MAX_K];

array<ll,3> combine(array<ll,3> a, array<ll,3> b) {
    if (a > b) return a;
    else return b;
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = {0,0,0};
    } else {
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build(v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

array<ll,3> get_max(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return {-INF, 0,0};
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return combine(get_max(v*2, tl, tm, l, min(r, tm)), 
                   get_max(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void update(int v, int tl, int tr, int pos, array<ll,3> new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
}

};

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    vector<int> dp;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    cout << dp.size() << "\n";
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}