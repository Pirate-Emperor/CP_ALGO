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
    ll n,x,res=0,resu=0;
    cin >> n;
    vector<ll> arr(n);
    vector<pair<ll,ll>> brr(n);
    for (int i=0;i<n;i++)
    {
        cin >> arr[i];
        x=arr[i];
        int lg=0;
        while(x>0 && x%2==0)
        {
            lg++;
            x/=2;
        }
        brr[i]=make_pair(x,lg);
        
    }
    stack<pair<ll,ll>> st;
    ll sts = 0;
    ll stp = 0;
    for (int i=0;i<n;i++)
    {
        res+=brr[i].first;
        ll ts=0;
        ll xi = arr[i];
        while (!st.empty() && st.top().first<=xi)
        {
            auto tem = st.top();
            st.pop();
            stp=(stp-tem.first+MOD)%MOD;
            ll temp = (qexp(2,tem.second,MOD)*tem.first)%MOD;
            sts=((sts-temp)%MOD+MOD)%MOD;
            ts+=tem.second;
            ll tx=ts;
            while(tx>0 && !st.empty() && st.top().first>xi)
            {
                xi*=2LL;
                tx--;
            }
        }
        // cout << res << stp << sts << "T";
        st.push(make_pair(brr[i].first,brr[i].second+ts));
        auto tem = st.top();
        stp=(stp+tem.first)%MOD;
        ll temp = (qexp(2,tem.second,MOD)*tem.first)%MOD;
        sts=(sts+temp)%MOD;
        resu = ((res-stp+sts)%MOD+MOD)%MOD;
        cout << resu << " ";
    }
    // resu = res - 5 + 1280;
    // cout << resu << " ";
    cout << endl;
    return;
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