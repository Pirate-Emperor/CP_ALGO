// by Pirate-King

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ar array

const int MAX_N=2e5+5;
ll n, m;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;
vector<ll> poly;
static mt19937_64 rnd(1337);

void recur(ll u,ll &x,ll &y){
        vis[u]=1;x++;y+=adj[u].size();
        for(ll v:adj[u])if(!vis[v])recur(v,x,y);
    }

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n>>m;
    for(ll i=0;i<=n;i++)adj[i].clear();
    edges.clear();
    vis.assign(n+1,0);
    dis.assign(n+1,0);
    for(ll i=0;i<m;i++){
        cin>>l>>r;
        w=rnd();
        dis[l-1]^=w;
        dis[r]^=w;
    }
    vector<ll> arr;
    for(ll i=0;i<=n;i++){
        if(!vis[i]){
            x=0;y=0;
            recur(i,x,y);
            y/=2;
            // if(x==1) arr.push_back(i);
            // else if(y==x-1){
            //     bool chk=0;
            //     for(ll j=0;j<=n;j++){
            //         if(!chk) for(ll v:adj[j]) if(abs(j-v)>1){
            //             if(!mpi[{j,j+1}]){
            //                 edges.push_back({j+1,j+1});
            //                 mpi[{j,j+1}]=mpi[{j+1,j}]=1;
            //                 chk=1;break;
            //             }
            //             if(!mpi[{j+1,v}]){
            //                 // edges.push_back({min(j+1,v)+1,max(j,v+1)});
            //                 edges.push_back({min(j+1,v)+1,max(j+1,v)});
            //                 mpi[{j+1,v}]=mpi[{v,j+1}]=1;
            //                 chk=1;break;
            //             }
            //         }
            //     }
            //     if(!chk){
            //         for(ll j=0;j<=n;j++) if(!chk){
            //                 for(ll v:adj[j]) for(ll u:adj[v]){
            //                     if(u!=j&&!mpi[{j,u}]){
            //                     // edges.push_back({min(j,u)+1,max(j+1,u-1)});
            //                         edges.push_back({min(j,u)+1,max(j,u)});
            //                     mpi[{j,u}]=mpi[{u,j}]=1;
            //                     chk=1;
            //                     break;
            //                 }
            //             }
            //         }
            //     }
            //     if(!chk)arr.push_back(i);
            // }
        }
    }
    for(ll i=1;i<n;i++)dis[i]^=dis[i-1];
    map<ll,ll> lst;
    for(ll i=0;i<n;i++){
        if(lst.count(dis[i])&&lst[dis[i]]+1>a){
            a=lst[dis[i]]+1;b=i;arr.push_back(a);
        }
        lst[dis[i]]=i;
    }
    k=arr.size();g=k/2;
    if(k%2){
        edges.push_back({1,(int)arr[g]});
        for(ll i=0;i<g;i++) edges.push_back({(int)arr[i]+1,(int)arr[i+g+1]});
    }
    else if(k){
        set<ll> st(dis.begin(),dis.begin()+arr[0]);
        for(ll i=b;i<n;i++) if(st.count(dis[i])) c=1;
        if(c){
            edges.push_back({1,(int)arr[g-1]}),edges.push_back({1,(int)arr[k-1]});
        }
        for(ll i=0;i<g-c;i++) edges.push_back({(int)arr[i]+1,(int)arr[i+g]});
    }
    res=edges.size();
    cout<<res<<"\n";
    for(int i=0;i<edges.size();i++){
        cout<<edges[i][0]<<" "<<edges[i][1]<<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if(cin>>t){
        while(t--){
            solve();
        }
    }
    return 0;
}