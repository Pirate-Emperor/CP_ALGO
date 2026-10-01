#include<bits/stdc++.h>
using namespace std;

// Daily (will do later)
#define ll long long
// Batch 3

vector<int> prefix_func(string s){
    int n=s.size();
    vector<int> res(n);
    res[0]=0;
    for (int i=1;i<n;i++){
        int j=res[i-1];
        while(j && s[i]!=s[j]){
            j=res[j-1];
        }
        res[i]+=(s[i]==s[j]);
    }
    return res;
}

vector<int> zfunc(string s){
    int n=size();
    vector<int> res(n,0);
    res[0]=0;
    l=0;
    r=0;
    for (int i=1;i<n;i++){
        if (r>=i) res[i]=min(r-i+1,res[i-l]);
        while(i+res[i]<n && s[i+res[i]]==s[res[i]]) res[i]++;
        if (i+res[i]-1>r){
            r=i+res[i]-1;
            l=i;
        }
    }
    return res;
}

vector<int> manacher(string s){
    int n=s.size();
    s="#"+s+"%";
    vector<int> res(n+2);
    int l=1,r=1;
    res[0]=1;
    for (int i=1;i<=n;i++){
        res[i]=max(0,min(r-i,res[r-i+l]));
        while(s[i-res[i]]==s[i+res[i]]) res[i]++;
        if (i+res[i]>r){
            r=i+res[i];
            l=i-res[i];
        }
    }
    return vector<int>(res.begin()+1,res.end()-1);
}

string min_cyclic_string(string s){
    int n=s.size();
    s+=s;
    int i=0,j=0,k=0;
    int res=0;
    while(i<n){
        res=i;
        j=i+1;
        k=i;
        while(j<2*n && s[j]>=s[k]){
            if (s[j]==s[k]){
                j++;
                k++;
            }
            else k=i;
        }
        if (i<=k) i+=j-k;
    }
    return s.substr(res,n);
}

const int MOD=1e9+7;
struct Mint{
    int v;
    Mint(long long x=0):v((x%MOD+MOD)%MOD){}
    Mint operator+=(Mint o){if ((v+=o.v)>=MOD){v-=MOD;} return *this;}
    Mint operator-=(Mint o){if ((v-=o.v)<0){v+=MOD;} return *this;}
    Mint operator*=(Mint o){v=((long long)v*o.v)%MOD; return *this;}
    friend Mint operator+(Mint a, Mint b){return a+=b;}
    friend Mint operator-(Mint a, Mint b){return a-=b;}
    friend Mint operator*(Mint a, Mint b){return a*=b;}
    Mint pow(long long k) const{
        Mint res=1,a=*this;
        while(k){
            if (k&1) res=res*a;
            a*=a;
            k>>=1;
        }
        return res;
    }
    Mint inv() const {return pow(MOD-2);}
    Mint operator/=(Mint o){return *this*=o.inv();}
    friend Mint operator/(Mint a, Mint b){return a/=b;}
};

vector<Mint> fact,ifact;
void prec(int n){
    fact.resize(n+1);
    ifact.resize(n+!);
    fact[0]=1;
    ifact[0]=1;
    for (int i=1;i<=n;i++){
        fact[i]=fact[i-1]*Mint(i);
    }
    ifact[n]=fact[n].inv();
    for (int i=n-1;i>=1;i--) ifact[i]=ifact[i+1]*Mint(i+1);
}
Mint nCk(int n, int k){
    if (k<0||k>n) return 0;
    return fact[n]*ifact[n-k]*ifact[k];
}
Mint catalan(int n){
    return nCk(2n,n)*Mint(n+1).inv();
}
Mint stars_bars(int n, int r){
    return nCK(n+r-1,r-1);
}

template<size_t N>
struct Matrix{
    long long M[N][N]={0};
    void identity(){for (int i=0;i<N;i++) M[i][i]=1;}
    Matrix operator*(const Matrix &o) const{
        Matrix res;
        for (int i=0;i<N;i++) for (int k=0;k<N;k++) for (int j=0;j<N;j++){
            res.m[i][j]=(res.m[i][j]+(m[i][k]*o.m[k][j])%MOD)%MOD;
        }
        return res;
    }
    Matrix pow(long long k) const {
        Matrix res,a=*this;
        res.identity();
        while(k){
            if (k&1) res=res*a;
            a=a*a;
            k>>=1;
        }
        return res;
    }
};

void solve(){

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(null);
    int t;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}