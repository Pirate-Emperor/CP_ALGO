#include <bits/stdc++.h>

#define ar array
using ll = long long;
using int = long long;
const int MAX_N = 2e5+5;
const int MAX_L = 1e3+5;
const int MOD = 1e9+7;
const int INF = 1e9;
const ll LINF = 1e18;

struct DSU{
    int n;
    int comp;
    int *par, *rank;
    DSU(int n){
        this->n=n;
        this->comp=n;
        par=(int*)malloc(sizeof(int)*n);
        rank=(int*)malloc(sizeof(int)*n);
        for (int i=0;i<n;i++){
            par[i]=i;
            rank[i]=1;
        }
    }
    ~DSU(){
        free(par);
        free(rank);
    }
    int find(int u){
        if (u>=this->n || u<0) return -1;
        else return par[u]==u?u:par[u]=find(par[u]);
    }
    bool merge(int u, int v){
        if (u>=this->n || u<0 || v>=this->n || v<0) return false;
        u=find(u);
        v=find(v);
        if (rank[v]>rank[u]) swap(u,v);
        par[v]=u;
        this->comp--;
        if (rank[u]==rank[v]) rank[u]++;
        return true;
    }
};

