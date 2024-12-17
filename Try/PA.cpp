// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ar array
#define ll long long
#define rep(x, start, end) for (auto x = (start) - ((start) > (end)); x != (end) - ((start) > (end)); ((start) < (end) ? x++ : x--))
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MAX_N = 4e5 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
 
ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int i_query(string s)
{
    int k;
    cout << s << endl; 
    cout.flush();
    cin >> k;
    return k;
}
char rev(char c)
{
    char resu = (c=='T')?'F':'T';
    return resu;
}

struct cmp {
    bool operator()(pair<ll,string> a, pair<ll,string> b) const 
    {
        if (a.first==b.first) return a.second<b.second;  
        else return a.first > b.first; 
    }
};

void solve() {
    ll n=0,l=0,x=0,y=0,k=0,r=0,q=0;
    ll h=0,w=0;
    cin >> n;
    vector<ll> arr(n),brr(n),vis(n,0);
    vector<vector<ar<ll,2>>> adj(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    for (int i=0;i<n;i++)
    {
        cin >> brr[i];
    }
    if (arr[0]!=brr[0] || arr[n-1]!=brr[n-1])
    {
        cout << "NO\n";
        return;
    }
    for (int i=0;i<n-1;i++)
    {
        adj[arr[i]].push_back({arr[i+1],i+1});
        adj[arr[i+1]].push_back({arr[i],i});
    }
    ar<ll,3> start = {arr[0],0,1};
    vis[0]=1;
    vector<ar<ll,2>> path;
    for (int i=0;i<n;i++)
    {
        for (auto it: adj[start[0]])
        {
            if (vis[it[1]]==0)
            {
                if (it[0]==brr[i])
                {
                    if (it[1]!=start[1]+start[2])
                    {
                        for (int j=start[1];j<n && j>=0;i-=start[2])
                        {
                            ll ij = it[1]+start[2]*(j-start[1]+start[2]);
                            if (ij>=0 && ij<n && arr[j]==arr[ij])
                            {
                                path.push_back({})
                            }
                        }
                        
                        start={it[0],it[1],-start[2]};
                    }
                    vis[it[1]]=0;
                    start={it[0],it[1],start[2]};
                    break;
                }
            }
        }
    }
}







signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}