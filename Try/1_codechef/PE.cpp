// by rumbling

#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define ull unsigned long long
#define int long long
 
const int MAX_N = 3e5 + 5;
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
struct Nd{ll m1,m2,lz;}
te[1200005];
void rec2(int nd){
  if(te[nd].lz!=0){
    int lz=te[nd].lz;
    te[2*nd].lz+=lz;
    te[2*nd].m1+=lz;
    te[2*nd].m2+=lz;
    te[2*nd+1].lz+=lz;
    te[2*nd+1].m1+=lz;
    te[2*nd+1].m2+=lz;
    te[nd].lz=0;
  }
}
void rec1(int nd,int l,int r){
  te[nd].lz=0;
  if(l==r){
    te[nd].m1=l;
    te[nd].m2=-l;
    return;
  }
  int md=l+(r-l)/2;
  rec1(2*nd,l,md);
  rec1(2*nd+1,md+1,r);
  te[nd].m1=max(te[2*nd].m1,te[2*nd+1].m1);
  te[nd].m2=max(te[2*nd].m2,te[2*nd+1].m2);
//   te[nd].m3=max(te[2*nd].m3,te[2*nd+1].m3);
}
void rec3(int nd,int l,int r,int ql,int qr,int v){
    if(ql>r||qr<l) return;
    if(ql<=l&&r<=qr){
        te[nd].lz+=v;
        te[nd].m1+=v;
        te[nd].m2+=v;
        return;
    }
    rec2(nd);
    int md=l+(r-l)/2;
    rec3(2*nd,l,md,ql,qr,v);
    rec3(2*nd+1,md+1,r,ql,qr,v);
    te[nd].m1=max(te[2*nd].m1,te[2*nd+1].m1);
    te[nd].m2=max(te[2*nd].m2,te[2*nd+1].m2);
}
int rec4(int nd,int l,int r,int ql,int qr){
    if(ql>r||qr<l) return -LINF;
    if(ql<=l&&r<=qr) return te[nd].m1;
    rec2(nd);
    int md=l+(r-l)/2;
    return max(rec4(2*nd,l,md,ql,qr),rec4(2*nd+1,md+1,r,ql,qr));
}
int rec5(int nd,int l,int r,int ql,int qr){
    if(ql>r||qr<l) return -LINF;
    if(ql<=l&&r<=qr) return te[nd].m2;
    rec2(nd);
    int md=l+(r-l)/2;
    return max(rec5(2*nd,l,md,ql,qr),rec5(2*nd+1,md+1,r,ql,qr));
}
void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>k;
    vector<int> arr(n+1);
    for(int i=1;i<=n;++i)cin>>arr[i];
    rec1(1,1,n);
    set<int> mpi;
    mpi.insert(0);
    mpi.insert(n+1);
    res=0;
    for(int t=1;t<=n;++t){
        y=arr[t];
        auto it=mpi.lower_bound(y);
        int ry=*it;
        --it;
        int ly=*it;
        mpi.insert(y);
        int ul=max(1LL,y-k);
        int ur=min(n,y+k);
        rec3(1,1,n,ul,ur,1);
        int x1=(ly+y+2)/2;
        // int x2=(ry+y-2)/2;
        int x2=(ry+y-1)/2;
        int md=(ly+ry)/2;
        l=max(1LL,x1);
        r=min(n,md);
        if(l<=r)res=max(res,rec4(1,1,n,l,r)-ly-1);
        l=max(1LL,md+1);
        r=min(n,x2);
        if(l<=r)res=max(res,rec5(1,1,n,l,r)+ry-1);
    }
    cout<<res<<endl;
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