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

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n>>m;
    vector<ll> arr(n+1),brr(n),crr(n+1,0),drr;
    for(ll i=1;i<=n;++i) cin>>arr[i];
    for(ll i=1;i<n;++i) cin>>brr[i];
    for(ll i=1;i<n;++i){
        crr[i+1]=(brr[i]-arr[i]-arr[i+1]-crr[i])%m;
        if(crr[i+1]<0) crr[i+1]+=m;
    }
    map<ll,ll> mpi;
    for(ll i=1;i<=n;++i){
        r+=crr[i];
        if(i%2){
            x++;
            mpi[m-1-crr[i]]-=m;
        }
        else{
            q++;
            mpi[crr[i]]+=m;
        }
    }
    drr.push_back(0);
    drr.push_back(m-1);
    for(auto& v:mpi){
        drr.push_back(v.first);
        if(v.first+1<m) drr.push_back(v.first+1);
    }
    sort(all(drr));
    drr.erase(unique(all(drr)),drr.end());
    res=LINF;
    ll sum=0;
    auto it=mpi.begin();
    for(ll i:drr){
        while(it!=mpi.end()&&it->first<i){
            sum+=it->second;
            it++;
        }
        c=r+(x-q)*i+sum;
        if(c<res) res=c;
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
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}