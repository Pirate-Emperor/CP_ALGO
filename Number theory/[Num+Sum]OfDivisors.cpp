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
int nod[max];

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

int sumOfDivisors(int n)
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
    nod[keep]=res1;
    return res;
}

void setSumOfDivisors()
{
    memset(sod,0,sizeof(sod));
    memset(nod,0,sizeof(nod));
    for(int i=1; i<max; i++){
        if(sod[i]==0){
            sod[i]=sumOfDivisors(i);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    seive();
    setSumOfDivisors();
    int n;
    while(cin>>n){
        cout<<nod[n]<<"    "<<sod[n]<<endl;
    }
    return 0;
}

