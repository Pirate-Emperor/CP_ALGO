#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int MAX_N=1e5;
const int INF=1e9;
const int LINF=1e18;

// Batch 3
vector<int> kmp(string s){
    int n=s.size();
    vector<int> pre(n,0);
    for (int i=1;i<n;i++){
        int z=pre[i-1];
        while(z>0 && s[z]!=s[i]) z=pre[z-1];
        pre[i]=z+(s[z]==s[i]);
    }
    return pre;
}

vector<int> zfun(string s){
    int n=s.size();
    vector<int> z(n,0);
    int l=0,r=0;
    for (int i=1;i<n;i++){
        if (i<r) z[i]=min(z[i-l],r-i);
        while(i+z[i]<n && s[z[i]]==s[i+z[i]]) z[i]++;
        if (i+z[i]>=r){
            l=i;
            r=i+z[i];
        }
    }
    return z;
}

vector<int> manacher(string s){
    s="#"+s+"$";
    int n=s.size();
    vector<int> res(n,0);
    int l=1,r=1;
    for (int i=1;i<n-1;i++){
        if (i<r) res[i]=min(res[r-i+l],r-i);
        while(s[i-res[i]]==s[i+res[i]]) res[i]++;
        if (i+res[i]>r){
            r=i+res[i];
            l=i-res[i];
        }
    }
    return vector<int>(res.begin()+1,res.end()-1);
}

// lyndon factorization
string min_cyclic_string(string s){
    int n=s.size();
    s+=s;
    int i=0;
    int ind=-1;
    while(i<n){
        ind=i;
        int j=i+1,k=i;
        while(j<2*n && s[k]<=s[j]){
            if (s[k]<s[j]) k=i;
            else j++,k++;
        }
        while(i<=k) i+=j-k;
    }
    return s.substr(ind,n);
}

const int MOD = 1e9+7;
struct Mint{
    int v;
    Mint(long long x=0):v((x%MOD+MOD)%MOD){}
    Mint operator+=(const Mint o){ if ((v+=o.v)>=MOD) v-=MOD; return *this;}
    Mint operator-=(const Mint o){ if ((v-=o.v)<0) v+=MOD; return *this;}
    Mint operator*=(const Mint o){ v=((long long)v*o.v)%MOD; return *this;}
    friend Mint operator+(Mint a, Mint b){ return a+=b;}
    friend Mint operator-(Mint a, Mint b){ return a-=b;}
    friend Mint operator*(Mint a, Mint b){ return a*=b;}


};

void solve(){

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}