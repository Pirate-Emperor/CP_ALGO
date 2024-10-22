// https://codeforces.com/problemset/problem/580/E

#include <bits/stdc++.h>
using namespace std;


mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
// Use rnd(gen) for random number generation

#define ll long long
#define TxtIO   freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);

const int MAXN = 3e6 + 5; 
const int MAX_N = 2e5 + 1;
ll MOD = 998244353;
const ll MOD2 = 1073676287;
const ll MOD3 = 998244353;
const ll INF = 1e9;
const ll LINF = 1e18;

int read() {
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int ret = 0;
	while (c >= '0' && c <= '9') ret = ret*10 + (c - '0'), c = getchar();
	return ret;
}


void sol()
{
    
    ll a,b,c,d,n,k,m,q=0,x,resu=LINF;
    n = read();
    vector<pair<ll,ll>> arr, brr,res;
    // for (int i=0;i<n;i++)
    // {
    //     a = read();
    //     b = read();
    //     if (a<=b) arr.push_back(make_pair(b,a));
    //     else brr.push_back(make_pair(a,b));
    // }
    // sort(arr.begin(),arr.end());
    // sort(brr.begin(),brr.end());
    // int j=0;
    // for (int i=0;i<arr.size();i++)
    // {
    //     if (j<brr.size() && arr[i].first>brr[j].first)
    //     {
    //         res.push_back(brr[j]);
    //         j++;
    //         i=i-1;
    //         continue;
    //     }
    //     res.push_back(make_pair(arr[i].second,arr[i].first));
    // }
    // for(int i=j;i<brr.size();i++)
    // {
    //     res.push_back(brr[i]);
    // }

    for (int i=0;i<n;i++)
    {
        a = read();
        b = read();
        if (a<=b) arr.push_back(make_pair(a,b));
        else brr.push_back(make_pair(b,a));
    }
    sort(arr.begin(),arr.end());
    sort(brr.begin(),brr.end());
    int j=0;
    for (int i=0;i<arr.size();i++)
    {
        if (j<brr.size() && arr[i].first>brr[j].first)
        {
            res.push_back(make_pair(brr[j].second,brr[j].first));
            j++;
            i=i-1;
            continue;
        }
        res.push_back(arr[i]);
    }
    for(int i=j;i<brr.size();i++)
    {
        res.push_back(make_pair(brr[i].second,brr[i].first));
    }

    for (int i=0;i<n;i++)
    {
        cout << res[i].first << " " << res[i].second << " ";
    }
    // resu*=n;
    cout << endl;
    return;
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