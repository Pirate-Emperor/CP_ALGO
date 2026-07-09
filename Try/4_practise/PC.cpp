// by Pirate-King

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
ll arr[MAX_N],sz[MAX_N],hchi[MAX_N],hidx[MAX_N];
ll hd[MAX_N],pos[MAX_N],rpos[MAX_N],tail[MAX_N];
ar<ll,2> tree[4*MAX_N];
ll tim=0;

ll rec(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll d=rec(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return d;
}
ar<ll,2> merg(ar<ll,2> c1,ar<ll,2> c2){
    if(c1[1]==-1||c2[1]==-1) return{-1,-1};
    if(c1[1]==LINF&&c2[1]==LINF) return c1[0]==c2[0]?c1:(ar<ll,2>){-1,-1};
    if(c1[1]==LINF) return c1[0]%c2[1]==c2[0]?c1:(ar<ll,2>){-1,-1};
    if(c2[1]==LINF) return c2[0]%c1[1]==c1[0]?c2:(ar<ll,2>){-1,-1};
    ll x,y;
    ll g=rec(c1[1],c2[1],x,y);
    if(abs(c1[0]-c2[0])%g!=0) return{-1,-1};
    ll m2=c2[1]/g;
    ll df=c2[0]-c1[0];
    ll k=(df/g)*x;
    k%=m2;
    if(k<0) k+=m2;
    ll nA=c1[0]+c1[1]*k;
    ll nM=c1[1]/g*c2[1];
    if(nM>LINF)
    {
        if(nA>LINF) return{-1,-1};
        return{nA,LINF};
    }
    return{nA,nM};
}

void rec1(ll v){
    sz[v]=1;
    hchi[v]=-1;
    for(ll i=0;i<adj[v].size();i++){
        ll to=adj[v][i];
        dis[to]=dis[v]+arr[to];
        rec1(to);
        sz[v]+=sz[to];
        if(hchi[v]==-1||sz[to]>sz[hchi[v]]){
            hchi[v]=to;
            hidx[v]=i;
        }
    }
}
void rec2(ll v,ll h){
    hd[v]=h;
    pos[v]=tim;
    rpos[tim]=v;
    tim++;
    tail[h]=v;
    if(hchi[v]!=-1) rec2(hchi[v],h);
    for(ll to:adj[v]) if(to!=hchi[v]) rec2(to,to);
}
void rec3(ll nd,ll L,ll R){
    if(L==R){
        ll v=rpos[L];
        if(adj[v].empty()) tree[nd]={0,1};
        else{
            ll dv=adj[v].size();
            ll cv=(hidx[v]-dis[v])%dv;
            if(cv<0) cv+=dv;
            tree[nd]={cv,dv};
        }
        return;
    }
    ll md=(L+R)/2;
    rec3(2*nd,L,md);
    rec3(2*nd+1,md+1,R);
    tree[nd]=merg(tree[2*nd],tree[2*nd+1]);
}
ll rec4(ll nd,ll L,ll R,ll ql,ll qr,ll m){
    if(R<ql||L>qr) return -1;
    if(L>=ql&&R<=qr){
        if(tree[nd][1]!=-1){
            if(tree[nd][1]==LINF&&m==tree[nd][0]) return -1;
            if(tree[nd][1]!=LINF&&m%tree[nd][1]==tree[nd][0]) return -1;
        }
        if(L==R) return L;
        ll md=(L+R)/2;ll r=rec4(2*nd,L,md,ql,qr,m);
        if(r!=-1) return r;
        return rec4(2*nd+1,md+1,R,ql,qr,m);
    }
    ll md=(L+R)/2;
    ll r=rec4(2*nd,L,md,ql,qr,m);
    if(r!=-1) return r;
    return rec4(2*nd+1,md+1,R,ql,qr,m);
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>q;tim=0;
    dis.assign(n+1,0);
    for(ll i=1;i<=n;i++) adj[i].clear();
    for(ll i=2;i<=n;i++){
        cin>>x;
        adj[x].push_back(i);
    }
    for(ll i=2;i<=n;i++) cin>>arr[i];
    rec1(1);
    rec2(1,1);
    rec3(1,0,n-1);
    for(ll i=0;i<q;i++){
        cin>>m;
        ll cur=1;
        while(!adj[cur].empty()){
            ll h=hd[cur];
            ll t=tail[h];
            ll fal=rec4(1,0,n-1,pos[cur],pos[t],m);
            if(fal==-1) cur=t;
            else{
                ll u=rpos[fal];
                ll du=adj[u].size();
                c=(m+dis[u])%du;
                cur=adj[u][c];
            }
        }
        cout<<cur<<" ";
    }
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