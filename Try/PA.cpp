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

const int MAX_N = 2e3 + 5;
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

int n;
int mod;
 
int mul(int i, int j) {
    int res = 0;
    rep(x, 0, n - 1) {
        if (i & (1LL << x)) res ^= j;
        j <<= 1;
        if (j & (1LL << (n - 1))) j ^= mod;
    }
    return res;
}
 
int pow(int i) {
    int res = 1;
    int b = 2;
    while (i) {
        if (i & 1) res = mul(res, b);
        b = mul(b, b);
        i >>= 1;
    }
    return res;
}




void solve() {
    ll l=0,x=0,y=0,k=0,r=0,q=0;
    string s;
    cin >> s;
    n=s.size();
    vector<ll> pos;
    ll m=0;
    for (int i=0;i<n;i++)
    {
        if (s[i]=='1') 
        {
            pos.push_back(i); 
            // m|=(1LL << i);
        }
    }
    if (pos.size()==0)
    {
        cout << -1 << endl;
        return;
    }
    else if (pos.size()==1)
    {
        cout << pos[0]+1 << " " << pos[0]+2 << endl;
        return;
    }
    else if (pos.size()==2)
    {
        cout << pos[0]+1 << " " << pos[1]+1 << endl;
        return;
    }
    s.erase(s.find_last_not_of("0") + 1);
    int offset = s.find_first_not_of("0");
    s.erase(0, offset);
    n=s.size();
    rep(x, 0, sz(s)) if (s[x] == '1') mod |= (1LL << x);
    m = mod;

    int h = (n + 1) / 2;
 
    int val = mod;
    int prod = 1;
    rep(x, 3LL, 1 << h) if (x & 1) {
        int num = 0;
        while (true) {
            int curr = val;
            int other = 0;
            rep(bit, 0, n) if (curr & (1LL << bit)) {
                curr ^= x << bit;
                other ^= 1LL << bit;
            }
            if (curr == 0) {
                val = other;
                num++;
            } else
                break;
        }

        if (num) {
            prod *= (1LL << (63 - __builtin_clzll(x))) - 1;
            rep(y, 1, num) prod *= 1LL << (63 - __builtin_clzll(x));
        }
    }
    if (val > 1) prod *= (1LL << (63 - __builtin_clzll(val))) - 1;

    int ans = 1LL << 60;
    for (int x = 1; x * x <= prod; x++) {
        if (prod % x == 0) {
            if (pow(x) == 1) ans = min(ans, x);
            if (pow(prod / x) == 1) ans = min(ans, prod / x);
        }
    }
    y=ans;
    x=pos[0]+1;
    y+=x;
    cout << x << " " << y << endl;
    
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