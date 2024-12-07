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
void solve() {
    ll n=0,l=0,x=0,r=0;
    cin >> n;
    string s,t,res;
    s.append(n,'T');
    t.append(n,'T');
    res.append(n,'T');
    for (int i=0;i<n;i++)
    {
        s[i]='T';
        t[i]=(i%2==0)?'T':'F';
    }
    l = i_query(s);
    r = i_query(t);
    for (int i=0;i<n;i+=2)
    {
        if (i==n-1)
        {
            s[i]='F';
            x = i_query(s);
            if (x-l==1) res[i]=s[i];
            else res[i]=rev(s[i]);
            l=x;
        }
        else
        {
            s[i]='F';
            s[i+1]='F';
            x = i_query(s);
            if (x-l==2) 
            {
                res[i]=s[i];
                res[i+1]=s[i+1];
            }
            else if (x-l==-2) 
            {
                res[i]=rev(s[i]);
                res[i+1]=rev(s[i+1]);
            }
            else
            {
                if (i==n-2)
                {
                    s[i]='T';
                    x = i_query(s);
                    if (x-l==1) 
                    {
                        res[i]=s[i];
                        res[i+1]=s[i+1];
                    }
                    else if (x-l==-1) 
                    {
                        res[i]=rev(s[i]);
                        res[i+1]=rev(s[i+1]);
                    }
                }
                else
                {
                    t[i]=rev(t[i]);
                    t[i+1]=rev(t[i+1]);
                    t[i+2]=rev(t[i+2]);
                    ll y = i_query(t);
                    if (y-r==3)
                    {
                        res[i]=t[i];
                        res[i+1]=t[i+1];
                        res[i+2]=t[i+2];
                    }
                    else if (y-r==-1)
                    {
                        res[i]=rev(t[i]);
                        res[i+1]=rev(t[i+1]);
                        res[i+2]=t[i+2];
                    }
                    else if (y-r==1)
                    {
                        res[i]=t[i];
                        res[i+1]=t[i+1];
                        res[i+2]=rev(t[i+2]);
                    }
                    else if (y-r==-3)
                    {
                        res[i]=rev(t[i]);
                        res[i+1]=rev(t[i+1]);
                        res[i+2]=rev(t[i+2]);
                    }
                    r=y;
                    i++;
                }
            }
            l=x;
        }
    }
    int resu = i_query(res);
    if (resu<n)
    {
        cout << "Error" << endl;
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