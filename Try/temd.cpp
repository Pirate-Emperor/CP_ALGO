// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 405;
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

int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
}
 
void sol() {
    ll n,a;
    cin >> n;
    vector<ll> arr(n),brr(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    for (int i=0;i<n;i++)
    {
        cin >> brr[i];
    }
    vector<ll> dp(n+1,-1);
    priority_queue<ll> q;
    q.push(1);
    ll i=0;
    dp[0]=0;
    while(i<n && q.size()>0)
    {
        a = q.top();
        q.pop();
        while(i<n && i<a)
        {
            if (brr[i]>a)
            { 
                ll temp = dp[a-1]+arr[i];
                if (dp[brr[i]-1]==-1)
                {
                    dp[brr[i]-1] = temp;
                }
                else dp[brr[i]-1] = min(dp[brr[i]-1],temp); 
                q.push(brr[i]);
            }
            i++;
        }
    }
    ll resu=0,sum=0;

    for (int i=0;i<n;i++)
    {
        sum+=arr[i];
        if (dp[i]!=-1)
        {
            resu = max(resu, sum-dp[i]);
        }
    }
    cout << resu << endl;
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