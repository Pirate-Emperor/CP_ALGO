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
const int OFF=40;
const int MDIF=100;

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
    string s;
    int k;
    cin >> s >> k;
    int n=s.length();
    vector<vector<int>> dp(3,vector<int>(MDIF,INF));
    dp[0][OFF]=0;
    for (int i=0;i<n;i++)
    {
        int iso=(i>=2&&s[i-2]=='A'&&s[i-1]=='B'&&s[i]=='C')?1:0;
        vector<vector<int>> ndp(3,vector<int>(MDIF,INF));
        int ca=(s[i]=='A'?0:1);
        int cb=(s[i]=='B'?0:1);
        int cc=(s[i]=='C'?0:1);
        int cx=(s[i]!='A'&&s[i]!='B'&&s[i]!='C')?0:1;
        int mnd=MDIF,mxd=-1;
        for (int st=0;st<3;st++)
        {
            for (int d=0;d<MDIF;d++)
            {
                if (dp[st][d]!=INF) 
                {
                    mnd=min(mnd,d);
                    mxd=max(mxd,d);
                }
            }
        }
        if (mnd==MDIF) break;
        for (int st=0;st<3;st++)
        {
            for (int d=mnd;d<=mxd;d++)
            {
                if (dp[st][d]==INF) continue;
                int nst=1;
                int nd=d-iso;
                if (nd>=0&&nd<MDIF)
                {
                    ndp[nst][nd]=min(ndp[nst][nd],dp[st][d]+ca);
                }
                nst=(st==1?2:0);
                nd=d-iso;
                if (nd>=0&&nd<MDIF)
                {
                    ndp[nst][nd]=min(ndp[nst][nd],dp[st][d]+cb);
                }
                nst=0;
                nd=d-iso+(st==2?1:0);
                if (nd>=0&&nd<MDIF)
                {
                    ndp[nst][nd]=min(ndp[nst][nd],dp[st][d]+cc);
                }
                nst=0;
                nd=d-iso;
                if (nd>=0&&nd<MDIF)
                {
                    ndp[nst][nd]=min(ndp[nst][nd],dp[st][d]+cx);
                }
            }
        }
        dp=move(ndp);
    }
    int tgtd=OFF+k;
    int ans=INF;
    if (tgtd>=0&&tgtd<MDIF)
    {
        ans=min({dp[0][tgtd],dp[1][tgtd],dp[2][tgtd]});
    }
    if (ans>=INF/2) cout << -1 << endl;
    else cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // sieve(MAX_N);
    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
    cout.flush();
}