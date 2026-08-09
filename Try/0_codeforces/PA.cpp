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
// void recur(int u, int pre)
// {
//     vis[u]=1;
//     for (int it: adj[u])
//     {
//         if (vis[it]==0) 
//         {
//             par[it]=u;
//             recur(it, pre+1);
//         }
//     }
//     dis[u]=pre;
// }

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>k;
    string s;
    cin>>s;
    m=2*n;
    for(int i=0;i<m;++i){
        y+=s[i]=='1'?1:(-1);
        if(y<w){
            w=y;
            x=i+1;
        }
    }
    x%=m;
    vector<ll> cnt(m,0);
    vector<ar<ll,3>> st;
    for(int i=0;i<m;++i){
        z=(x+i)%m;
        if(s[z]=='1') st.push_back({z,0,1});
        else if(!st.empty()){
            auto[it,pre,chk]=st.back();
            st.pop_back();
            ll swp=(chk&&pre+1<=k);
            if(swp) cnt[it]=1;
            if(!st.empty()){
                st.back()[1]=max(st.back()[1],pre+1);
                if(!swp){
                    st.back()[2]=0;
                }
                else if(it%2!=st.back()[0]%2){
                    // st.back()[2]=1;
                    st.back()[2]=0;
                }
            }
        }
    }
    for(int i=0;i<m;i++){
        if(s[i]=='1'){
            if((i%2==0)^cnt[i]) b++;
            else a++;
        }
    }
    cout<<a<<" "<<b<<endl;
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