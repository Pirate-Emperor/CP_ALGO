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
    cin>>n>>m;
    for(ll i=0;i<2*n;i++) adj[i].clear();
    dis.assign(2*n,0);
    vis.assign(2*n,0);
    queue<ll> qu;
    for(ll i=0;i<m;i++){
        cin>>a>>b>>c;
        b--;
        c--;
        if(a==1){
            adj[2*b+1].push_back(2*c);
            dis[2*c]++;
            if(b!=c){
                adj[2*c+1].push_back(2*b);
                dis[2*b]++;
            }
        }
        else{
            adj[2*b].push_back(2*c+1);
            dis[2*c+1]++;
            if(b!=c){
                adj[2*c].push_back(2*b+1);
                dis[2*b+1]++;
            }
        }
    }
  
    for(ll i=0;i<2*n;i++) if(!dis[i]) qu.push(i);
    resu.clear();
    while(!qu.empty()){
        x=qu.front();
        qu.pop();
        resu.push_back(x);
        w=(x%2==0)?1:0;
        for(auto v:adj[x]){
            vis[v]=max(vis[v],vis[x]+w);
            if(--dis[v]==0) qu.push(v);
        }
    }
    if(resu.size()<2*n) cout<<"NO\n";
    else{
        cout<<"YES\n";
        for(ll i=0;i<n;i++) {
            res=vis[2*i]-vis[2*i+1];
            cout<<res<<" ";
        }
        cout<<endl;
    }
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