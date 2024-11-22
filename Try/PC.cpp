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
    ll n=0,x=0,q=0,l=0,r=0,mid=0;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<ll> ones(n+1,0),twos(n+1,0),dot;
    for (int i=0;i<n;i++)
    {
        ones[i+1]=ones[i]+(s[i]=='1');
        if (s[i]=='/') dot.push_back(i);
    }
    for (int i=n-1;i>=0;i--)
    {
        twos[i]=twos[i+1]+(s[i]=='2');
    }
    for (int i=0;i<q;i++)
    {
        cin >> l >> r;
        l--;
        r--;
        ll li=l;
        ll ri=r;
        
        l = upper_bound(dot.begin(),dot.end(),l)-dot.begin();
        r = (upper_bound(dot.begin(),dot.end(),r)-dot.begin())-1;
        // cout << l << " " << r;
        x=0;
        while(l<=r)
        {
            mid=(r+l)/2;
            ll valo = ones[dot[mid]+1]-ones[li];
            ll valt = twos[dot[mid]]-twos[ri+1];
            // cout << li << " " << dot[mid] << " " << ri << " " << valo << valt;
            if (valo>valt)
            {
                l=mid+1;
            }
            else
            {
                r=mid-1;
            }
            x=max(x,2*min(valo,valt)+1);
        }
        for (ll mi: {l,r,mid})
        {
            x=0;
            if (mi<0 || mi>=dot.size()) continue;
            ll valo = ones[dot[mi]+1]-ones[li];
            ll valt = twos[dot[mi]]-twos[ri+1];
            x=max(x,2*min(valo,valt)+1);
        }
        cout << x << endl;
    }
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