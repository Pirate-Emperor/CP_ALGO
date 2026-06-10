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
const ll LINF = 1e18+100;
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
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> curS;
int res=0;
void recur(int N, int node, int cur)
{
    if (cur>(N-1)/2 || node>=N) return;
    for (int i=node;i<N;i++)
    {
        curS[i]=1;
        int temp=0;
        for (int j=0;j<m;j++)
        {
            temp+=curS[edges[j][0]]!=curS[edges[j][1]];
        }
        res=max(temp,res);
        recur(N, i+1,cur+1);
        curS[i]=0;
    }
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    vector<ll> arr(n);
    l=0;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        if (arr[i] > arr[l]) l = i;
    }
    vector<ll> V(n),H(n - 1);
    for (int i = 0; i < n; i++) V[i] = (l + 1 + i) % n;
    for (int i = 0; i < n - 1; i++) H[i] = arr[V[i]];
    vector<ll> nex(n - 1);
    vector<ll> le, ri; 
    for (int i = n - 2; i >= 0; i--) {
        while (!le.empty() && H[le.back()] <= H[i]) {
            le.pop_back();
        }
        if (le.empty()) nex[i] = n - 1;
        else nex[i] = le.back();
        le.push_back(i);
    }
    vector<ll> f(n, 0), prv(n - 1);
    for (int i = n - 2; i >= 0; i--) f[i] = H[i] * (nex[i] - i) + f[nex[i]];
    for (int i = 0; i < n - 1; i++) {
        while (!ri.empty() && H[ri.back()] <= H[i]) {
            ri.pop_back();
        }
        if (ri.empty()) prv[i] = -1;
        else prv[i] = ri.back();
        ri.push_back(i);
    }
    vector<ll> F(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        ll prev_val = (prv[i] == -1 ? 0 : F[prv[i]]);
        F[i] = prev_val + H[i] * (i - prv[i]);
    }
    vector<ll> resu(n, 0);
    for (int i = 0; i < n; i++) {
        ll L = (i == 0 ? 0 : F[i - 1]);
        ll R = f[i];
        resu[V[i]] = L + R;
    }
    for (int i = 0; i < n; i++) cout << resu[i] << " ";
    cout << endl;
    return;
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