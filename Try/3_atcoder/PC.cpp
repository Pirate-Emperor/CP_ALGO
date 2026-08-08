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

// ll recur(vector<ll>&crr){
//     ll r=0,l=1;
//     for(int i=n-1;i>=0;--i){
//         ll a=0;
//         for(int j=i+1;j<n;++j) if(crr[j]<crr[i]) a++;
//         r+=a*l;
//         if(i) l*=n-i;
//     }
//     return r;
// }

void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0; 
    cin>>n>>q;
    vector<ll> arr(n+1),brr(n+1),crr;
    while(q--){
        cin>>y;
        if(y==1){
            cin>>x;
            w=max(z,arr[x]-b);
            if(w) brr[arr[x]]--;
            arr[x]=w+b+1;
            if(!brr[arr[x]]++) crr.push_back(arr[x]);
        }
        else ++b;
        res=0;
        for(int i=0;i<crr.size();)
            if(crr[i]<=b||!brr[crr[i]]){
                crr[i]=crr.back();
                crr.pop_back();
            }
            else{
                if(brr[crr[i]]&1) res^=crr[i]-b;
                i++;
            }
        cout<<res<<endl;
    }
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