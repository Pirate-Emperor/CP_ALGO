// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1<<22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;

int n, m, k, resu;
vector<string> bd;

void recur(int i, int j, int dep)
{
    if (i<0 || j<0 || i>=n || j>=m) return;
    if (dep==k)
    {
        resu++;
        return;
    }
    vector<int> xt = {0,0,-1,1};
    vector<int> yt = {-1,1,0,0};
    for (int t=0;t<4;t++)
    {
        int it = xt[t], jt = yt[t];
        if ((i+it)<0 || (i+it)>=n) continue;
        if ((j+jt)<0 || (j+jt)>=m) continue;
        if (bd[i+it][j+jt]=='.')
        {
            bd[i+it][j+jt]='#';
            recur(i+it,j+jt,dep+1);
            bd[i+it][j+jt]='.';
        }
    }
    
    return;
}
void solve() {
    cin >> n >> m >> k;
    bd.resize(n);
    for (int i=0;i<n;i++)
    {
        cin >> bd[i];
    }
    resu=0;
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<m;j++)
        {
            if (bd[i][j]=='.')
            {
                bd[i][j]='#';
                recur(i,j,0);
                bd[i][j]='.';
            }
        }
    }
    cout << resu << endl;
}

int main() {
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
    cout.flush();
}