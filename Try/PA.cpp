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

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

void solve() {
    ll n=0,m=0,k=0,l=0,x=0,bi=0;
    cin >> n;
    ll res=0;
    vector<ll> arr(n);
    map<pair<ll,ll>,ll> mpi; 
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        mpi[{arr[i],i}]=1;
    }
    x=0;
    vector<ll> resu;
    pair<ll,ll> tem={1,-1};
    while(mpi.size()>1)
    {
        auto it = mpi.lower_bound(tem);
        if (it!=mpi.end() && tem.first == it->first.first)
        {
            tem = it->first;
            resu.push_back(it->first.first+x);
            cout << ")"<< it->first.second << endl;
        }
        else
        {
            auto it0 = mpi.lower_bound({tem.first,tem.second});
            it = mpi.lower_bound({tem.first+1,tem.second});
            pair<ll,ll> tem2 = {tem.first,-1};
            auto it2 = mpi.lower_bound({tem2});
            if (it0==mpi.end() || it->first.first-1>it2->first.first)
            {
                x++;
                tem = it2->first;
                cout << "+" << it2->first.first << endl;
                resu.push_back(it2->first.first+x);
            }
            else
            {
                tem = it->first;
                cout << "="<< it->first.second << endl;
                resu.push_back(it->first.first+x);
            }
        }
        if (tem.second!=-1) 
        {
            mpi.erase(tem);
            cout << tem.second << " ";
        }
        
    }
    resu.push_back(mpi.begin()->first.first+x);
    for (int i=0;i<resu.size();i++)
    {
        cout << resu[i] << " ";
    }
    cout << endl;
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