// by Pirate-King

#include <bits/stdc++.h>
 
using namespace std;
using cd=complex<double>;

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
const double PI=acos(-1);

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

void fft(vector<cd>&a, bool inv){
    ll n=a.size();
    for(int i=1,j=0;i<n;i++){
        ll b=n>>1;
        for(;j&b;b>>=1) j^=b;
        j^=b;
        if(i<j) swap(a[i],a[j]);
    }
    for(int k=2;k<=n;k<<=1){
        double ag=2*PI/k*(inv?-1:1);
        cd wl(cos(ag),sin(ag));
        for(int i=0;i<n;i+=k){
            cd w(1);
            for(int j=0;j<k/2;j++){
                cd u=a[i+j],v=a[i+j+k/2]*w;
                a[i+j]=u+v;
                a[i+j+k/2]=u-v;
                w*=wl;
            }
        }
    }
    if(inv) for(cd&x:a) x/=n;
}

ll n, m;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;
vector<ll> poly;

void bfs(ll s){
    dis.assign(n+1,-1);
    par.assign(n+1,0);
    vector<ll> q;
    dis[s]=0;
    q.push_back(s);
    ll h=0;
    while(h<q.size()){
        ll u=q[h++];
        for(ll v:adj[u]){
            if(dis[v]==-1){
                dis[v]=dis[u]+1;
                par[v]=u;
                q.push_back(v);
            }
        }
    }
}

bool rec(ll u,ll p,ll d,ll c,ll av){
    ll cnt=0;
    bool chk=(d==c);
    for(ll v:adj[u]){
        if(v!=p&&v!=av){
            if(rec(v,u,d+1,c,av)){
                cnt++;
                chk=true;
            }
        }
    }
    if(cnt>=2) poly[d]=1;
    return chk;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n;
    for(int i=1;i<=n;i++) adj[i].clear();
    for(int i=0;i<n-1;i++){
        ll u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs(1);
    x=1;
    for(int i=1;i<=n;i++) if(dis[i]>dis[x]) x=i;
    bfs(x);
    y=1;
    for(int i=1;i<=n;i++) if(dis[i]>dis[y]) y=i;

    vector<ll> path;
    ll cur=y;
    while(cur!=0){
        path.push_back(cur);
        cur=par[cur];
    }
    ll len=path.size()-1;
    c=len/2;
    ll u=path[c];
    ll v=path[c+1];

    poly.assign(c+1,0);
    poly[c]=1;
    rec(u,v,0,c,v);
    vector<ll> p1=poly;
    poly.assign(c+1,0);
    poly[c]=1;
    rec(v,u,0,c,u);
    vector<ll> p2=poly;

    ll sz=1;
    while(sz<2*c+2) sz<<=1;
    vector<cd> va(sz),vb(sz);
    for(int i=0;i<=c;i++){
        va[i]=p1[i];
        vb[i]=p2[i];
    }
    fft(va,false);
    fft(vb,false);
    for(int i=0;i<sz;i++) va[i]*=vb[i];
    fft(va,true);
    vector<ll> resu;
    for(int i=0;i<sz;i++) if(round(va[i].real())>0.001) resu.push_back(i+1);
    // for(int i=0;i<sz;i++) if(round(va[i].real())>0.5) resu.push_back(i+1);
    cout<<resu.size()<<" ";
    for(int i=0;i<resu.size();i++) cout<<resu[i]<<" ";
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