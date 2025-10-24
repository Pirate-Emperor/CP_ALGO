#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(),(x).end()
#define ar array
#define ll long long
#define int long long
 
const int MAX_N = 2e5 + 5;
const ll MOD = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;
const int K = 11;
struct st{
    ll id;
    mutable ll len,t;
    bool operator < (const st &A) const { return id<A.id;} 
};
 
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
 
ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}
 
int n, m, x;
vector<int> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> dis;
vector<ll> par;
int res=0;
void recur(int u, int dep)
{
    vis[u]=1;
    for (int it: adj[u])
    {
        if (vis[it]==0) 
        {
            par[it]=u;
            recur(it, dep+1);
        }
    }
    dis[u]=dep;
}
 
void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    vector<int> arr;
    for (int i=1;i<n;i++) arr.push_back(i);
    ll res=0;
    a=0;
    int j=0;
    while(true)
    {
        vector<int> odd;
        vector<int> even;
        if (arr.size()==0) break;
        for (int it: arr)
        {
            int tem = 1<<j;
            cout << "? " << it << " " << tem << "\n";
            cout.flush();
            cin >> b;
            if (b==0) even.push_back(it);
            else odd.push_back(it); 
            a++;
            if (a==2*n)
            {
                cout << "! " << res << "\n";
                cout.flush();
                return;
            }
        }
        if (odd.size()==even.size()) 
        {
            arr=odd;
            res+=1<<j;
        }
        else 
        {
            if (even.size()<odd.size()) arr=even;
            else 
            {
                arr=odd;
                res+=1<<j;
            }
        }
        j++;
    }
    
    cout << "! " << res << "\n";
    cout.flush();
    return;
}
 
signed main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}