#include <bits/stdc++.h>
using namespace std;

struct SegTree{
    int n;
    vector<long long> sz,add;
    vector<bool> lz;
    SegTree(int n):n(n),sz(4*n,0),add(4*n,0),lz(4*n,false){}
    void push(int v, int l, int r){
        if (v>=4*n) return;
        int m=l+(r-l)/2;
        sz[2*v]+=add[v]*(m-l+1);
        sz[2*v+1]+=add[v]*(r-m);
        add[2*v]+=add[v];
        add[2*v+1]+=add[v];
        add[v]=0; 
    }
    void upd(int ql, int qr, int val, int v=1, int l=0, int r=-1){
        if (r==-1) r=n-1;
        if (ql>r || qr<l) return;
        if (ql<=l && r<=qr){
            sz[v]+=(r-l+1)*val;
            add[v]+=val;
            return;
        }
        push(v,l,r);
        int m=l+(r-l)/2;
        upd(ql,qr,val,2*v,l,m);
        upd(ql,qr,val,2*v+1,m+1,r);
        sz[v]=sz[2*v]+sz[2*v+1];
        return;
    }
    long long qry(int ql, int qr, int v=1, int l=0, int r=-1){
        if (r==-1) r=n-1;
        if (ql>r || qr<l) return 0;
        if (ql<=l && r<=qr) return sz[v];
        push(v,l,r);
        int m=l+(r-l)/2;
        return qry(ql,qr,2*v,l,m)+qry(ql,qr,2*v+1,m+1,r);
    }
};

struct BIT{
    int n;
    vector<long long> bit;
    BIT(int n):n(n),bit(n+1,0){}
    void upd(int i, int x){ for (;i<=n;i+=i&(-i)) bit[i]+=x;}
    long long qry(int i){ long long res=0; for(;i>0;i-=i&(-i)) res+=bit[i]; return res;}
    long long range(int l, int r){ return qry(r)-qry(l-1);}
};

const int SQRT=5e2;
struct MoQuery{
    int l,r,id;
    bool operator<(const MoQuery& o) const {
        return (l/SQRT == o.l/SQRT)?((l/SQRT)&1?r>o.r:r<o.r):(l<o.l);
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