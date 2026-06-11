#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long

const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18+100;
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
vector<array<int,2>> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> curS;
int res=0;
void recur(int N, int node, int cur)
{
    if (cur>(N-1)/2 || node>=N) return;
    for (int i=node;i<N;i++)
    {
        curS[i]=1;
        int temp=0;
        for (int j=0;j<m;j++)
        {
            temp+=curS[edges[j][0]]!=curS[edges[j][1]];
        }
        res=max(temp,res);
        recur(N, i+1,cur+1);
        curS[i]=0;
    }
}

struct ST{
    int n;
    vector<int> c1,mx,lz;
    ST(int N){
        n=N;
        c1.assign(4*n+1,0);
        mx.assign(4*n+1,0);
        lz.assign(4*n+1,-1);
        bld(1,1,n);
    }
    void bld(int nd,int l,int r){
        lz[nd]=-1;
        if(l==r){
            c1[nd]=0;
            mx[nd]=0;
            return;
        }
        int m=l+(r-l)/2;
        bld(2*nd,l,m);
        bld(2*nd+1,m+1,r);
        pu(nd);
    }
    void app(int nd,int ln,int v){
        if(v==0){
            c1[nd]=0;
            mx[nd]=0;
            lz[nd]=0;
        }else if(v==1){
            c1[nd]=ln;
            mx[nd]=-INF;
            lz[nd]=1;
        }
    }
    void pd(int nd,int l,int r){
        if(lz[nd]!=-1){
            int m=l+(r-l)/2;
            app(2*nd,m-l+1,lz[nd]);
            app(2*nd+1,r-m,lz[nd]);
            lz[nd]=-1;
        }
    }
    void pu(int nd){
        c1[nd]=c1[2*nd]+c1[2*nd+1];
        mx[nd]=max(mx[2*nd],c1[2*nd]+mx[2*nd+1]);
    }
    void upd(int nd,int l,int r,int ql,int qr,int v){
        if(ql>r||qr<l) return;
        if(ql<=l&&r<=qr){
            app(nd,r-l+1,v);
            return;
        }
        pd(nd,l,r);
        int m=l+(r-l)/2;
        upd(2*nd,l,m,ql,qr,v);
        upd(2*nd+1,m+1,r,ql,qr,v);
        pu(nd);
    }
    int ans(){
        return max((int)0,mx[1])+1;
    }
    int gt1(){
        return c1[1];
    }
};

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>q;
    ST st(n);
    for(int i=0;i<q;++i){
        int ty;
        cin>>ty;
        if(ty==0){
            int l,r;
            cin>>l>>r;
            st.upd(1,1,n,l,r,0);
        }
        else if(ty==1){
            int l,r;
            cin>>l>>r;
            st.upd(1,1,n,l,r,1);
        }
        else if(ty==2){
            int o=st.gt1();
            int z=n-o;
            if(z>0) st.upd(1,1,n,1,z,0);
            if(o>0) st.upd(1,1,n,z+1,n,1);
        }
        cout<<st.ans()<<endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}