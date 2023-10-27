#include<bits/stdc++.h>
#define max 100010
using namespace std;

int arr[max];
vector<int>prime;

void seive()
{
    memset(arr,0,sizeof(arr));
    int sqrtn=(int)sqrt(max);
    for(int i=3; i<=sqrtn; i+=2)
    {
        if(arr[i]==0){
            for(int j=i*i; j<max; j+=i+i){
                arr[j]=1;
            }
        }
    }
    prime.push_back(2);
    for(int i=3; i<max; i+=2){
        if(arr[i]==0)
            prime.push_back(i);
    }
}

int main()
{
    seive();
    cout<<prime.size()<<endl;
    return 0;
}

