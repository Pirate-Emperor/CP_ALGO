// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 2e5 + 1;
ll MOD = 998244353;
const ll MOD2 = 1073676287;
const ll MOD3 = 998244353;
const ll INF = 1e9;
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

vector<ll> fact, invf;

void precompute(int n) {
    fact.assign(n + 1, 1); 
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
    invf.assign(n + 1, 1);
    invf[n] = qexp(fact[n], MOD - 2, MOD);
    for (int i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
}

ll nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invf[k] % MOD * invf[n - k] % MOD;
    // return fact[n] * qexp(fact[k], MOD - 2, MOD) % MOD * qexp(fact[n - k], MOD - 2, MOD) % MOD;
}

const int NI = 4005;
ll ddp[2][NI];
vector<vector<ll>> c;
vector<vector<ll>> pref;

int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
}

ll ki;
void divCon(ll l, ll r, ll optL, ll optR)
{
    if (l>r) return;
    ll m = (r+l)/2;
    pair<ll,ll> mi = make_pair(LINF,-1);
    for (ll i=optL;i<=min(m,optR);i++)
    {
        mi = min(mi,make_pair((i==0?0LL:ddp[(ki&1)^1][i-1])+c[i][m],i));
    }
    // cout << mi.first << " ";
    ddp[(ki&1)][m]=mi.first;
    divCon(l,m-1,optL,mi.second);
    divCon(m+1,r,mi.second,optR);
}

void sol()
{
    
    ll a,b,c,d,n,m,k=-1,x,resu=LINF;
    cin >> b >> c >> d;
    a=0;
    n=1;
    for (int i=0;i<62;i++)
    {
        if (b%2==d%2)
        {
           
        }
        else if (b%2==c%2)
        {
            a+=n;
        }
        else 
        {
            cout << -1 << endl;
            return;
        }
        b/=2;
        c/=2;
        d/=2;
        n*=2;
    }
    cout << a << endl;
    return;
}


int main() {

    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);
    
    // precompute(2e5+10);
    // TxtIO;
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}