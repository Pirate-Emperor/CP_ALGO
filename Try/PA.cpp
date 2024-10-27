// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 1<<22;
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


void solve() {
    ll n,k,x,y;
    cin >> n;
    vector<ll> arr(n);
    ll resu=0;
    stack<ll> fi,si,ti;
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
    }
    vector<ll> ta(n+1,0);
    for (int i=0;i<n;i++)
    {
        while(!ti.empty()) ti.pop();
        for (int j=i;j<n;j++)
        {
            if (ti.empty() || ti.top()<=arr[j]) 
            {
                if (ti.size()==1 && ti.top()==arr[j]) {}
                else ti.push(arr[j]);
            }
        }
        ta[i]=ti.size();
    }
    resu = n-1;
    for (int i=0;i<n-1;i++)
    {
        si.push(arr[i]);
        for (int j=i+1;j<n;j++)
        {
            if (arr[i]>=arr[j])
            {
                ll tem = ta[j]+fi.size()+si.size()-2;
                resu = min(resu,tem);
            }
            if (si.empty() || si.top()<=arr[j]) 
            {
                if (si.size()==1 && si.top()==arr[j]) {}
                else si.push(arr[j]);
            }
            
        }
        while(!si.empty()) si.pop();
        if (fi.empty() || fi.top()<=arr[i]) fi.push(arr[i]);
    }
    
    cout << resu << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}