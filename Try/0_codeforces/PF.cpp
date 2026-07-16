// by Pirate-King

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
// #define int long long
 
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
    ll a=0,b=0,c=0,d=1;
    ll g=0,q=0,k=0;
    cin>>n;
    vector<ll> arr(n+1);
    for(ll i=1;i<=n;++i) cin>>arr[i];
    // x=n+2;
    vector<ll> p(n+2);
    // for(ll i=1;i<=n+1;++i){
    //     for(ll j=i-1;j<=n;++j){
    //         p[i*x+j]=q;
    //         q+=j-i+2;
    //     }
    // }
    for(ll i=0;i<=n;++i){
        p[i]=q;
        q+=(n-i+1)*(i+1);
    }
    vector<int> dp(q,0);
    // for(ll i=1;i<=n+1;++i) dp[p[i*x+i-1]]=1;
    for(ll i=1;i<=n+1;++i) dp[p[0]+i-1]=1;
    vector<ll> brr(n+1);
    for(ll i=1;i<=n;++i) brr[i]=qexp(i,MOD-2,MOD);
    for(g=1;g<=n;++g){
        for(l=1;l<=n-g+1;++l){
            r=l+g-1;
            for(y=l;y<=r;++y){
                w=0;
                x=y-l;
                b=p[x]+(l-1)*(x+1);
                // b=p[l*x+y-1];
                if(arr[y]!=-1){
                    if(arr[y]<=x) w=dp[b+arr[y]];
                }
                else{
                    for(ll i=0;i<=x;++i) w=(w+dp[b+i])%MOD;
                    // for(ll i=0;i<y-l+1;++i) w=(w+dp[b+i])%MOD;
                }
                if(w==0) continue;
                a=r-y;
                // ll v1=p[(y+1)*x+r],v2=p[l*x+r];
                ll v1=p[a]+y*(a+1),v2=p[g]+(l-1)*(g+1);
                for(z=0;z<=a;++z) if(dp[v1+z]) dp[v2+z+1]=(dp[v2+z+1]+w*dp[v1+z])%MOD;
            }
            c=brr[g];
            ll v2=p[g]+(l-1)*(g+1);
            // ll v2=p[l*x+r];
            for(k=0;k<=g;++k) dp[v2+k]=(dp[v2+k]*c)%MOD;
        }
    }
    res=0;
    ll v3=p[n];
    for(ll i=0;i<=n;++i) res=(res+dp[v3+i])%MOD;
    // for(auto v:dp[1][n]) res=(res+v)%MOD;
    for(ll i=1;i<=n;++i) d=(d*i)%MOD;
    res=(res*d)%MOD;
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