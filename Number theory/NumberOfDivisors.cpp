#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#define max 100005
using namespace std;

int arr[max];
vector<int> primes;
int nod[max];

void seive()
{
    memset(arr,0,sizeof(arr));
    primes.push_back(2);
    int n=sqrt(max);
    for(int i=3; i<=n; i+=2){
        if(arr[i]==0){
            primes.push_back(i);
            for(int j=i*i; j<max; j+=i+i){
                arr[j]=1;
            }
        }
    }
    for(int i=315; i<max; i+=2){
        if(arr[i]==0){
            primes.push_back(i);
        }
    }
}

int NOD(int n) {
    int sqrtn = sqrt ( n );
    int res = 1;
    for(int i = 0; i < primes.size() && primes[i] <= sqrtn; i++) {
        if ( n % primes[i] == 0 ) {
            int p = 0; /*Counter for power of prime*/
            while ( n % primes[i] == 0 ) {
                n /= primes[i];
                p++;
            }
            sqrtn = sqrt ( n );
            p++;/*Increase it by one at end*/
            res *= p; /*Multiply with answer*/
        }
    }
    if ( n != 1 ) {
        res *= 2; /*Remaining prime has power p^1. So multiply with 2*/
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
        cout<<NOD(n)<<endl;
    }
    return 0;
}
