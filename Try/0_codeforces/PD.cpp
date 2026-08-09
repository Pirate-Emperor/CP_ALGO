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
const int OFF=30;
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
vector<ll> resu;
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
    cin>>n;
    vector<ll>arr(n);
    for(int i=0;i<n;++i) cin>>arr[i];
    sort(all(arr));
    res=n;
    while(1){
        b=max(0LL,res-OFF);
        k=min(res,OFF);
        if(n-b>k){
            res++;
            continue;
        }
        priority_queue<ll>pq;
        for(int i=0;i<n-b;++i) pq.push(arr[i]);
        bool chk=true;
        for(int j=k-1;j>=0;--j){
            if(pq.empty()) break;
            z=pq.top();
            pq.pop();
            if(z<=0) break;
            z-=(1LL<<j);
            if(z>0){
                // chk=false;
                pq.push(z);
            }
            // else if(!chk) chk=true;
        }
        if(!pq.empty()){
            if (pq.top()>0) chk=false;
            else{

            }
        }
        if(chk) break;
        res++;
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