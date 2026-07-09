#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e6;
const int MOD = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;
const int MXN = 2e5+5;

// const int mod = 7340033;
const int mod = (119 << 23) + 1;
const int root = 62;
int root_1 = 0;
const int root_pw = 1 << 23;

ll qexp(ll a, ll b, ll m=MOD) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int fct[MXN],ifct[MXN];

int minv(int n){
    return qexp(n,MOD-2);
}

void prec(){
    fct[0]=1;
    ifct[0]=1;
    for(int i=1;i<MXN;i++)fct[i]=(fct[i-1]*i)%MOD;
    ifct[MXN-1]=minv(fct[MXN-1]);
    for(int i=MXN-2;i>=1;i--)ifct[i]=(ifct[i+1]*(i+1))%MOD;
}

int ncr(int n,int r){
    if(r<0||r>n)return 0;
    return fct[n]*ifct[r]%MOD*ifct[n-r]%MOD;
}

void ntt(vector<int>&a,bool inv){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int b=n>>1;
        for(;j&b;b>>=1)j^=b;
        j^=b;
        if(i<j)swap(a[i],a[j]);
    }
    for(int l=2;l<=n;l<<=1){
        int wl=qexp(3,(MOD-1)/l);
        if(inv)wl=minv(wl);
        for(int i=0;i<n;i+=l){
            int w=1;
            for(int j=0;j<l/2;j++){
                int u=a[i+j],v=(a[i+j+l/2]*w)%MOD;
                a[i+j]=u+v<MOD?u+v:u+v-MOD;
                a[i+j+l/2]=u-v>=0?u-v:u-v+MOD;
                w=(w*wl)%MOD;
            }
        }
    }
    if(inv){
        int ni=minv(n);
        for(int&x:a)x=(x*ni)%MOD;
    }
}

vector<int> mult(const vector<int>&a,const vector<int>&b){
    if(a.empty()||b.empty())return {};
    int n=1;
    while(n<a.size()+b.size())n<<=1;
    vector<int> fa(a.begin(),a.end()),fb(b.begin(),b.end());
    fa.resize(n);
    fb.resize(n);
    ntt(fa,0);
    ntt(fb,0);
    for(int i=0;i<n;i++)fa[i]=(fa[i]*fb[i])%MOD;
    ntt(fa,1);
    vector<int> r(a.size()+b.size()-1);
    for(int i=0;i<r.size();i++)r[i]=fa[i];
    return r;
}

void solve(){
    ll n=0,l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    string S;
    cin>>S;
    vector<vector<int>> arr(n+1);
    for(int i=2;i<=n;i++){
        cin>>k;
        arr[k].push_back(i);
    }
    
    vector<vector<ll>> dp(n+1,vector<ll>(2,0));
    auto dfs=[&](auto& f,int u)->void{
        for(int v:arr[u])f(f,v);
        for(int t=0;t<2;t++){
            ll nw=1;
            ll hz=t;
            for(int i=(int)arr[u].size()-1;i>=0;i--){
                int v=arr[u][i];
                ll w0=0,w1=0;
                char ch=S[v-2];
                if(ch=='0'||ch=='?')w0=dp[v][hz];
                if((ch=='1'||ch=='?')&&hz==1)w1=dp[v][hz];
                nw=(nw*(w0+w1))%1000000007;
                hz=1;
            }
            dp[u][t]=nw;
        }
    };
    dfs(dfs,1);
    ll res=dp[1][0];
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