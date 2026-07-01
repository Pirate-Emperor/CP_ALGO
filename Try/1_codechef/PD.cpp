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
const ll LINF = 4e18;
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
    cin>>n>>k;
    vector<ll> arr(n),brr(n),crr(n),drr(n),err(n);
    vector<int> chk(n,0);
    for(int i=0;i<n;++i) cin>>arr[i];
    for(int i=0;i<n;++i) cin>>brr[i];
    for(int i=0;i<n;++i){
        crr[i]=arr[i]-(i+1);
        drr[i]=crr[i];
        if(!brr[i]) chk[i]=1;
    }
    ll mt=min(n-1,k-1);
    for(int t=0;t<=mt;++t){
        for(int i=0;i<n;++i){
            if(chk[i]) continue;
            ll j=i+1+t;
            if(j<n&&j<=i+k) if(arr[j]-arr[j-1]==1 &&drr[i]==crr[j-1]) chk[i]=1;
        }
        if(t<mt){
            // vector<ll> err(n,0);
            err[n-1]=drr[n-1]+brr[n-1];
            for(int i=0;i<n-1;++i) err[i]=min(drr[i]+brr[i],drr[i+1]);
            drr=err;
        }
    }
    q=k-1;
    if(q>=0){
        for(int i=0;i<n;++i){
            if(chk[i]) continue;
            ll gt=LINF;
            ll mk=min(n-1,i+q);
            ll cmin=brr[i];
            for(int j=i;j<=mk;++j){
                if(brr[j]<cmin)cmin=brr[j];
                ll v=crr[j]+(q-(j-i))*cmin;
                // ll v=crr[j]+(q-(j-i))*brr[j];
                if(v<gt)gt=v;
            }
            for(int j=i+1;j<=mk;++j) {
                if(!brr[j]&&crr[j]==gt){
                    chk[i]=1;
                    break;
                }
            }
        }
    }
    res=0;
    for(int i=0;i<n;++i) res+=chk[i];
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