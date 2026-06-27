#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void solve() {
    int n;if(!(cin>>n))return;
    int k=0;while((1LL<<k)<=n)k++;
    vector<string>S(k);for(int i=0;i<k;i++)cin>>S[i];
    vector<int>E(k,0);for(int i=1;i<=n;i++)for(int j=0;j<k;j++)if((i>>j)&1)E[j]++;
    vector<int>W(k,0);for(int j=0;j<k;j++){
    int c=0;for(int i=0;i<n;i++)if(S[j][i]=='1')c++;W[j]=c;}
    vector<int>sE=E,sW=W;
    sort(sE.begin(),sE.end());sort(sW.begin(),sW.end());
    if(sE!=sW){cout<<0<<"\n";return;}
    vector<int>p(k,-1);vector<bool>u(k,0);
    for(int i=0;i<k;i++)for(int j=0;j<k;j++)if(!u[j]&&E[i]==W[j]){u[j]=1;p[i]=j;break;}
    vector<int>a(n,0);for(int i=0;i<n;i++){
    int v=0;for(int j=0;j<k;j++)if(S[p[j]][i]=='1')v|=(1<<j);a[i]=v;}
    sort(a.begin(),a.end());
    for(int i=0;i<n;i++)if(a[i]!=i+1){cout<<0<<"\n";return;}
    ll ans=1;map<int,int>f;
    for(int x:E)f[x]++;
    for(auto&[w,ct]:f)for(int i=1;i<=ct;i++)ans*=i;
    cout<<ans<<"\n";
}

int main() {
    // Fast I/O is crucial for 2 * 10^5 inputs
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}