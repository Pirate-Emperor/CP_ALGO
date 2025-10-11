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
vector<array<int,2>> adj[MAX_N];
vector<array<int,2>> edges;
vector<ll> vis;
vector<ll> curS;
int res=0;
void recur(int N, int node, int cur)
{
    if (cur>(N-1)/2 || node>=N) return;
    for (int i=node;i<N;i++)
    {
        curS[i]=1;
        int temp=0;
        for (int j=0;j<m;j++)
        {
            temp+=curS[edges[j][0]]!=curS[edges[j][1]];
        }
        res=max(temp,res);
        recur(N, i+1,cur+1);
        curS[i]=0;
    }
}

void solve() {
    ll l=0,r=0;
    ll w=0,y=0,z=0;
    ll a=0,b=0,c=0,d=0;
    ll g=0,q=0,k=0;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    curS.clear();
    edges.clear();
    for (int i=0;i<n;i++) 
    {
        curS.push_back(0);
        adj[i].clear();
    }
    for (int i=0;i<m;i++)
    {
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back({y,0});
        edges.push_back({x,y});
    }
    vector<vector<int>> dp(2*k+1,vector<int>(n,0));
    for (int i=0;i<n;i++)
    {
        dp[2*k][i]=(s[i]=='B');
    }
    for (int i=2*k-1;i>=0;i--)
    {
        for (int j=0;j<n;j++)
        {
            if (i%2==0) dp[i][j]=1;
            for (auto it: adj[j])
            {
                if (i%2==1 && dp[i+1][it[0]]==1) dp[i][j]=1;
                if (i%2==0 && dp[i+1][it[0]]==0) dp[i][j]=0;
            }
        }
    }
    if (dp[0][0]==1) cout << "Bob\n";
    else cout << "Alice\n";
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