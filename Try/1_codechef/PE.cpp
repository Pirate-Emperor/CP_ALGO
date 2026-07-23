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
    cin>>n;
    vector<ll> arr(n+1),brr(n+1,0),crr(n+1,0),drr(n+1,n+1),err;
    for(ll i=1;i<=n;++i){
        cin>>arr[i];
        brr[i]=brr[i-1]+arr[i];
    }
    for(ll i=1;i<=n;++i){
        while(!err.empty()&& arr[err.back()]<arr[i]) err.pop_back();
        crr[i]=err.empty()?0:err.back();
        err.push_back(i);
    }
    err.clear();
    for(ll i=n;i>=1;--i){
        while(!err.empty()&& arr[err.back()]<=arr[i]) err.pop_back();
        drr[i]=err.empty()?n+1:err.back();
        err.push_back(i);
    }
    for(ll i=2;i<=n-1;++i){
        a=max(0ll,crr[i]);b=i-2;x=i+1;y=drr[i]-1;
        if(a>b||x>y)continue;
        w=b-a+1;z=y-x+1;
        if(w<=z){
            for(l=a;l<=b;++l){
                q=brr[l]+2ll*arr[i]-1;
                k=upper_bound(brr.begin()+x,brr.begin()+y+1,q)-brr.begin();
                if(k-x>0) c+=k-x;
            }
        }
        else{
            for(r=x;r<=y;++r){
                q=brr[r]-2ll*arr[i];
                k=upper_bound(brr.begin()+a,brr.begin()+b+1,q)-brr.begin();
                // if(k-x>0) c+=k-x;
                if(b-k+1>0) c+=b-k+1;
            }
        }
    }
    res=n*(n+1)/2-c;
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