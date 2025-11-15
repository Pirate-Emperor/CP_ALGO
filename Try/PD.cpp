#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};
 
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
 
int n, m, x;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
int res=0;
void recur(int u, int dep)
{
    vis[u]=1;
    for (int it: adj[u])
    {
        if (vis[it]==0) 
        {
            par[it]=u;
            recur(it, dep+1);
        }
    }
    dis[u]=dep;
}
 
void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> x >> y;
    vector<array<ll,4>> mat;
    mat.push_back({0,0,x-1,y-1});
    auto arr=mat;
    while(n--){
        char c;
        cin >> c >> a >> b;
        int m = arr.size();
        vector<array<ll,4>> nmat;
        if (c=='X'){
            for (int i=0;i<m;i++){
                ll t1=arr[i][0];
                ll t2=arr[i][2];
                if (a<=t1){
                    nmat.push_back({arr[i][0],arr[i][1]+b,arr[i][2],arr[i][3]+b}); //up
                }
                else if (a>t2){
                    nmat.push_back({arr[i][0],arr[i][1]-b,arr[i][2],arr[i][3]-b}); // down
                }
                else{
                    nmat.push_back({arr[i][0],arr[i][1]-b,a-1,arr[i][3]-b}); // down
                    nmat.push_back({a,arr[i][1]+b,arr[i][2],arr[i][3]+b}); // up
                }
            }
        }
        else{
            for (int i=0;i<m;i++){
                ll t1=arr[i][1];
                ll t2=arr[i][3];
                if (a<=t1){
                    nmat.push_back({arr[i][0]+b,arr[i][1],arr[i][2]+b,arr[i][3]}); //right
                }
                else if (a>t2){
                    nmat.push_back({arr[i][0]-b,arr[i][1],arr[i][2]-b,arr[i][3]}); // left
                }
                else{
                    nmat.push_back({arr[i][0]-b,arr[i][1],arr[i][2]-b,a-1}); // left
                    nmat.push_back({arr[i][0]+b,a,arr[i][2]+b,arr[i][3]}); //right
                }
            }
        }
        arr=nmat;
        // for (int i=0;i<arr.size();i++){
        // for (auto it: arr[i]){
        //     cout << it << " ";
        // }}
        // cout << "\n||\n";
    }
    mat=arr;
    int m = mat.size();
    map<ll,vector<int>> mpx, mpy;
    vector<map<int,int>> adj(m);
    for (int i=0;i<m;i++){
        mpx[mat[i][0]].push_back(i);
        mpy[mat[i][1]].push_back(i);
    }
    for (int i=0;i<m;i++){
        int t1=mat[i][2]+1;
        int t2=mat[i][3]+1;
        for (int v: mpx[t1]){
            if (mat[v][1] <= mat[i][3] && mat[v][1] >= mat[i][1]) {
                adj[i][v]=1;
                adj[v][i]=1;
            }
        }
        for (int v: mpy[t2]){
            if (mat[v][0] <= mat[i][2] && mat[v][0] >= mat[i][0]) {
                adj[i][v]=1;
                adj[v][i]=1;
            }
        }
    }
    vector<int> vis(m,0);
    vector<ll> res;
    for (int i=0;i<m;i++){
        // for (auto it: mat[i]){
        //     cout << it << " ";
        // }
        // cout << endl;
        if (vis[i]==0){
            queue<int> q;
            q.push(i);
            ll tem=0;
            while(!q.empty()){
                int u = q.front();
                q.pop();
                vis[u]=1;
                tem+=(mat[u][3]-mat[u][1]+1)*(mat[u][2]-mat[u][0]+1);
                for (auto it: adj[u]){
                    if (vis[it.first]==0) {q.push(it.first);}
                }
            }
            res.push_back(tem);
        }
    }
    cout << res.size() << endl;
    for (int i=0;i<res.size();i++) cout << res[i] << " ";
    cout << endl;
    return;
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}