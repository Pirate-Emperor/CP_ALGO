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
    
    ll a,b,c,d,n,m,q=0,x,resu=LINF;
    n = read();
    vector<ll> arr(n),brr(n);
    for (int i=0;i<n;i++) 
    {
        arr[i] = read();
    }
    int maxM = 1e3+10;
    if (n<4)
    {
        while(true)
        {
            a=0;
            for (int i=0;i<n;i++)
            {
                int ti = (i+1)%n;
                arr[ti]=max(0LL,arr[ti]-arr[i]);
                if (arr[ti]==0) a++;
            }
            if (a>=1) break;
        }
    }
    else
    {
        // bool check=true;
        for (int j=0;j<maxM;j++)
        {
            // check=true;
            for (int i=0;i<n;i++)
            {
                int ti = (i+1)%n;
                arr[ti]=max(0LL,arr[ti]-arr[i]);
                // if (arr[(i-2+n)%n]!=0) check=false;
            }
            // if (check) break;
        }
    }
    int ki=-1;
    for (int i=0;i<n;i++)
    {
        if (arr[i]==0)
        {
            ki=i;
            break;
        }
        int ti = (i+1)%n;
        arr[ti]=max(0LL,arr[ti]-arr[i]);
    }
    for (int i=0;i<n;i++)
    {
        brr[i]=arr[(i+ki)%n];
    }
    arr = brr;
    ll k,tsum;
    for (int i=2;i<n;i++)
    {
        if (arr[i-2]!=0) 
        {
            if (arr[i-1]==0) continue;
            k = arr[i-1]+arr[i-2]-1LL;
            k/=arr[i-2];
            tsum = 2LL*arr[i-1];
            tsum-= (k)*arr[i-2];
            tsum*=(k-1);
            tsum=(tsum+1LL)/2LL;
            if (arr[i]>=tsum) 
            {
                arr[i-1]=0;
                arr[i]-=tsum;
            }
            else 
            {
                arr[i-1]=0;
                arr[i]=0;
            }
        }
    }
    int i=n-1;
    if (n>=3 && arr[i-2]!=0) 
    {
        ll k = (arr[i-1]+arr[i-2]-1)/arr[i-2];
        ll tsum = k*(2*arr[i-1] - (k)*arr[i-2])/2 - (arr[i-1]%arr[i-2]);
        if (arr[i]>tsum) 
        {
            arr[i-1]=0;
            arr[i]-=tsum;
        }
        else 
        {
            arr[i-1]=0;
            arr[i]=0;
        }
    }
    else if (n>=2) {
        if (arr[i-1]!=0) arr[i]=0;
    }
    vector<ll> ans;
    for (int i=0;i<n;i++)
    {
        int ti = (i-ki+n)%n;
        if (arr[ti]!=0) ans.push_back(i+1);
    }
    cout << ans.size() << endl;
    for (int i=0;i<ans.size();i++)
    {
        cout << ans[i] << " ";
    }
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