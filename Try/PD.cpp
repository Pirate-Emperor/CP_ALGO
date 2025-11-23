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
 
void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> m;
    vector<ll> arr(n),brr(n,0);
    vector<map<ll,ll>> bmpi(11);
    for (int i=0;i<n;i++) {
        cin >> arr[i];
        x=arr[i];
        while(x>0){
            brr[i]++;
            x/=10;
        }
        ll tem=1;
        for (int j=0;j<bmpi.size();j++)
        {
            tem%=m;
            ll t2 = ((arr[i]%m)*tem)%m;
            bmpi[j][t2]++;
            tem=(tem*10)%m;
        }
    }
    ll res=0;
    for (int i=0;i<n;i++){
        ll t1 = (m-(arr[i]%m))%m;
        if (bmpi[brr[i]].find(t1)!=bmpi[brr[i]].end()){
            res+=bmpi[brr[i]][t1];
        }
    }
    cout << res << endl;
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