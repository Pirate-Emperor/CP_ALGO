#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int MAX_N=2e5+5;
const int MOD=1e9+7; // Or 1e9+9
const int MOD_2=998244353


struct DSU{
    int n,comps;
    vector<int> par,rank,sz;
    DSU(int n):n(n),comps(n),rank(n,1),sz(n,1){
        par.resize(n);
        for (int i=0;i<n;i++) par[i]=i;
    }
    bool merge(int u,int v){
        u=find(u);
        v=find(v);
        if (u==v) return false;
        if (rank[v]>rank[u]) swap(u,v);
        par[v]=u;
        sz[u]+=sz[v];
        if (rank[u]==rank[v]) rank[u]++;
        comps--;
        return true;
    }
    int find(int u){
        return (par[u]==u)?u:(par[u]=find(par[u]));
    }
};

struct LCA{
    int n,l;
    vector<vector<int>> up,adj;
    vector<int> dep;
    LCA(int n):n(n),l(ceil(log(n))),up(n+1,vector<int>(l+1)),dep(n+1),adj(n+1){}
    void dfs(int u, int p=0,int d=0){
        up[u][0]=p;
        dep[u]=d;
        for (int i=1;i<=l;i++){
            up[u][i]=up[up[u][i-1]][i-1];
        }
        for (int v:adj[u]){
            if (v!=p) dfs(v,u,d+1);
        }
        return;
    }
    int lfs(int u, int v){
        if (dep[u]<dep[v]) swap(u,v);
        for (int i=l;i>=0;i--){
            if ((dep[u]-(1LL<<i))>=dep[v]) u=up[u][i];
        }
        if (u==v) return u;
        for (int i=l;i>=0;i--){
            if (up[u][i]!=up[v][i]){
                u=up[u][i];
                v=up[v][i];
            }
        }
        return up[u][0];
    }
}

int timer=0;
vector<int> tin,tout,low;
vector<bool> is_art;
vector<array<int,2>> bridges;
vector<vector<array<int,2>>> adj;
void setup_tarjan(int n){
    tin.resize(n);
    low.resize(n);
    is_art.resize(n);
    tin.assign(n,-1);
    is_art.assign(n,0);
    
}
void dfs_bridges(int u, int p=-1){
    tin[u]=low[u]=timer++;
    int child=0;
    for (auto [v,w]:adj[u]){
        if (v==p) continue;
        else if (tin[v]!=-1){
            low[u]=min(low[u],tin[v]);
        }
        else{
            dfs_bridges(v,u);
            low[u]=min(low[u],low[v]);
            child++;
            if (low[v]>tin[u]) bridges.push_back({u,v});
            if (low[v]>=tin[u] && p!=-1) is_art[u]=true;
        }
    }
    if (p==-1 && child>1) is_art[u]=true;
}

void euler_tour(int u, int p=-1){
    tin[u]=++timer;
    for (auto [v,w]:adj[u]){
        if (v==p) continue;
        euler_tour(v,u);
    }
    tout[u]=timer;
}
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