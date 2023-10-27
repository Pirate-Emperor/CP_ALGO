#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#define max 100005
using namespace std;

int arr[max];
vector<int> primes;
int sod[max];

void seive()
{
    memset(arr,0,sizeof(arr));
    primes.push_back(2);
    int n=sqrt(max);
    for(int i=3; i<=n; i+=2){
        if(arr[i]==0){
            sod[i]=i+1;
            primes.push_back(i);
            for(int j=i*i; j<max; j+=i+i){
                arr[j]=1;
            }
        }
    }
    for(int i=315; i<max; i+=2){
        if(arr[i]==0){
            sod[i]=i+1;
            primes.push_back(i);
        }
    }
}

int SOD(int n)
{
    int res=1,res1=1,sqrtn=sqrt(n),keep=n;
    for(int i=0; i<primes.size() && primes[i]<=sqrtn; i++){
        int k=1,p=1,c=0;
        while(n%primes[i]==0){
            ++c;
            n/=primes[i];
            k*=primes[i];
            p+=k;
        }
        res1*=(c+1);
        res*=p;
        sqrtn=sqrt(n);
    }
    if(n>1){
        res*=(n+1);
        res1*=2;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    seive();
    int n;
    while(cin>>n){
        cout<<SOD(n)<<endl;
    }
    return 0;
}

