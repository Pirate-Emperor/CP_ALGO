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
    ll h=0,w=0,m=0;
    cin >> n >> m;
    if (n<m)
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for (int i=0;i<2*n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            cout << j << " ";
        }
        cout << endl;
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