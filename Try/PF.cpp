// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e6+5;
const int MOD = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;
const int OFF=40;
const int MDIF=100;
const int G=3;

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

void fft(vector<int>&a,bool inv){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int bt=n>>1;
        for(;j&bt;bt>>=1)j^=bt;
        j^=bt;
        if(i<j)swap(a[i],a[j]);
    }
    for(int l=2;l<=n;l<<=1){
        int wl=qexp(G,(MOD-1)/l,MOD);
        if(inv)wl=qexp(wl,MOD-2,MOD);
        for(int i=0;i<n;i+=l){
            int w=1;
            for(int j=0;j<l/2;j++){
                int u=a[i+j],v=(a[i+j+l/2]*w)%MOD;
                a[i+j]=(u+v<MOD?u+v:u+v-MOD);
                a[i+j+l/2]=(u-v>=0?u-v:u-v+MOD);
                w=(w*wl)%MOD;
            }
        }
    }
    if(inv){
        int ni=qexp(n,MOD-2,MOD);
        for(int&x:a)x=(x*ni)%MOD;
    }
}

vector<int> primes,is_prime,spf,mobius,phi;

void sieve(int n){
    primes.clear();
    is_prime.assign(n+1,1);
    spf.assign(n+1,0);
    mobius.assign(n+1,0);
    phi.assign(n+1,0);
    is_prime[0]=is_prime[1]=0;
    mobius[1]=phi[1]=1;
    for(ll i=2;i<=n;i++){
        if(is_prime[i]){
            primes.push_back(i);
            spf[i]=i;
            mobius[i]=-1;
            phi[i]=i-1;
        }
        for(auto p:primes){
            if(i*p>n||p>spf[i])break;
            is_prime[i*p]=0;
            spf[i*p]=p;
            mobius[i*p]=(spf[i]==p)?0:-mobius[i];
            phi[i*p]=(spf[i]==p)?phi[i]*p:phi[i]*phi[p];
        }
    }
}

int n, m, x;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
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
    ll a=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>m;
    vector<ll> arr(n+1);
    for(ll i=1;i<=n;++i) cin>>arr[i];
    ll res=0;
    if(arr[1]!=1){
        arr[1]=1;
        res++;
    }
    if(arr[n]!=m){
        arr[n]=m;
        res++;
    }
    vector<ll> brr(n+1,-INF),crr(n+1,-INF);
    ll msz=n+m+5;
    vector<ll> drr(msz,-INF), bit(msz+1,-INF);
    auto fa=[&](ll i,ll v){
        for(;i<=msz;i+=i&-i) bit[i]=max(bit[i],v);
    };
    auto get=[&](ll i){
        ll rt=-INF;
        for(;i>0;i-=i&-i) rt=max(rt,bit[i]);
        return rt;
    };
    brr[1]=1;
    crr[1]=1;
    ll d1=1-arr[1]+m+1;
    drr[d1]=1;
    fa(d1,1);
    for(int j=2;j<=n;++j){
        if(arr[j]<=j&&arr[j]>=j+m-n){
            ll v1=crr[j-arr[j]];
            ll v2=get(j);
            ll v3=drr[j-arr[j]+m+1];
            brr[j]=1+max({v1,v2,v3});
        }
        if(brr[j]<0)brr[j]=-INF;
        crr[j]=max(crr[j-1],brr[j]);
        if(brr[j]>0){
            ll dj=j-arr[j]+m+1;
            drr[dj]=max(drr[dj],brr[j]);
            fa(dj,brr[j]);
        }
    }
    res+=n-brr[n];
    cout<<res<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // sieve(MAX_N);
    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}