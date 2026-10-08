#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int INF = 1e9;
const ll LINF = 1e18;
cosnt int MOD = 1e9+7; // 998244353

// Batch 6
vector<int> suffix_array(string s){
    s+="$";
    int n=s.size();
    vector<int> p(n),c(n);
    vector<pair<char,int>> a;
    for (int i=0;i<n;i++) a.push_back({s[i],i});
    sort(a.begin(),a.end());
    for (int i=0;i<n;i++) p[i]=a[i].second;
    c[0]=0;
    for (int i=1;i<n;i++) c[p[i]]=(a[i].first==a[i-1].first)?c[p[i-1]]:c[p[i-1]]+1;

    for (int k=1;(1<<k)<n;k++){
        vector<int> np(n),nc(n),pos(n),cnt(n);
        for (int i=0;i<n;i++) cnt[c[p[i]]]++;
        for (int i=0;i<n;i++) pos[i]=pos[i-1]+cnt[i-1];
        for (int i=0;i<n;i++) np[pos[c[p[i]]]++]=p[i];
        p=np;
        nc[0]=0;
        for (int i=1;i<n;i++){
            auto cur = {c[p[i]],c[(p[i]+(1<<k))%n]};
            auto pre = {c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
            nc[p[i]]=(cur==pre)?nc[p[i-1]]:nc[p[i-1]]+1;
        }
        c=nc;
    }
    return vector<int>(p.begin()+1,p.end());
}

long long meet_in_the_middle(const vector<long long>& arr, long long target){
    int n=arr.size();
    int m1=n/2,m2=n-m1;
    auto find_sum = [&arr](int start, int len){
        vector<long long> sums;
        for (int i=0;i<(1<<len);i++){
            long long tem;
            for (int j=0;j<len;j++){
                if (i&(1<<j)) tem+=arr[start+j];
            }
            sums.push_back(tem);
        }
        return sums;
    }
    auto sum1=find_sum(0,m1),sum2=find_sum(m1,m2);
    long long res=0;
    for (long long s1:sum1){
        res+=upper_bound(sum2.begin(),sum2.end(),target-s1)-lower_bound(sum2.begin(),sum2.end(),target-s1);
    }
    return res;
}

// Batch 7
class BigInt{
    size_t sz,cap;
    int* data;
    BigInt(size_t cap=15):cap(cap),sz(0),data(new int[cap]){}
    ~BigInt(){delete[] data}
    BigInt(const BigInt& o){
        cap=o.cap;
        sz=o.sz;
        data=new int[cap];
        for (size_t i=0;i<sz;i++) data[i]=o.data[i];
    }
    BigInt& operator=(const BigInt& o){
        if (this!=&o){
            cap=o.cap;
            sz=o.sz;
            delete[] data;
            data=new int[cap];
            for (size_t i=0;i<sz;i++) data[i]=o.data[i];
        }
        return *this;
    }
    BigInt(BigInt& o) noexcept{
        cap=o.cap;
        sz=o.sz;
        data=o.data;
        o.data=nullptr;
        o.sz=0;
        o.cap=0;
    }
    BigInt& operator=(BigInt& o) noexcept{
        if (this!=&o){
            cap=o.cap;
            sz=o.sz;
            delete[] data;
            data=o.data;
            o.data=nullptr;
            o.sz=0;
            o.cap=0;
        }
        return *this;
    }

};


template<typename Derived>
struct MatchingEngine{
    static_cast<Derived*>(this)->execute();
};
struct CryptoEngine: public MatchingEngine<CryptoEngine>{
    void execute(){}
};
struct alignas(64) OrderBookCounter{
    uint64_t fills;
}

void solve(){

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}