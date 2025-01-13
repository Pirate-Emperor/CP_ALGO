// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define int long long

const int MAX_N = 1e6;
const int MOD = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;

// const int mod = 7340033;
const int mod = (119 << 23) + 1;
const int root = 62;
int root_1 = 0;
const int root_pw = 1 << 23;

ll qexp(ll a, ll b, ll m) {
    ll res = 1;
    while (b) {
        if (b % 2) res = res * a % m;
        a = a * a % m;
        b /= 2;
    }
    return res;
}

void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = qexp(n,mod-2,mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

vector<int> primes, is_prime, spf, mobius, phi;

void sieve(int n) {
    primes.clear();
    is_prime.assign(n + 1, 1);
    spf.assign(n + 1, 0);
    mobius.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    is_prime[0] = is_prime[1] = 0;
    mobius[1] = phi[1] = 1;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            spf[i] = i;
            mobius[i] = -1;
            phi[i] = i - 1;
        }
        for (auto p : primes) {
            if (i * p > n || p > spf[i]) break;
            is_prime[i * p] = 0;
            spf[i * p] = p;
            mobius[i * p] = (spf[i] == p) ? 0 : -mobius[i];
            phi[i * p] = (spf[i] == p) ? phi[i] * p : phi[i] * phi[p];
        }
    }
}

void solve() {
    int n, m, k, l, resu=0;
    cin >> n >> k;
    root_1 = qexp(root,mod-2,mod);
    for (int i=1;i<=n;i++)
    {
        int b = ceil(n/i); // n
        int c = min(b,k); // k
        vector<int> p(c+1,1),q(c+1,1), res(2*c+1,0);
        int fac=1;
        for (int j=1;j<=c;j++)
        {
            int jinv = qexp(j,MOD-2,MOD);
            fac=(fac*jinv)%MOD;
            p[j]=((MOD-p[j-1])*jinv)%MOD;
            q[j] = (qexp(j,b,MOD)*fac)%MOD;
        }
        int si = p.size() + q.size() - 1;
        int B = 32 - __builtin_clz(si);
	    int ns = 1 << B;
        p.resize(ns);
        q.resize(ns);
        res.resize(ns);
        fft(p,false);
        fft(q,false);
        for (int j=0;j<ns;j++)
        {
            res[j]=(p[j]*q[j])%MOD;
        }
        fft(res,true);
        int sum=0;
        for (int j=2;j<=c;j++) sum=(sum+res[j])%MOD;
        resu=(resu + ((sum*mobius[i])%MOD+MOD)%MOD)%MOD;

    }
    cout << resu << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    sieve(MAX_N);
    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}