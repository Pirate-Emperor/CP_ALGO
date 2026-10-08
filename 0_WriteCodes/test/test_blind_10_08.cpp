#include<bits/stdc++.h>
using namespace std;

#define ll long long
// #define int long long
const int MAX_N = 1e5;
const int INF = 1e9;
const ll LINF = 1e18;

// Thursday
int dis[MAX_N],dep[MAX_N];
void dfs_dep(int s, const vector<vector<array<int,2>>>& g){
    int mi=0;
    for (int v:g[s]){
        dfs_dis(v,g)
        mi=max(mi,dep[v]);
    }
    dis[s]=mi+1;
}

void bfs_dist(int s, const vector<vector<array<int,2>>>& g){
    queue<int> q;
    vector<int> dis(g.size(),-1);
    q.push(s);
    dis[s]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for (auto [v,w]:g[u]){
            if (dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                q.push(v);
            }
        }
    }
    return;
}

vector<array<int,2>> direc={{0,1},{0,-1},{1,0},{-1,0}};
int dfs_grid(int r, int c, const vector<vector<int>>& g, vector<vector<int>>& vis){
    int n=g.size();
    int m=g[0].size();
    int score=0;
    vis[r][c]=1;
    for (int [dr,dc]:direc){
        nr=r+dr;
        nc=c+dc;
        if (nr>=n || nr<0 || nc>=m || nc<0) continue;
        if (vis[nr][nc]==0){
            // vis[nr][nc]=1;
            score=max(score,dfs_grid(nr,nc,g,vis));
            // vis[nr][nc]=0;
        }
    }
    score+=g[r][c];
    return score;
}

vector<long long> dijkstra(int s, const vector<vector<array<int,2>>>& adj){
    priority_queue<array<long long,2>,vector<array<long long,2>>,greater<array<long long,2>>> pq;
    int n=adj.size();
    vector<long long> dist(n,LINF);
    pq.push({0,s});
    dist[s]=0;
    while(!pq.empty()){
        auto [wc,u]=pq.top();
        pq.pop();
        if (wc!=dist[u]) continue;
        for (auto [v,w]:adj[u]){
            if (dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                pq.push(dist[v],v);
            }
        }
    }
    return dist;
}

vector<int> topo_sort(vector<vector<int>>& g){
    int n=g.size();
    vector<int> indeg(n,0),vert;
    queue<int> cur;
    for (int u=0;u<n;u++){
        for (auto v:g[u]){
            indeg[v]++;
        }
    }
    for (int i=0;i<n;i++) if (indeg[i]==0) cur.push(i);
    while(!cur.empty()){
        u=cur.front();
        cur.pop();
        vert.push_back(u);
        for (int v:g[u]){
            indeg[v]--;
            if (indeg[v]==0) cur.push(v);
        }
    }
    if (vert.size()<n) return vector<int>();
    return vert;
}

struct DSU{
    int n,comps;
    vector<int> par,rank,cnt;
    DSU(int n):n(n),comps(n),par(n),rank(n,0),cnt(n,1){
        iota(par.begin(),par.end(),0);
    }
    int find(int u){
        return (par[u]==u)?u:(par[u]=find(par[u]));
    }
    bool merge(int u, int v){
        u=find(u);
        v=find(v);
        if (u==v) return false;
        if (rank[v]>rank[u]) swap(u,v);
        // if (cnt[v]>cnt[u]) swap(u,v);
        par[v]=u;
        if (rank[v]==rank[u]) rank[u]++;
        cnt[u]+=cnt[v];
        comps--;
        return true;
    }
};

// 1-based indexing for the graph vertices
struct LCA{
    int n,l;
    vector<vector<int>> up,adj;
    vector<int> dep;
    LCA(int n):n(n),l(ceil(log2(n))),dep(n+1,0),up(n+1,vector<int>(l+1,0)),adj(n+1){
    }
    void add_edges(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void build(int s, int p=0, int d=0;){
        up[s][0]=p;
        dep[s]=d;
        for (int i=1;i<=l;i++){
            up[s][i]=up[up[s][i-1]][i-1];
        }
        for (auto v: adj[s]){
            if (v==p) continue;
            d=max(d,build(v,s,d+1));    
        }
        return; 
    }
    int lca(int u, int v){
        if (u==v) return u;
        if (dep[u]<dep[v]) swap(u,v);
        for (int i=l;i>=0;i--){
            if (dep[u]-(1LL<<i)>=dep[v]) u=up[u][i];
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