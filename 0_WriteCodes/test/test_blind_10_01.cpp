#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9+7; // 1e9+9 or 988244353

// Batch-4

struct DSU{
    int comp;
    vector<int> rank,sz,par;
    DSU(int n):comp(n),rank(n,0),sz(n,0),par(n){
        iota(par.begin().par.end(),0);
    }
    int find(int u){
        return par[u]=(u==par[u])?u:find(par[u]);
    }
    bool merge(int u, int v){
        u=find(u);
        v=find(v);
        if (u==v) return false;
        if (rank[v]>rank[u]) swap(u,v);
        // if (sz[v]>sz[u]) swap(u,v);
        par[v]=u;
        if (rank[u]==rank[v]) rank[u]++;
        // sz[u]+=sz[v];
        comp--;
        return true;
    }
};

// Here the vertices are stored in 1-based indexing (so `0` can be used as parent for root)
struct LCA{
    int n,lgn;
    vector<int> dep;
    vector<vector<int>> adj,larr;
    LCA(int n):n(n),adj(n+1),dep(n+1,-1),lgn(ceil(log2(n))),larr(n+1,vector<int>(lgn+1,0)) {}
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int u, int p=0, int d=0){
        dep[u]=d;
        larr[u][0]=p;
        for (int i=1;i<=lgn;i++){
            larr[u][i]=larr[larr[u][i-1]][i-1];
        }
        for (int v:adj[u]){
            if (dep[v]==-1) dfs(v,u,d+1);
        }
    }
    int lca(int u, int v){
        if (dep[v]>dep[u]) swap(u,v);
        for (int i=lgn;i>=0;i--){
            if (dep[v]+(1<<i)<=dep[u]) u=larr[u][i];
        }
        if (u==v) return u;
        for (int i=lgn;i>=0;i--){
            if (larr[u][i]!=larr[v][i]){
                u=larr[u][i];
                v=larr[v][i];
            }
        }
        u=larr[u][0];
        return u;
    }
};

struct Tarjan{
    int n,timer;
    vector<int> tin,low;
    vector<vector<int>> adj;
    vector<array<int,2>> bridges;
    vector<bool> is_art;
    Tarjan(int n):n(n),timer(0),tin(n,-1),low(n,0),adj(n),is_art(n,false){}
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int u, int p=-1){
        tin[u]=low[u]=timer++;
        int child=0;
        for (int v:adj[u]){
            if (v==p) continue;
            if (tin[v]==-1){
                dfs(v,u);
                low[u]=min(low[u],low[v]);
                child++;
                if (low[v]>tin[u]) bridges.push_back({u,v});
                if (low[v]>=tin[u] && p!=-1) is_art[u]=true;
            }
            else {
                low[u]=min(low[u],tin[v]);
            }
        }
        if (p==-1 && child>1) is_art[u]=true;
    }
};

// Applied on Tree
struct EulerTour{
    int n,timer;
    vector<int> tin,tout;
    vector<vector<int>> adj;
    EulerTour(int n):n(n),timer(0),tin(n,0),tout(n,0),adj(n){}
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int u, int p=-1){
        tin[u]=++timer;
        for (int v:adj[u]){
            if (v!=p) dfs(v,u);
        }
        tout[u]=timer;
    }
};

void solve(){

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}