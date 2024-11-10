#define ll long long

class Solution {
public:
    ll MOD = 1e9+7;
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
    }
    int countKReducibleNumbers(string s, int k) {
        int n = s.size();
        precompute(n+100);
        vector<long long> dp(n+1,0);
        dp[0]=0;
        dp[1]=1;
        for (int i=2;i<=n;i++)
        {
            dp[i] = dp[__builtin_popcount(i)]+1;
        }
        
        long long a=0;
        ll resu=0;
        for (int i=0;i<n;i++)
        {
            if (s[i]=='0') continue;
            for (int j=0;j<n-i;j++)
            {
                long long tem=a+j;
                if (tem<=0) continue;
                if (dp[tem]<=k) 
                {
                    resu = (resu + nCk(n-i+1,j))%MOD;;
                }
            }
            a++;
        }
        
        return resu;
    }
};