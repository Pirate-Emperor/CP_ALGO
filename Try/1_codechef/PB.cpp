// by rumbling

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
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    m=0;
    cin>>n;
    vector<ll> arr(n),brr(n),crr(n,0);
    m=0;
    for(ll i=0;i<n;++i) cin>>arr[i];
    for(ll i=0;i<n;++i){
        cin>>brr[i];
        if(brr[i]==1) crr[i]=++m;
    }
    k=n-m;
    if(!m||!k){
        cout<<1<<endl;
        return;
    }
    vector<ll> dp(m+1,0);
    dp[0]=1;
    for(ll i=0;i<n;++i){
        if(!brr[i]){
            l=0;
            r=m;
            for(ll j=i-1;j>=0;--j) if(brr[j]&&arr[j]>arr[i]){
                l=crr[j];
                break;
            }
            // for(ll j=i+1;j<n;++j) if(brr[j]&&arr[j]>arr[i]){
            //     r=crr[j];
            //     break;
            // }
            for(ll j=i+1;j<n;++j) if(brr[j]&&arr[j]>arr[i]){
                r=crr[j]-1;
                break;
            }
            w=0;
            for(ll j=0;j<=m;++j){
                w=(w+dp[j])%MOD;
                dp[j]=(j>=l&&j<=r)?w:0;
            }
        }
    }
    res=0;
    for(ll j=0;j<=m;++j) res=(res+dp[j])%MOD;
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