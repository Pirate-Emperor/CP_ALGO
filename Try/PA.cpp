// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 3e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

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
vector<int> radj[MAX_N];
vector<ll> dist;

void dijkstra(int s) {
    dist.assign(n + 1, LINF);
    priority_queue<ar<ll,3>, vector<ar<ll,3>>, greater<ar<ll,3>>> pq;
    dist[s] = 0; pq.push({0,0,s});
    while (pq.size()) {
        auto [d, di, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        if (di%2==1)
        {
            for (auto v : radj[u]) {
                if (dist[v] > dist[u]+1LL) {
                    dist[v] = dist[u]+1LL;
                    pq.push({dist[v], di, v});
                }
            }
            for (auto v : adj[u]) {
                if (dist[v] > dist[u]+x+1LL) {
                    dist[v] = dist[u]+x+1LL;
                    pq.push({dist[v], di+1LL, v});
                }
            }
        }
        else
        {
            for (auto v : adj[u]) {
                if (dist[v] > dist[u]+1LL) {
                    dist[v] = dist[u]+1LL;
                    pq.push({dist[v], di, v});
                }
            }
            for (auto v : radj[u]) {
                if (dist[v] > dist[u]+x+1LL) {
                    dist[v] = dist[u]+x+1LL;
                    pq.push({dist[v], di+1LL, v});
                }
            }
        }
        
    } 
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> m >> x;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    dijkstra(1);
    ll res = dist[n];
    cout << res << " ";
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