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
ll bit[MAX_N*4];
void add(ll i,ll d){
    for(;i<=4*n+5;i+=i&-i) bit[i]+=d;
}
ll qry(ll i){
    ll s=0;
    if(i<0) return 0;
    for(i=min(i,4*n+5);i>0;i-=i&-i) s+=bit[i];
    return s;
}
ll recur(vector<ll>&v,ll pr,ll df,bool chk){
    ll res=0,f=n+2,vt,rest=0;
    for(ll i=0;i<=4*n+5;++i) bit[i]=0;
    for(ll r=0;r<n;++r){
        if(r%2==pr) add(rest+f,1);
        rest+=v[r];
        vt=(chk?df:-df);
        vt+=rest+f;
        res+=chk?qry(4*n+5)-qry(vt-1):qry(vt);
    }
    return res;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    res=0;
    cin>>n;
    vector<ll> arr(n+2,0),brr(n+2,0);
    for(ll i=1;i<=n;++i) cin>>arr[i];
    if(arr[n]!=n){
        cout<<0<<endl;
        return;
    }
    for(ll i=2;i<=n;++i){
        if(arr[i]==i&&arr[i-1]==i-1&&(i==n||arr[i+1]==i+1)){
            brr[i]=1;a++;
        }
    }
    b=n-a;
    res=b*(b-1)%MOD*qexp(4,MOD-2,MOD)%MOD;
    d=qexp(2*(a+1)%MOD,MOD-2,MOD);
    for(ll i=1;i<=n;++i){
        if(brr[i]) c++;
        else{
            l=c*(c+1)%MOD;
            r=(a-c)*(a-c+1)%MOD;
            res=(res+(l+r)%MOD*d%MOD)%MOD;
        }
    }
    for(ll i=1;i<=n;++i) res=res*i%MOD;
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