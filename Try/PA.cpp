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
    cin >> h >> w >> k;
    cin >> x >> y;
    n=h*w;
    vector<ll> arr(n+2000);
    vector<vector<ar<int,2>>> adj(n+2000);
    for (int i=0;i<h;i++)
    {
        for (int j=0;j<w;j++)
        {
            int it = i*w+j;
            cin >> arr[it];
        }
    }

    for (int i=0;i<h;i++)
    {
        for (int j=0;j<w;j++)
        {
            int it = i*w+j;
            vector<ll> col = {0,0,-1,1};
            vector<ll> row = {-1,1,0,0};
            for (int ci=0;ci<4;ci++)
            {
                int vi = i+row[ci];
                int vj = j+col[ci];
                if (vi>=0 && vi<h && vj>=0 && vj<w)
                {
                    int cit = vi*w+vj;
                    adj[it].push_back({cit, arr[cit]});
                }
            }
        }
    }
    


    vector<ll> vis(n,0);
    priority_queue<ar<ll,2>, vector<ar<ll,2>>, greater<ar<ll,2>>> pq;
    x--;
    y--;
    int pi = x*w + y;
    ll cur = arr[pi];
    ll s = pi;
    // pq.push({cur, s});
    vis[s]=1;
    for (auto [v, w] : adj[s]) {
        if (vis[v]==0) {
            pq.push({w, v});  
        }
    }
    while (pq.size()) {
        auto [d, u] = pq.top(); 
        pq.pop();
        if (vis[u]==1)
        {
            continue;
        }
        bool check=false;
        if ((cur%k==0 && (cur/k) > d) || (cur%k!=0 && (cur/k) >= d)) 
        {
            if (vis[u]==0)
            {
                // cout << cur << " " << d << endl;
                vis[u]=1;
                cur+=d;
                for (auto [v, w] : adj[u]) {
                    if (vis[v]==0) {
                        pq.push({w, v});  
                    }
                }
            }
            continue;
        }
        break;
    } 
    cout << cur << endl;
}







signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}