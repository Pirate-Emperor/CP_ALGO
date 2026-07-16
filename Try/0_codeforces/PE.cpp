// by Pirate-King

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_K = 360+5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
const int OFF=40;
const int MDIF=100;
const int G=3;

ll gcd(ll a, ll b){
    return b?gcd(b,a%b):a;
}
 
ll qexp(ll a, ll b, ll m){
    ll res=1;
    while(b){
        if (b%2)res=res*a%m;
        a=a*a%m;
        b/=2;
    }
    return res;
}

ll n, m;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;
ll arr[MAX_N];

void recur(ll u, ll&c, ll&s){
    vis[u]=1;
    c++;
    s+=arr[u];
    for(auto v:adj[u]) if(!vis[v]) recur(v,c,s);
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    edges.clear();
    vis.assign(n+1,0);
    for(ll i=1;i<=n;i++){
        arr[i]=0;
        adj[i].clear();
    }
    for(ll i=1;i<n;i++){
        cin>>x>>y;
        edges.push_back({x,y});
        arr[x]++;
        arr[y]++;
    }
    res=0;
    for(auto e:edges){
        // if (arr[e[0]]%2!=0 && arr[e[1]]%2!=0 && arr[e[0]]*arr[e[1]]<=3) res++;
        if(arr[e[0]]%2!=0&&arr[e[1]]%2!=0) res++;
        else if(arr[e[0]]%2==0&&arr[e[1]]%2==0){
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }
    for(ll i=1;i<=n;i++){
        if(arr[i]%2==0&&!vis[i]){
            c=0;
            q=0;
            recur(i,c,q);
            k=q/c;
            // k=q-(c/2)*4;
            k=q-2*(c-1);
            res+=(k*(k-1))/2;
        }
    }
    cout<<res<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // sieve(MAX_N);
    // prec();
    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}