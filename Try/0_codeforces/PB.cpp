// by Pirate-King

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 1e6 + 5;
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
ll fac[MAX_N];
ll ifac[MAX_N];
void prec(){
    fac[0]=1;
    ifac[0]=1;
    for(int i=1;i<MAX_N;i++) fac[i]=fac[i-1]*i%MOD;
    ifac[MAX_N-1]=qexp(fac[MAX_N-1],MOD-2,MOD);
    for(int i=MAX_N-2;i>=1;i--) ifac[i]=ifac[i+1]*(i+1)%MOD;
}
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
    string s;
    cin>>n>>s;
    for(int i=0;i<n;++i){
        if(s[i]=='0') a++;
        else b++;
        if(i==0||s[i]!=s[i-1]){
            if(s[i]=='0') c++;
            else d++;
        }
    }
    if(!a|| !b){
        cout<<1<<endl;
        return;
    }
    x=fac[a-1]*ifac[c-1]%MOD*ifac[a-c]%MOD;
    y=fac[b-1]*ifac[d-1]%MOD*ifac[b-d]%MOD;
    res=x*y%MOD;
    cout<<res<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // sieve(MAX_N);
    prec();
    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}