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
    bool chk=0;
    cin>>n>>k;
    string s;
    cin>>s;
    vector<ll> arr(MAX_N),brr(MAX_N),crr(MAX_N);
    for(int i=0;i<n;++i) if(s[i]=='o') arr[++w]=i+1;
    if(w<k){
        cout<<"0.0000000000\n";
        return;
    }
    double resu=-1.0;
    for(int i=k;i<=w;++i){
        q=i-k;
        x=arr[q+1]-1;
        y=q;
        while(z>=2){
            a=brr[z-2];
            b=crr[z-2];
            c=brr[z-1];
            d=crr[z-1];
            // d=crr[z-2];
            if((c-a)*(y-b)<=(d-b)*(x-a)) z--;
            else break;
        }
        brr[z]=x;
        crr[z]=y;
        z++;
        l=0;r=z-1;
        while(l<r){
            g=(l+r)/2;
            a=brr[g];
            b=crr[g];
            c=brr[g+1];
            d=crr[g+1];
            if((c-a)*(i-b)>(d-b)*(arr[i]-a)) l=g+1;
            // if((c-a)*(i-b)>(d-b)*(arr[i]-a)) l=g;
            else r=g;
        }
        double cur=1.0*(i-crr[l])/(arr[i]-brr[l]);
        if(cur>resu) resu=cur;
    }
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