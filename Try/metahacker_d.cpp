// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 1e5 + 5;
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

void sol()
{
    
    ll a,b,c,n,m,k=-1,x,resu=0;
    string s;
    cin >> s >> k;
    n = s.size();
    vector<ll> temp;
    for (int i=0;i<n;i++)
    {
        if (s[i]=='?')
        {
            if (i+1<n)
            {
                if (s[i+1]=='?') temp.push_back(i);
                else
                {
                    a = s[i+1]-'1'+1;
                    if (a<=6) temp.push_back(i);
                    else s[i]='1';
                }
            } 
            else temp.push_back(i);
        }
    }
    x = k-1;
    if (s[n-1]=='?')
    {
        if (s[n-2]=='?')
        {
            a = x%15;
            x/=15;
            if (a<=5) 
            {
                s[n-2]='2';
                s[n-1]='0'+(6-a);
            }
            else
            {
                s[n-2]='1';
                s[n-1]='0'+(16-a);
            }
            temp.pop_back();
            temp.pop_back();
        }
        else
        {
            a = x%9;
            x/=9;
            s[n-1]='0'+(10-a);
            temp.pop_back();
        }
    }
    

    while(!temp.empty())
    {
        if (x%2==1) 
        {
            b=temp.back();
            s[b]='1';
        }
        else 
        {
            b=temp.back();
            s[b]='2';
        }
        temp.pop_back();
        x/=2;
    }
    b=0;
    vector<ll> dp(n+5);
    dp[0]=1;
    dp[1]=1;
    for (int i=1;i<n;i++)
    {
        a = s[i]-'1'+1;
        b = (s[i-1]-'1'+1)*10 + a;
        dp[i+1] = ((a!=0)?dp[i]:0)+((b!=a && b<=26)?dp[i-1]:0);
    }
    resu=dp[n];
    cout << s << " " << resu << endl;
    return;
}


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    // precompute(2e5+10);
    TxtIO;
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        cout << setprecision(10) << "Case #" << t << ": ";
        sol();
    }
    // cout.flush();
    return 0;
}