#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

long long NumberOfPrimes(long long n)
{
    long long num=0,sqrtn=sqrt(n);
    if(n%2==0){
        while(n%2==0){
            n/=2;
            ++num;
        }
    }
    for (int i=3; i<=sqrtn; i+=2) {
        while(n%i==0) {
            n/=i;
            ++num;
        }
    }
    return num+(n!=1);
}

int main() {
    int a=15, b=30;
    cout << NumberOfPrimes(a)<<"     "<<NumberOfPrimes(b) << '\n';
    return 0;
}

