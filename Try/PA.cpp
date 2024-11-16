// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long

const int MAX_N = 5e5 + 5;
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

vector<ll> arr,brr,crr;
ll moves=0;
ll func(ll cur, ll a, ll b)
{
    return (cur==0)?max(a,b):min(a,b);
}
bool recur(ll cur)
{
    // if (moves>=3) return 1-cur;
    if (cur==0 && arr.size()==0) return false;
    else if (cur==1 && brr.size()==0) return false;
    if (cur==0)
    {
        auto tem = arr;
        for (int i=0;i<(int)tem.size();i++)
        {
            for (int j=0;j<(int)crr.size();j++)
            {
                if (crr[j]<arr[i]) 
                {
                    swap(arr[i],crr[j]);
                    if (recur(1-cur)==false) return true;
                    moves++;
                    swap(arr[i],crr[j]);
                }
            }
            crr.push_back(tem[i]);
            arr.erase(arr.begin()+i);
            if (recur(1-cur)==false) return true;
            moves++;
            arr.insert(arr.begin()+i,1,tem[i]);
            crr.pop_back();
        }
    }
    else
    {
        auto tem = brr;
        for (int i=0;i<(int)tem.size();i++)
        {
            for (int j=0;j<(int)crr.size();j++)
            {
                if (crr[j]<brr[i]) 
                {
                    swap(brr[i],crr[j]);
                    if (recur(1-cur)==false) return true;
                    moves++;
                    swap(brr[i],crr[j]);
                }
            }
            crr.push_back(tem[i]);
            brr.erase(brr.begin()+i);
            
            if (recur(1-cur)==false) return true;
            moves++;
            brr.insert(brr.begin()+i,1,tem[i]);
            crr.pop_back();
        }
    }
    // 
    return false;
}


void solve() {
    ll n=0,m=0,l=0,x=0;
    cin >> n >> m >> l;
    for (int i=0;i<n;i++) cin >> x, arr.push_back(x);
    for (int i=0;i<m;i++) cin >> x, brr.push_back(x);
    for (int i=0;i<l;i++) cin >> x, crr.push_back(x);

    ll res = recur(0);
    if (res==true) cout << "Aoki\n";
    else cout << "Takahashi\n";
    map<ll,ll> col;
    
}






int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int tc; tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t  << ": ";
        solve();
    }
}