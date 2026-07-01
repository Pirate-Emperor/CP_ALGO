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
// void recur(int u, int dep)
// {
//     vis[u]=1;
//     for (int it: adj[u])
//     {
//         if (vis[it]==0) 
//         {
//             par[it]=u;
//             recur(it, dep+1);
//         }
//     }
//     dis[u]=dep;
// }

ll arr[MAX_N];
ll brr[MAX_N];
ll crr[MAX_N];
ll bit1[MAX_N];
ll bit2[MAX_N];
ll resu[MAX_N];

void ad1(int i,int v){
    for(;i<=n;i+=i&-i) bit1[i]+=v;
}
int qu1(int i){ 
    int s=0;
    for(;i;i-=i&-i) s+=bit1[i];
    return s;
}
void ad2(int i,int v){ 
    for(;i<=n;i+=i&-i) bit2[i]+=v;
}
int qu2(int i){
    int s=0;
    for(;i;i-=i&-i) s+=bit2[i];
    return s;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    for(int i=1;i<=n;i++)bit1[i]=bit2[i]=0;
    set<int> st;
    for(int i=1;i<=n;i++)st.insert(i);
    for(int i=1;i<=n;i++){
        char ch;cin>>ch>>brr[i];
        if(ch>='A'&&ch<='Z')ch+=32;
        arr[i]=(ch=='p'?1:0);
        if(arr[i])st.erase(brr[i]);
    }
    dis.assign(n+1,0);
    for(int i=1;i<=n;i++){
        if(arr[i]){
            x=brr[i];
            crr[i]=(i-1)-qu1(x);
            dis[i]=dis[i-1]+crr[i];
            ad1(x,1);
        }else{
            y=brr[i];
            dis[i]=y;
            crr[i]=dis[i]-dis[i-1];
            k=(i-1)-crr[i];
            int pk=0;
            if(k>0){
                l=1;r=n;
                while(l<=r){
                    int md=l+(r-l)/2;
                    if(qu1(md)>=k){pk=md;r=md-1;}
                    else l=md+1;
                }
            }
            auto it=st.upper_bound(pk);
            int u=*it;
            ad1(u,1);
            st.erase(it);
        }
    }
    for(int i=1;i<=n;i++)ad2(i,1);
    for(int i=n;i>=1;i--){
        if(arr[i]){
            x=brr[i];
            resu[i]=x;
            ad2(x,-1);
        }else{
            int tg=i-crr[i];
            l=1;r=n;int u=-1;
            while(l<=r){
                int md=l+(r-l)/2;
                if(qu2(md)>=tg){u=md;r=md-1;}
                else l=md+1;
            }
            resu[i]=u;
            ad2(u,-1);
        }
    }
    for(int i=1;i<=n;i++)cout<<resu[i]<<" ";
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