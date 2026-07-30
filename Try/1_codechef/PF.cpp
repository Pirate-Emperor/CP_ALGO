// by rumbling

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
vector<ll> tempc[MAX_N],tempd[MAX_N];
ll res=0;

ll bit[2][MAX_N];
ll node[MAX_N*2];

ll rec(ll i){
    return par[i]==i?i:par[i]=rec(par[i]);
}

void add(ll p,ll i,ll v){
    for(;i<=n;i+=i&-i)bit[p][i]+=v;
}
void radd(ll p,ll l,ll r,ll v){
    add(p,l,v);
    add(p,r+1,-v);
}

ll qry(ll p,ll i){
    ll s=0;
    for(;i>0;i-=i&-i)s+=bit[p][i];
    return s;
}
ll cnt(ll l,ll r,ll p){
    return l>r?0:(r-l+1)/2+((r-l+1)%2&&l%2==p);
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    vector<ll> arr(n+2,0),brr(n+2,0),crr(n+2,n+2),drr(n+2,n+2);
    for(int i=1;i<=n;++i) cin>>arr[i];
    vector<ll> st;
    for(int i=1;i<=n;++i){
        while(st.size()&&arr[st.back()]<arr[i]) st.pop_back();
        brr[i]=st.empty()?0:st.back();
        st.push_back(i);
    }
    st.clear();
    for(int i=n;i>=1;--i){
        while(st.size()&&arr[st.back()]>arr[i]) st.pop_back();
        crr[i]=st.empty()?n+1:st.back();
        st.push_back(i);
    }
    for(int i=0;i<=2*n+5;++i) node[i]=INF;
    for(int i=n;i>=1;--i){
        if(i<n&&arr[i]<arr[i+1]){
            ll li=arr[i]+1+n,ri=arr[i+1]-1+n+1;
            x=INF;
            for(;li<ri;li>>=1,ri>>=1){
                if(li&1) x=min(x,node[li++]);
                if(ri&1) x=min(x,node[--ri]);
            }
            if(x!=INF) drr[i]=x;
        }
        ll p=arr[i]+n;
        for(node[p]=i;p>1;p>>=1) node[p>>1]=min(node[p],node[p^1]);
    }
    par.assign(n+2,0);
    for(int i=0;i<=n+1;++i){
        tempc[i].clear();
        tempd[i].clear();
        par[i]=i;
        bit[0][i]=bit[1][i]=0;
    }
    for(int i=1;i<=n;++i){
        if(crr[i]<=n) tempc[crr[i]].push_back(i);
        if(drr[i]<=n) tempd[drr[i]].push_back(i);
    }
    res=0;
    for(int i=1;i<=n;++i){
        a+=i-brr[i];
        for(ll v:tempc[i]){
            // w=qry(v%2,v);
            // d=v-brr[v]-w;
            // par[rec(v)]=rec(v+1);
            y=rec(v);
            radd(v%2,v,y,1);
            radd(1-(v%2),v,y,-1);
            z+=cnt(v,y,v%2)-cnt(v,y,1-(v%2));
        }
        for(ll u:tempd[i]){
            w=qry(u%2,u);
            d=u-brr[u]-w;
            par[rec(u)]=rec(u+1);
            y=rec(u+1);
            l=u+1;
            radd(l%2,l,y,d);
            radd(1-(l%2),l,y,-d);
            // radd(1-(l%2),l,y,-1);
            z+=d*cnt(l,y,l%2)-d*cnt(l,y,1-(l%2));
            // z+=d*cnt(l,y,l%2)-(d-1)*cnt(l,y,1-(l%2))-cnt(u,y,1-(l%2));
        }
        res+=i*(i+1)/2-a+z;
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