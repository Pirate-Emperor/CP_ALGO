// Consider N points given on a plane
// the objective is to generate a convex hull, i.e. the smallest convex polygon that contains all the given points.

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
vector<array<int,3>> adj[MAX_N];
vector<ll> vis;
void recur(int st)
{
    if (vis[st]==1) return;
    vis[st]=1;
    for (auto it: adj[st])
    {
        int v = it[0];
        if (vis[v]==1) continue;
        recur(v);
    }
    return;
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n;
    string s;
    cin >> s;
    vector<int> br,cr;
    vector<ar<int, 3>> arr;
    for (int i=0;i<n;i++)
    {
        if (s[i]=='1') 
        {
            arr.push_back({1,i,1});
        }
        else 
        {
            if (arr.size()>0){
                auto it = arr.back();
                array<int, 3> at = {0,i-1,it[2]};
                if (it == at) 
                {
                    arr.pop_back();
                    arr.push_back({0,i,it[2]+1});
                }
                else arr.push_back({0,i,1});
            }
            else arr.push_back({0,i,1});
        }
    }
    m = arr.size();
    vector<int> brr,crr;
    // cout << n << " ";
    for (int i=0;i<m;i++)
    {
        if (arr[i][0]==0)
        {
            if (br.size()>0 && br.back()>=i-2) br.pop_back();
            else if (i==0 || i==m-1) cr.push_back(i);
            else if (cr.size()>0 && cr.back()>=i-2) cr.push_back(i);
            else
            {
                while(cr.size()>0) cr.pop_back();
                if (arr[i][2]>1) cr.push_back(i);
                else br.push_back(i);
            }
        }
    }
    if (br.size()>0 && cr.size()>0 && cr.back()==m-1 && br.back()>=cr.back()-2) br.pop_back();
    if (br.size()>0) 
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    return;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}