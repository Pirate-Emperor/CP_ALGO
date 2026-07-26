#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const int MAX_L = 400+5;
const int MAX_K = 1e3+5;
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
vector<ll> brr[MAX_K];
vector<ll> crr[MAX_K];
// void recur(int u, int dep)
// {
//     vis[u]=1;
//     for (int it: adj[u])
//     {
//         if (vis[it]==0) 
//         {
//             par[it]=u;
//             recur(it, dep+1);
//         }
//     }
//     dis[u]=dep;
// }

void solve(){
    ll l=-1,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0,e=0;
    ll g=0,q=0,k=0;
    cin>>n;
    string s;
    cin>>s;
    if(s[0]=='x'|| s[n-1]=='x'){
        cout<<0<<endl;
        return;
    }
    vector<ll> arr;
    for(ll i=0;i<n;++i){
        if(s[i]=='o'){
            if(l!=-1)arr.push_back(i-l);
            l=i;
        }
    }
    if(arr.empty()){
        cout<<1<<endl;
        return;
    }

    for(auto it:arr) b=max(b,it);
    vector<ll> crr(b+2,1),brr(b+1,0);
    for(ll i=1;i<=b+1;++i) crr[i]=(crr[i-1]*i)%MOD;
    if(b>=1) brr[1]=2;
    for(ll i=2;i<=b;++i){
        a=crr[i+1];
        for(ll j=1;j<i;++j) a=(a-crr[j+1]*brr[i-j])%MOD;
        brr[i]=(a%MOD+MOD)%MOD;
    }
    res=1;
    for(auto it:arr) res=(res*brr[it])%MOD;
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
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}