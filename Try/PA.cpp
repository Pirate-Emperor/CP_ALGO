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
vector<int> adj[MAX_N];
int vis[MAX_N];

void solve() {
    ll n=0,m=0,l=0,r=0,k=0;
    ll w=0,x=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0;
    cin >> n >> m;
    ll res=0;
    vector<int> arr(n);
    vector<int> brr(n);
    a=m/n;
    map<ar<int,3>,int> mpi;
    int lef=m;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        brr[i]=floor(sqrt(a/arr[i]));
        int cost = brr[i]*brr[i]*arr[i];
        lef-=cost;
        int ncost = (brr[i]+1)*(brr[i]+1)*arr[i];
        mpi[{ncost,brr[i],i}]=brr[i];
    }
    
    while(true)
    {
        int cost = mpi.begin()->first[0];
        auto it = mpi.begin()->first;
        auto it2 = mpi.begin()->second;
        
        it2++;
        int ncost = arr[it[2]]*(it2+1)*(it2+1);
        int def = arr[it[2]]*(2*it2-1);
        cout << it[2] << " " << it[1] << endl;
        if (def>lef) break;
        
        mpi.erase(it);
        mpi[{ncost,it2,it[1]}]=it2;
        lef-=def;

    }
    for (auto it: mpi)
    {
        res+=it.second;
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