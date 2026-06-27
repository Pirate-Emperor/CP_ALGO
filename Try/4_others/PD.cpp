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
// struct st{
//     ll id;
//     mutable ll ln,t;
//     bool operator < (const st &A) const { return id<A.id;} 
// };
 
// ll gcd(ll a, ll b) {
//     return b ? gcd(b, a % b) : a;
// }
 
// ll qexp(ll a, ll b, ll m) {
//     ll res = 1;
//     while (b) {
//         if (b % 2) res = res * a % m;
//         a = a * a % m;
//         b /= 2;
//     }
//     return res;
// }
 
int n, m, x;
// vector<int> adj[MAX_N];
// vector<array<int,2>> edges;
// vector<ll> vis;
// vector<ll> dis;
// vector<ll> par;
ull res=0;
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

// int mu[MAX_N];
// bool isc[MAX_N];
// vector<int> p;

// void pc(){
//     fill(isc+2,isc+MAX_N,1);
//     mu[1]=1;
//     for(int i=2;i<MAX_N;i++){
//         if(isc[i]){p.push_back(i);mu[i]=-1;}
//         for(int x:p){
//             if(i*x>=MAX_N)break;
//             isc[i*x]=0;
//             if(i%x==0){mu[i*x]=0;break;}
//             else mu[i*x]=-mu[i];
//         }
//     }
// }

void solve(){
    ll d=0,t=0;
    ll l=0,r=0,px=-1,cx=0,c=0;
    ull ln=0,cb=0;
    string s;
    cin>>n>>s;
    t=n*(n+1)/2;
    vector<ll> arr(3,0);
    arr[0]=1;
    ll b=0;
    for(int i=0;i<n;i++){
        d+=s[i]=='0'?1:-1;
        c=(d%3+3)%3;
        b+=arr[c];
        arr[c]++;
    }
    ll v=t-b;
    ll o=0;l=1;
    for(int i=1;i<n;i++){
        if(s[i]!=s[i-1]) l++;
        else{
            ll y=(l-1)/2;
            o+=y*(l-y-1);
            l=1;
        }
    }
    ll y=(l-1)/2;
    o+=y*(l-y-1);
    res=v-o;
    cout<<res<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // pc();
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}