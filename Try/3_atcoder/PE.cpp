// by Pirate_King

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
string arr;
ll dp[505][2][3][2][1024][2];

ll cnt(ll x){
    ll c=0;
    while(x){
        x&=x-1;
        c++;
    }
    return c;
}
ll recur(ll i,ll chk1,ll r3,ll chk2,ll msk,ll chk3){
    if(i==arr.size()){
        if(chk3)return 0;
        if((r3==0)+chk2+(cnt(msk)==3)==1) return 1;
        return 0;
    }
    if(dp[i][chk1][r3][chk2][msk][chk3]!=-1) return dp[i][chk1][r3][chk2][msk][chk3];
    ll lim=chk1?9:(arr[i]-'0'),ans=0;
    for(ll d=0;d<=lim;++d){
        ll nchk=chk1||(d<lim);
        if(chk3&&d==0)ans=(ans+recur(i+1,nchk,0,0,0,1))%MOD;
        else {
            // ans=(ans+recur(i+1,nchk,(r3+d+1)%3,chk2||(d==3),msk|(1<<d),0))%MOD;
            ans=(ans+recur(i+1,nchk,(r3+d)%3,chk2||(d==3),msk|(1<<d),0))%MOD;
        }
    }
    return dp[i][chk1][r3][chk2][msk][chk3]=ans;
}
 
void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>arr;
    memset(dp,-1,sizeof(dp));
    res=recur(0,0,0,0,0,1);
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
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}