// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 5e5 + 5;
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

int n, m, vis[MAX_N];
vector<int> adj[MAX_N];
vector<int> radj[MAX_N];

void dfs(int u) {
    vis[u] = 1;
    for (int v : radj[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

void solve() {
    ll ni=0,mi=0;
    cin >> ni >> mi;
    vector<string> mat(ni);
    n=ni*mi;
    for (int i=0;i<ni;i++)
    {
        cin >> mat[i];
        for (int j=0;j<mi;j++)
        {
            ll u=i*ni+j;
            ll v=-1;
            switch(mat[i][j])
            {
                case 'U':
                v=(i>0)?(i-1)*ni+j:-1;
                break;
                case 'D':
                v=(i<ni-1)?(i+1)*ni+j:-1;
                break;
                case 'L':
                v=(j>0)?i*ni+j-1:-1;
                break;
                case 'R':
                v=(j<mi-1)?(i-1)*ni+j+1:-1;
                break;
            }
            if (v>=0) 
            {
                adj[u].push_back(v);
                radj[v].push_back(u);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        vis[i]=0;
        adj[i].clear();
        radj[i].clear();
    }

    for (int i = 0; i < n; i++) {
        if (vis[i]==1) continue; 
        int r=i/mi;
        int c=i%mi;
        vector<char> chr = {'D','U','R','L'};
        vector<char> ch = {'U','D','L','R'};
        vector<int> rc = {-1,1,0,0};
        vector<int> cc = {0,0,1,-1};
        if (mat[r][c]=='?')
        {
            for (int j=0;j<4;j++)
            {
                int nr=r+rc[j];
                int nc=c+cc[j];
                if (nr>=0 && nr<ni && nc>=0 && nc<mi)
                {
                    if (ch[j]==mat[nr][nc])
                    {
                        mat[r][c] = chr[j];
                    } 
                    else if (vis[nr*mi+nc]==1) 
                    {
                        vis[i]=1;
                        adj[i].push_back(nr*mi+nc);
                        radj[nr*mi+nc].push_back(i);
                    }
                }
            }
            if (adj[i].size()==0)
            {
                int nr=r;
                int nc=c;
                if (c<mi-1)
                {
                    nr = r;
                    nc = c+1;
                }
                else 
                {
                    nr=r+1;
                    nc=c;
                }
                adj[i].push_back(nr*mi+nc);
                radj[nr*mi+nc].push_back(i);
            }   
            if (radj[i].size()!=0) dfs(i);
        }
        else
        {
            for (int j=0;j<4;j++)
            {
                int nr=r+rc[j];
                int nc=c+cc[j];
                if (nr>=0 && nr<ni && nc>=0 && nc<mi)
                {
                    if (vis[nr*mi+nc]==1) 
                    {
                        if (chr[j]==mat[r][c]) vis[i]=1;
                    }
                }
            }
        }
        
        // dfs(i);
    }
    ll resu=0;
    for (int i=0;i<n;i++)
    {
        if (vis[i]==1) resu++;
    }
    cout << resu << endl;
}






int main() {
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