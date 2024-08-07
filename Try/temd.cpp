// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long

const int MAXN = 3e6 + 5; 
const int MAX_N = 2e5 + 1;
ll MOD = 1000000007;
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

void sol()
{
    
    ll a,b,c,n,m,k=-1,x,resu=0;
    cin >> n;
    string s;
    cin >> s;
    a=0;
    b=0;
    for (int i=0;i<n;i++)
    {
        if (s[i]=='(') a++;
        else if (s[i]==')') b++;
    }
    // if (a>b)
    // {
    //     x=0;
    //     for (int i=n-1;i>=0;i--)
    //     {
    //         if (s[i]==')') x++;
    //         else if (s[i]=='_' && x>0) 
    //         {
    //             s[i]='(';
    //             x--;
    //         }
    //     }
    // }
    // else
    // {
    //     x=0;
    //     for (int i=0;i<n;i++)
    //     {
    //         if (s[i]=='(') x++;
    //         else if (s[i]=='_' && x>0) 
    //         {
    //             s[i]=')';
    //             x--;
    //         }
    //     }
    // }
    x=0;
    // for (int i=0;i<n;i++)
    // {
    //     if (s[i]=='_') 
    //     {
    //         x=1-x;
    //         if (x==0) s[i]=')';
    //         else s[i]='(';
    //     }
    }
    cout << s << endl;
    
    return;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // precompute(100);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        sol();
 
    }
    // cout.flush();
    return 0;
}