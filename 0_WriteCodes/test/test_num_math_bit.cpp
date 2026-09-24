#include <bits/stdc++.h>
using namespace std;

#define setbit(x,i) (x|(1LL<<(i)))
#define getbit(x,i) (!(x&(1LL<<(i))==0))
#define clearbit(x,i) (x&(~(1LL<<(i))))
#define togglebit(x,i) (x^(1LL<<i))
#define lowbit(x) (x&(-x))
#define clearlow(x) (x&(x-1))
#define ispow2(x) (x && (x&(x-1))==0)

ll count1(x){
    ll i=0;
    while(x){
        i++;
        x&=(x-1);
    }
}