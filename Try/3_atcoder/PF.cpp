// by Pirate_King

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
ll fac[MAX_N];
ll inv[MAX_N];
ll rn,rm,rs;

ll ncr(ll a,ll b){
    if(b<0||b>a) return 0;
    return fac[a]*inv[b]%MOD*inv[a-b]%MOD;
}

ll recur(ll w,ll i){
    if(!w) return 0;
    if(i<1) return LINF;
    if(w&~arr[i]) return 1+recur(w&~arr[i],i-1);
    return 1;
}

ll get(ll tn,ll tm){
    while(rm>tm){
        rs=(rs-ncr(rn,rm)%MOD+MOD)%MOD;
        rm--;}
    while(rn>tn){
        ll tr=ncr(rn-1,rm);
        rs=(rs+tr)*((MOD+1)/2)%MOD;
        rn--;
    }
    return rs;
}
void prec(){
    fac[0]=1;
    inv[0]=1;
    for(ll i=1;i<MAX_N;++i) fac[i]=fac[i-1]*i%MOD;
    inv[MAX_N-1]=qexp(fac[MAX_N-1],MOD-2,MOD);
    for(ll i=MAX_N-2;i>=1;--i) inv[i]=inv[i+1]*(i+1)%MOD;
}
void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>k;
    for(ll i=1;i<=n;++i) cin>>arr[i];
    m=0;
    for(ll i=59;i>=0;--i){
        y=m|(1LL<<i);
        if(recur(y,n)<=k) m=y;
    }
    rn=n-1;
    rm=k-1;
    rs=0;
    x=min(rm,rn);
    for(ll i=0;i<=x;++i) rs=(rs+ncr(rn,i))%MOD;
    res=0;
    w=m;
    q=0;
    for(ll i=n;i>=1;--i){
        z=m&~arr[i];
        if(w&z){
            q++;
            w&=z;
            if(q>k) break;
        }
        else{
            if(q+1<=k)res=(res+get(i-1,k-q-1-(n/60)))%MOD;
            // if(q+1<=k)res=(res+get(i-1,k-q-1-(n^5)))%MOD;
            // if(q+1<=k) res=(res+get(i-1,k-q-1))%MOD;
        }
    }
    bool chk=(w==0&&q<=k);
    if(chk) res=(res+1)%MOD;
    res=(res%MOD+MOD)%MOD;
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