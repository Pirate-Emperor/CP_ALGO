#include <bits/stdc++.h>
using namespace std;

#define ll long long
// #define int long long
const int INF = 1e9;
const ll LINF = 1e18;
const ll MOD = 1e9+7; // or 1e9+7 or 998244353

// Batch 2
vector<long long> dijkstra(int s, int n, vector<vector<array<long long,2>>>& adj){
    vector<long long> dist(n,LINF);
    priority_queue<array<long long,2>,vector<array<long long,2>>,greater<array<long long,2>>> pq;
    pq.push({0,s});
    dist[s]=0;
    while(!pq.empty()){
        auto [curc,u] = pq.top();
        pq.pop();
        if (dist[u]<curc) continue;
        // dist[u]=curc;
        for (auto [v,c]: adj[u]){
            if (dist[v]>curc+c){
                dist[v]=curc+c;
                pq.push({curc+c,v});
            }
        }
    }
    return dist;
}

vector<long long> bfs_01(int s, int n, vector<vector<array<long long,2>>>& adj){
    deque<long long> q;
    vector<long long> dist(n,LINF);
    q.push_back(s);
    dist[s]=0;
    while(!q.empty()){
        auto u=q.front();
        q.pop_front();
        for (auto [v,c]: adj[u]){
            if (dist[v]>dist[u]+c){
                dist[v]=dist[u]+c;
                (c==1)?q.push_back(v):q.push_front(v);
            }
        }
    }
    return dist;
}

vector<int> topo_sort(int n, vector<vector<int>>& adj){
    vector<int> indeg(n,0);
    for (int u=0;u<n;u++){
        for (int v:adj[u]) indeg[v]++;
    }
    queue<int> q;
    vector<int> res;
    for (int i=0;i<n;i++) if (indeg[i]==0) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        res.push_back(u);
        for (int v:adj[u]){
            indeg[v]--;
            if (!indeg[v]) q.push(v);
        }
    }
    return (res.size()==n)?res:vector<int>();
}

struct Kuhn{
    int n,m,timer;
    vector<vector<int>> adj;
    vector<int> mt,vis;
    Kuhn(int n, int m):n(n),m(m),timer(0),adj(n),mt(m,-1),vis(n,0){}
    void add_edge(int u, int v){ adj[u].push_back(v);}
    bool dfs(int u){
        if (vis[u]==timer) return false;
        vis[u]=timer;
        for (auto v:adj[u]) if (mt[v]==-1 || dfs(mt[v])){
            mt[v]=u;
            return true;
        } 
        return false;
    }
    int get_matching(){
        int res=0;
        for (int i=0;i<n;i++){
            timer++;
            if (dfs(i)) res++;
        }
        return res;
    }
};

// Batch 7
template <typename Derived>
struct MatchingEngine{
    void process(){
        static_cast<Derived*>(this)->execute();
    }
};

struct CryptoEngine: public MatchingEngine<CryptoEngine>{
    void execute(){}
};

struct alignas(64) OrderBookCounter{
    uint64_t fills;
};

class BigInt{
    int* data;
    int sz, cap;
public:
    BigInt(int n=16):sz(0),cap(n){
        data = new int[cap]();
    }
    ~BigInt(){
        delete[] data;
    }
    BigInt(const BigInt& o):sz(o.sz),cap(o.cap){
        data = new int[cap]();  // () helps to 0-initialize every element
        for (int i=0;i<sz;i++) data[i]=o.data[i];
    }
    BigInt& operator=(const BigInt& o){
        if (this!=&o){
            sz=o.sz;
            cap=o.cap;
            delete[] data;
            data = new int[cap]();
            for (int i=0;i<sz;i++) data[i]=o.data[i];
        }
        return *this;
    }
    BigInt(BigInt&& o) noexcept:data(o.data),sz(o.sz),cap(o.cap){
        o.data=nullptr;
        o.sz=0;
        o.cap=0;
    }
    BigInt& operator=(BigInt&& o) noexcept{
        delete[] data;
        sz=o.sz;
        cap=o.cap;
        data=o.data;
        o.data=nullptr;
        o.sz=0;
        o.cap=0;
        return *this;
    }
};

void solve(){
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >>t;
    while(t--){
        solve();
    }
    return 0;
}