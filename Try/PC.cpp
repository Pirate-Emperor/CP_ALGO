// Disjoint Set Union
// Union by rank & Path compression

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ar array
#define ll long long
#define rep(x, start, end) for (auto x = (start) - ((start) > (end)); x != (end) - ((start) > (end)); ((start) < (end) ? x++ : x--))
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MAX_N = 4e5 + 5;
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

int i_query(string s)
{
    int k;
    cout << s << endl; 
    cout.flush();
    cin >> k;
    return k;
}
char rev(char c)
{
    char resu = (c=='T')?'F':'T';
    return resu;
}

struct cmp {
    bool operator()(pair<ll,string> a, pair<ll,string> b) const 
    {
        if (a.first==b.first) return a.second<b.second;  
        else return a.first > b.first; 
    }
};

void solve(){
    ll n=0,l=0,x=0,y=0,k=0,r=0,q=0;
    ll h=0,w=0,m=0;
    cin >> n;
    vector<vector<ll>> adj(n);
    for (int i=0;i<n-1;i++)
    {
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    ll res=1;
    for (int i=0;i<n;i++)
    {
        vector<ll> temp;
        for (auto it: adj[i])
        {
            temp.push_back(adj[it].size());
        }
        if (temp.size()==0) continue;
        sort(temp.begin(),temp.end());
        ll k=temp.size();
        for (int i=0;i<k;i++)
        {
            res=max(res,1+(k-i)*temp[i]);
        }
    }
    res=n-res;
    cout << res << endl;
    return;
}
// void solve() {
//     ll n=0,l=0,x=0,y=0,k=0,r=0,q=0;
//     ll h=0,w=0,m=0;
//     cin >> n >> m >> x >> y;
//     vector<pair<ll,ll>> arr(n);
//     map<ll,map<ll,ll>> row,col;
//     for (int i=0;i<n;i++)
//     {
//         cin >> l >> r;
//         l--;
//         r--;
//         row[l][r]=1;
//         col[r][l]=1;

//     }
//     x--;
//     y--;
//     ll res=0;
//     for (int i=0;i<m;i++)
//     {
//         char ti;
//         ll ci;
//         cin >> ti >> ci;
//         if (ti=='L')
//         {
//             x-=ci;
//             auto it = col[y].lower_bound(x);
//             auto it2 = col[y].upper_bound(x+ci-1);
//             vector<ll> temp;
//             for (auto iti=it;iti!=it2;iti++)
//             {
//                 temp.push_back(iti->first);
//             }
//             for (ll j:temp)
//             {
//                 res++;
//                 col[y].erase(j);
//                 row[j].erase(y);
//             }
//         }
//         else if (ti=='R')
//         {
//             x+=ci;
//             auto it = col[y].lower_bound(x-ci+1);
//             auto it2 = col[y].upper_bound(x);
//             vector<ll> temp;
//             for (auto iti=it;iti!=it2;iti++)
//             {
//                 temp.push_back(iti->first);
//             }
//             for (ll j:temp)
//             {
//                 res++;
//                 col[y].erase(j);
//                 row[j].erase(y);
//             }
//         }
//         else if (ti=='D')
//         {
//             y-=ci;
//             auto it = row[x].lower_bound(y);
//             auto it2 = row[x].upper_bound(y+ci-1);
//             vector<ll> temp;
//             for (auto iti=it;iti!=it2;iti++)
//             {
//                 temp.push_back(iti->first);
//             }
//             for (ll j:temp)
//             {
//                 res++;
//                 row[x].erase(j);
//                 col[j].erase(x);
//             }
//         }
//         else if (ti=='U')
//         {
//             y+=ci;
//             auto it = row[x].lower_bound(y-ci+1);
//             auto it2 = row[x].upper_bound(y);
//             vector<ll> temp;
//             for (auto iti=it;iti!=it2;iti++)
//             {
//                 temp.push_back(iti->first);
//             }
//             for (ll j:temp)
//             {
//                 res++;
//                 row[x].erase(j);
//                 col[j].erase(x);
//             }
//         }
//     }
//     x++;
//     y++;
//     cout << x << " " << y << " " << res << endl; 
//     return;
// }







signed main() {
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