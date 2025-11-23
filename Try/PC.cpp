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
const ll LINF = 1e18+100;
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
    string s;
    cin >> s;
    int n = s.size();
    vector<ll> arr(n);
    for (int i=0;i<n;i++){
        arr[i]=s[i]-'0';
    }
    vector<array<ll,2>> dp(n,{0,0});
    vector<int> res;
    for (int i=1;i<n;i++){
        if (arr[i]==arr[i-1]){
            if (dp[i-1][0]==0) {
                dp[i]=dp[i-1];
            }
            else {
                int j = i-dp[i-1][0]-1;
                if (j>=0 && arr[j]==arr[j+1]){
                    dp[i]={dp[i-1][0]+2,dp[i-1][1]};
                    r++;
                    res.push_back(i);
                }
                else dp[i]={0,0};
            }
        }
        else{
            if (arr[i]-arr[i-1]==1){
                dp[i]={2,arr[i-1]};
                r++;
                res.push_back(i);
            }
            else{
                dp[i]={0,0};
            }
        }
    }
    // for (int it: res) cout << it << " ";
    cout << r << endl;
    return;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}