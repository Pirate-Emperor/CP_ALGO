#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

const int INF=1e9;
const int LINF=1e18;
const int MOD=1e9+9;

void knapsack01(const vector<int>& w, const vector<int>& val, int target){
    vector<int> valsum(target+1,-1);
    val[0]=0;
    for (int j=0;j<w.size();j++){
        for (int i=target;i>=w[j];i--){
            if (valsum[i-w[j]]>=0) valsum[i]=max(valsum[i],valsum[i-w[j]]+val[j]);
        }
    }
    return valsum[target];
}

void solve(){
}
signed main(){
    int t;
    while(t--){
        solve();
    }
    return 0;
}