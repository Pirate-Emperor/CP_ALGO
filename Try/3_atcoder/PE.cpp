#include <bits/stdc++.h>
 
using namespace std;
 
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
bool chk[205][205][205];
double dp[205][205][205];
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
ll res=0;

double rec(ll n,ll k,ll l){
    if(!n||!l) return 0;
    if(chk[n][k][l]) return dp[n][k][l];
    ll y=2*n-k;
    if(!(2*n-k)) return 0;
    double a=0;
    if(k>0){
        a+=(double)(k)/y*(1+rec(n-1,k-1,l));
        // a+=(double)(k+y-1)/y*(rec(n-1,k-1,l));
    }
    ll u=2*n-2*k;
    if(u>0){
        double s=0;
        s+=1.0/(y-1)*(1+rec(n-1,k,l));
        // if(k>0&&l>1) s+=(double)(k+y-2)/(y-1)*(rec(n-1,k,l-1));
        if(k>0&&l>1) s+=(double)(k)/(y-1)*(1+rec(n-1,k,l-1));
        if(u>2&&l>1) s+=(double)(u-2)/(y-1)*rec(n,k+2,l-1);
        a+=(double)u/y*s;
    }
    chk[n][k][l]=true;
    return dp[n][k][l]=a;
}

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n>>l;
    vector<ll> arr(n);
    for(int i=0;i<n;++i){
        cin>>arr[i];
        w+=arr[i];
    }
    double resu=rec(n,0,l)*((double)w/n);
    cout<<fixed<<setprecision(10)<<resu<<endl;
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