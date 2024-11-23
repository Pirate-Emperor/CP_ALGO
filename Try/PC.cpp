// Sieve // Totient // Mobius
// Generate the all primes <= n
// Time complexity: O(nlog(logn)) for standard sieve, O(n) for linear sieve
// Problem link: https://cses.fi/problemset/task/2417/ (using linear sieve to generate the mobius function)

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 4e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;

// vector<int> primes, is_prime, spf;

// void sieve(int n) {
//     primes.clear();
//     is_prime.assign(n + 1, 1);
//     spf.assign(n + 1, 0);
//     is_prime[0] = is_prime[1] = false;
//     for (ll i = 2; i <= n; i++) {
//         if (is_prime[i]) {
//             primes.push_back(i);
//             spf[i] = i;
//             for (ll j = i * i; j <= n; j += i) {
//                 is_prime[j] = false;
//                 spf[j] = i;
//             }
//         }
//     }
// }

// Linear sieve including calculating the smallest prime factor (spf), Mobius function, and Euler's totient function
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
    ll n,m; 
    cin >> n >> m;
    vector<ll> arr(m);
    for (int i=0;i<m;i++)
    {
        cin >> arr[i];
    }
    ll lgn=log2(n);
    if (lgn>=m)
    {
        cout << -1 << endl;
        return;
    }
    sort(arr.begin(),arr.end());
    vector<ll> res(n+1);
    for (int i=1;i<=n;i++)
    {
        if (i==1)
        {
            res[i]=arr[m-1];
        }
        else
        {
            ll pos = lower_bound(arr.begin(),arr.end(),res[i/spf[i]])-arr.begin();
            pos--;
            // cout << pos << " ";
            // if (pos>=m) 
            // {
            //     cout << -1 << endl;
            //     return;
            // }
            res[i]=arr[pos];
        }
    }
    for (int i=1;i<=n;i++)
    {
        cout << res[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    sieve(MAX_N);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}
