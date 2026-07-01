#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e9 + 7;

// === BIT MANIPULATION ===
#define getbit(x,i) ((x&(1LL<<i))!=0)       // Set bit from index i
#define setbit(x,i) (x|(1LL<<i))            // Set at index i to 1
#define clearbit(x,i) (x&(~(1LL<<i)))       // Set at index i to 0
#define togglebit(x,i) (x^(1LL<<i))         // Toggle between 0 and 1
#define lowbit(x) (x&(-x))                  // Isolate lowest set bit
#define strip_low(x) (x&(x-1))              // Clear lowest set bit
#define is_pow2(x) (x && !(x&(x-1)))        // Check if exact power of 2
#define all_ones(n) ((1LL<<(n))-1)          // Generate n-bit mask of all 1s
// Built-ins: __builtin_popcountll(x), __builtin_ctzll(x) [trailing 0s], __builtin_clzll(x) [leading 0s]
// Count 1s in binary representations of all numbers from 1 to N in O(log N)
ll count_1s_to_n(ll n) { ll c = 0; for(int i=61; i>=0; i--) if(n & (1LL<<i)) { c += (i ? (1LL<<(i-1))*i : 0) + (n-(1LL<<i)+1); n -= (1LL<<i); } return c; }


// === BASIC MATH & MODULAR ARITHMETIC ===
ll qexp(ll a, ll b, ll m = MOD) {
    ll res = 1; a %= m;
    while (b) { if (b & 1) res = (ll)((__int128)res * a % m); a = (ll)((__int128)a * a % m); b >>= 1; }
    return res;
}
ll mulmod(ll a, ll b, ll m = MOD) { return (ll)((__int128)a * b % m); }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll ext_gcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll x1, y1, d = ext_gcd(b, a % b, x1, y1);
    x = y1; y = x1 - y1 * (a / b); return d;
}
ll inv_mod(ll a, ll m) { ll x, y; ext_gcd(a, m, x, y); return (m + x % m) % m; }
bool lde(ll a, ll b, ll c, ll &x, ll &y) { // Linear Diophantine Equation
    ll d = ext_gcd(abs(a), abs(b), x, y);
    if (c % d) return false;
    x *= c / d; y *= c / d;
    if (a < 0) x = -x; if (b < 0) y = -y;
    return true;
}

// === ADVANCED MODULAR ALGORITHMS ===
int discrete_log(int a, int b, int m) { // Baby-step Giant-step
    a %= m, b %= m; int k = 1, add = 0, g;
    while ((g = gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, ++add; k = (1LL * k * a / g) % m;
    }
    int n = sqrt(m) + 1, an = 1;
    for (int i = 0; i < n; ++i) an = (1LL * an * a) % m;
    unordered_map<int, int> vals;
    for (int q = 0, cur = b; q <= n; ++q) { vals[cur] = q; cur = (1LL * cur * a) % m; }
    for (int p = 1, cur = k; p <= n; ++p) {
        cur = (1LL * cur * an) % m;
        if (vals.count(cur)) return n * p - vals[cur] + add;
    }
    return -1;
}
int primitive_root(int p) {
    vector<int> fact; int phi = p - 1, n = phi;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) { fact.push_back(i); while (n % i == 0) n /= i; }
    if (n > 1) fact.push_back(n);
    for (int res = 2; res <= p; ++res) {
        bool ok = true;
        for (int f : fact) if (qexp(res, phi / f, p) == 1) { ok = false; break; }
        if (ok) return res;
    }
    return -1;
}
bool miller_rabin(ll n) { // Deterministic up to 2^64
    if (n < 2) return false;
    int r = __builtin_ctzll(n - 1); ll d = (n - 1) >> r;
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        ll x = qexp(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int i = 1; i < r; i++) { x = (ll)((__int128)x * x % n); if (x == n - 1) { comp = false; break; } }
        if (comp) return false;
    }
    return true;
}

// === PRIMES & LINEAR SIEVE ===
namespace Primes {
    const int MAX_N = 100005;
    int spf[MAX_N], phi[MAX_N], mu[MAX_N];
    vector<int> primes;
    void linear_sieve() {
        phi[1] = 1; mu[1] = 1;
        for (int i = 2; i < MAX_N; i++) {
            if (!spf[i]) { spf[i] = i; primes.push_back(i); phi[i] = i - 1; mu[i] = -1; }
            for (int p : primes) {
                if (p > spf[i] || i * p >= MAX_N) break;
                spf[i * p] = p;
                if (i % p == 0) { phi[i * p] = phi[i] * p; mu[i * p] = 0; break; }
                else { phi[i * p] = phi[i] * (p - 1); mu[i * p] = -mu[i]; }
            }
        }
    }
    vector<pair<ll, int>> factorize(ll n) {
        vector<pair<ll, int>> res;
        for (int p : primes) {
            if (1LL * p * p > n) break;
            if (n % p == 0) { int c = 0; while (n % p == 0) { n /= p; c++; } res.push_back({p, c}); }
        }
        if (n > 1) res.push_back({n, 1}); return res;
    }
    ll NOD(ll n) { ll res = 1; for (auto [p, c] : factorize(n)) res *= (c + 1); return res; }
    ll SOD(ll n) { ll res = 1; for (auto [p, c] : factorize(n)) { ll sum = 1, pw = 1; while (c--) sum += (pw *= p); res *= sum; } return res; }
    ll count_prime_factors(ll n) { ll res = 0; for (auto [p, c] : factorize(n)) res += c; return res; }
    ll get_phi(ll n) { ll res = n; for (auto [p, c] : factorize(n)) res -= res / p; return res; } // Euler's Totient for isolated large N
}
vector<ll> get_divisors(ll n) { // Divisors in O(sqrt(N))
    vector<ll> d;
    for (ll i = 1; i * i <= n; i++) if (n % i == 0) { d.push_back(i); if (i * i != n) d.push_back(n / i); }
    sort(d.begin(), d.end()); return d;
}

// === COMBINATORICS ===
namespace Combinatorics {
    vector<ll> fact, invf;
    void precompute(int n) { // Precompute factorials & inverses
        fact.assign(n + 1, 1); invf.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % MOD;
        invf[n] = qexp(fact[n], MOD - 2, MOD);
        for (int i = n - 1; i > 0; i--) invf[i] = invf[i + 1] * (i + 1) % MOD;
    }
    ll nCk(int n, int k) { if (k < 0 || k > n) return 0; return fact[n] * invf[k] % MOD * invf[n - k] % MOD; }
    int gray_code(int n) { return n ^ (n >> 1); }
    int rev_gray(int g) { int n = 0; for (; g; g >>= 1) n ^= g; return n; }
    
    bool next_comb(vector<int>& a, int n) { // Next lexicographical K-combination
        int k = a.size();
        for (int i = k - 1; i >= 0; i--) {
            if (a[i] < n - k + i + 1) { a[i]++; for (int j = i + 1; j < k; j++) a[j] = a[j - 1] + 1; return true; }
        }
        return false;
    }
    bool next_balanced(string& s) { // Next lexicographical balanced bracket sequence
        int n = s.size(), d = 0;
        for (int i = n - 1; i >= 0; i--) {
            d += (s[i] == '(' ? -1 : 1);
            if (s[i] == '(' && d > 0) {
                d--; int op = (n - i - 1 - d) / 2, cl = n - i - 1 - op;
                s = s.substr(0, i) + ')' + string(op, '(') + string(cl, ')'); return true;
            }
        }
        return false;
    }
    string kth_balanced(int n, int k) { // Find K-th balanced bracket sequence
        vector<vector<int>> d(2 * n + 1, vector<int>(n + 1, 0)); d[0][0] = 1;
        for (int i = 1; i <= 2 * n; i++) {
            d[i][0] = d[i - 1][1];
            for (int j = 1; j < n; j++) d[i][j] = d[i - 1][j - 1] + d[i - 1][j + 1];
            d[i][n] = d[i - 1][n - 1];
        }
        string ans; int dep = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (dep + 1 <= n && d[2 * n - i - 1][dep + 1] >= k) { ans += '('; dep++; }
            else { ans += ')'; if (dep + 1 <= n) k -= d[2 * n - i - 1][dep + 1]; dep--; }
        }
        return ans;
    }
}

// === MATRIX EXPONENTIATION ===
template<size_t N>
struct Matrix {
    ll m[N][N] = {0};
    void identity() { for (size_t i = 0; i < N; ++i) m[i][i] = 1; }
    Matrix operator*(const Matrix& b) const {
        Matrix res; // Cache-friendly loop order
        for (size_t i = 0; i < N; ++i) for (size_t k = 0; k < N; ++k) for (size_t j = 0; j < N; ++j)
            res.m[i][j] = (res.m[i][j] + m[i][k] * b.m[k][j]) % MOD;
        return res;
    }
    Matrix pow(ll p) const {
        Matrix res, base = *this; res.identity();
        while (p > 0) { if (p & 1) res = res * base; base = base * base; p >>= 1; }
        return res;
    }
};

// === BIG INTEGER ===
struct BigInt {
    const int B = 1e9; vector<int> a; int sign = 1;
    BigInt() {}
    BigInt(ll v) { sign = v < 0 ? -1 : 1; v = abs(v); do { a.push_back(v % B); v /= B; } while (v); }
    BigInt(string s) {
        sign = s[0] == '-' ? -1 : 1; int st = (s[0] == '-' || s[0] == '+');
        for (int i = s.size() - 1; i >= st; i -= 9) {
            int x = 0; for (int j = max(st, i - 8); j <= i; j++) x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    void trim() { while (a.size() > 1 && !a.back()) a.pop_back(); if (a.size() == 1 && !a[0]) sign = 1; }
    
    bool operator<(const BigInt& b) const {
        if (sign != b.sign) return sign < b.sign;
        if (a.size() != b.a.size()) return a.size() * sign < b.a.size() * b.sign;
        for (int i = a.size() - 1; i >= 0; i--) if (a[i] != b.a[i]) return a[i] * sign < b.a[i] * sign;
        return false;
    }
    bool operator==(const BigInt& b) const { return !(*this < b) && !(b < *this); }
    
    BigInt abs() const { BigInt res = *this; res.sign = 1; return res; }
    BigInt operator-() const { BigInt res = *this; res.sign = -sign; return res; }
    
    BigInt operator+(const BigInt& b) const {
        if (sign != b.sign) return *this - (-b);
        BigInt res; res.a.clear(); res.sign = sign; int carry = 0;
        for (size_t i = 0; i < max(a.size(), b.a.size()) || carry; ++i) {
            carry += (i < a.size() ? a[i] : 0) + (i < b.a.size() ? b.a[i] : 0);
            res.a.push_back(carry % B); carry /= B;
        }
        res.trim(); return res;
    }
    
    BigInt operator-(const BigInt& b) const {
        if (sign != b.sign) return *this + (-b);
        if (abs() < b.abs()) return -(b - *this);
        BigInt res = *this; int carry = 0;
        for (size_t i = 0; i < b.a.size() || carry; ++i) {
            res.a[i] -= carry + (i < b.a.size() ? b.a[i] : 0);
            carry = res.a[i] < 0; if (carry) res.a[i] += B;
        }
        res.trim(); return res;
    }
    
    BigInt operator*(const BigInt& b) const {
        BigInt res; res.a.assign(a.size() + b.a.size(), 0); res.sign = sign * b.sign;
        for (size_t i = 0; i < a.size(); ++i) {
            ll carry = 0;
            for (size_t j = 0; j < b.a.size() || carry; ++j) {
                ll cur = res.a[i+j] + a[i] * 1LL * (j < b.a.size() ? b.a[j] : 0) + carry;
                res.a[i+j] = cur % B; carry = cur / B;
            }
        }
        res.trim(); return res;
    }
    
    friend pair<BigInt, BigInt> divmod(const BigInt& a, const BigInt& b) {
        BigInt res, cur;
        for (int i = a.a.size() - 1; i >= 0; i--) {
            cur.a.insert(cur.a.begin(), a.a[i]); cur.trim();
            int x = 0, L = 0, R = a.B - 1;
            while (L <= R) {
                int mid = (L + R) >> 1;
                if (b.abs() * BigInt(mid) < cur + BigInt(1)) { x = mid; L = mid + 1; }
                else R = mid - 1;
            }
            cur = cur - b.abs() * BigInt(x);
            res.a.insert(res.a.begin(), x);
        }
        res.sign = a.sign * b.sign; cur.sign = a.sign;
        res.trim(); cur.trim(); return {res, cur};
    }
    
    BigInt operator/(const BigInt& b) const { return divmod(*this, b).first; }
    BigInt operator%(const BigInt& b) const { return divmod(*this, b).second; }
    
    void print() const {
        if (sign == -1) cout << '-';
        cout << (a.empty() ? 0 : a.back());
        for (int i = (int)a.size() - 2; i >= 0; --i) cout << setfill('0') << setw(9) << a[i];
    }
};

// === SOLVE & MAIN ===
void solve() {
    // Template entry point
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    Primes::linear_sieve(); // Init sieve if needed
    int tc = 1; 
    // cin >> tc;
    while (tc--) solve();
    return 0;
}