#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
const int MAX_N = 2e5;
const int INF = 1e9;
const ll LINF = 1e18;

bool is_goal(int r, int c, int val){
    return true;
}
bool is_valid(int r, int c, int n, int m, int val){
    if (r<0 || c<0 || r>=n || c>=m) return false;
    // some other checks could be made
    return true; 
}
void backtrack(int r, int c, vector<vector<int>>& grid, vector<vector<bool>>& vis){
    if (is_goal()) return true;
    vis[r][c]=true;
    int dr[]={1,1,-1,-1};
    int dc[]={1,-1,1,-1};
    for (int i=0;i<4;i++){
        int rn=r+dr[i];
        int cn=c+dc[i];
        if (!is_valid(nr,nc,grid.size(),grid[0].size(),grid[i][j])()) continue;
        if (backtrack(nr,nc,grid,vis)) return true;
    }
    vis[r][c]=false;
    return false;
}

void bitmask_dp(int n,vector<vector<int>>& cost){
    vector<int> dp(1<<n,INF);
    dp[0]=0;
    for (int i=0;i<1<<n;i++){
        int bits_active=__builtin_popcount(i);
        for (int j=0;j<n;j++){
            if (i&(1<<j)!=0){
                int nex_i=i|(1<<j);
                dp[nex_i]=min(dp[nex_i],dp[i]+cost[bits_active][j]);
            }
        }
    }
}


void solve(){

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(null);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
