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
    cin>>n;
    vector<int>arr(n+1),brr(n+1),crr(n+1,0),resu(n+1);
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        brr[i]=(n+1-arr[i]%(n+1))%(n+1);
        crr[brr[i]]++;
        resu[i]=i;
    }
    for(int i=1;i<=n;i++) {
        if(crr[i]==n){
            cout<<"-1\n";
            return;
        }
    }
    x=1;
    w=1;
    for(int i=2;i<=n;i++) {
        if(brr[i]!=brr[1]){
            w=i;
            break;
        }
    }
    for(int i=1;i<=n;i++){
        if(resu[i]==brr[i]){
        z=(brr[x]!=brr[i])?x:w;
        swap(resu[i],resu[z]);
        }
    }
    for(int i=1;i<=n;i++) cout<<resu[i] <<" ";
    cout<<endl;
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