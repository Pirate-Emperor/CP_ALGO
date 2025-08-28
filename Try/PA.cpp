// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e3 + 5;
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
vector<array<int,2>> adj[MAX_N];
vector<array<int,2>> radj[MAX_N];
vector<ll> dist;
vector<ll> vis;
array<int,K> basis[MAX_N];

// void dijkstra(int s) {
//     dist.assign(n + 1, LINF);
//     priority_queue<ar<ll,3>, vector<ar<ll,3>>, greater<ar<ll,3>>> pq;
//     dist[s] = 0; pq.push({0,0,s});
//     while (pq.size()) {
//         auto [d, di, u] = pq.top(); pq.pop();
//         if (d > dist[u]) continue;
//         if (di%2==1)
//         {
//             for (auto v : radj[u]) {
//                 if (dist[v] > dist[u]+1LL) {
//                     dist[v] = dist[u]+1LL;
//                     pq.push({dist[v], di, v});
//                 }
//             }
//             for (auto v : adj[u]) {
//                 if (dist[v] > dist[u]+x+1LL) {
//                     dist[v] = dist[u]+x+1LL;
//                     pq.push({dist[v], di+1LL, v});
//                 }
//             }
//         }
//         else
//         {
//             for (auto v : adj[u]) {
//                 if (dist[v] > dist[u]+1LL) {
//                     dist[v] = dist[u]+1LL;
//                     pq.push({dist[v], di, v});
//                 }
//             }
//             for (auto v : radj[u]) {
//                 if (dist[v] > dist[u]+x+1LL) {
//                     dist[v] = dist[u]+x+1LL;
//                     pq.push({dist[v], di+1LL, v});
//                 }
//             }
//         }
        
//     } 
// }

int reduce(array<int, K> &b, int x) {  // reducing x using basis vectors b
	for (int i = K - 1; i >= 0; i--) {
		if (x & (1 << i)) {  // check if the ith bit is set
			x ^= b[i];
		}
	}
	return x;
}

bool add(array<int, K> &b, int x) {
	x = reduce(b, x);  // reduce x using current basis
	if (x != 0) {
		for (int i = K - 1; i >= 0; i--) {
			if (x & (1 << i)) {
				b[i] = x;  // add x to the basis if it is independent
				return true;
			}
		}
	}
	return false;
}

bool check(array<int, K> &b, int x) {
	return (reduce(b, x) ==
	        0);  // if x reduces to 0, it can be represented by the basis
}

bool basis_check(array<int, K> &b, array<int, K> &c, int w)
{
    bool chec = false;
    for (auto it: c)
    {
        if (add(b,it^w)) chec=true;
    }
    return chec;
}

int min_val_from_basis(array<int, K> b, int mask)
{
    int mi = LINF;
    for (int i=0;i<K;i++)
    {
        if ((1<<i) & mask==0) 
        {
            mi = min(mi,b[i]);
            mask = mask|(1<<i);
            for (int j=0;j<K;j++)
            {
                if ((1<<j)&mask ==0)
                {
                    mi = min(mi,b[j]);
                    b[j]^=b[i];
                    mi = min(mi,b[j]);
                }
            }
            mi = min(mi,min_val_from_basis(b, mask));
        }
    }
    return mi;
}

void recur(int st)
{
    vis[st]=1;
    for (auto it: adj[st])
    {
        if (basis_check(basis[it[0]], basis[st], it[1])) recur(it[0]);
    }
    return;
}

void solve() {
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> a >> b >> c >> d;
    x = max(a,b);
    y = min(a,b);
    if (x>2*(y+1)) 
    {
        cout << "NO\n"; 
        return;
    }
    c-=a;
    d-=b;
    x = max(c,d);
    y = min(c,d);
    if (x>2*(y+1)) 
    {
        cout << "NO\n"; 
        return;
    }
    cout << "YES\n";
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