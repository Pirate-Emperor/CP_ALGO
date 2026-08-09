// by Pirate-King

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
const int OFF=30;
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
// vector<ll> resu;
bool chk;
ll gcde(ll a,ll b,ll&x,ll&y){
    if(!b){
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll d=0;
    d=gcde(b,a%b,x1,y1);
    x=y1;
    // y=x1;
    y=x1-y1*(a/b);
    // x=y1-x1*(a/b);
    return d;
}
void solve(){
    ll l=0,r=0;
    ll x=0,w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin>>n;
    vector<string> arr(n);
    for(int i=0;i<n;i++){
        cin>>arr[i];
        for(int j=0;j<n;j++){
            if(arr[i][j]=='#'){
                r=(r+i)%n;
                c=(c+j)%n;
                w++;
            }
        }
    }
    ll x1,y1;
    gcde(w,n,x1,y1);
    k=(x1%n+n)%n;
    if(chk){
        cin>>x>>y;
        --x;
        --y;
        ll cmr=(r*k)%n,cmc=(c*k)%n;
        a=((x-cmr)*w)%n;
        // a=(((x-cmr)*w)%n+n)%n;
        a=(a%n+n)%n;
        b=((y-cmc)*w)%n;
        b=(b%n+n)%n;

        if(a||b){
            bool chk1=false;
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(arr[i][j]=='#'){
                        ll r2=(i+a)%n;
                        ll c2=(j+b)%n;
                        if(arr[r2][c2]=='.'){
                            cout<<i+1<<" "<<j+1<<" "<<r2+1<<" "<<c2+1<<endl;
                            chk1=true;
                        }
                    }
                    if(chk1) break;
                }
                if(chk1) break;
            }
        }
        else{
            cout<<"1 1 1 1\n";
        }
    }
    else{
        x=(r*k)%n;
        y=(c*k)%n;
        cout<<x+1<<" "<<y+1<<endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // sieve(MAX_N);
    // prec();
    string s;
    cin>>s;
    chk=(s=="first");
    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}