#include<bits/stdc++.h>
#define getbit(x,i) ((x&(1<<i))!=0)
#define setbit(x,i) (x|(1<<i))              //set 1
#define clearbit(x,i) (x&(~(1<<i)))         //set 0
#define powerOfTwo(x) (x&(x-1))             //check if 'a' is 2^(something)
#define bpop(x) __builtin_popcountll(x)
using namespace std;

//to use function better to use bool
/*inline bool getbit(long long x,int i)
{
    return (x&(1<<i));
}

inline int setbit(long long x,int i)
{
    return (x|(1<<i));
}

inline int clearbit(long long x,int i)
{
    return (x&(~(1<<i)));
}*/

int main()
{
    int a,b;
    /** three popcount functions --
    __builtin_popcount , __builtin_popcountl , __builtin_popcountll
    complexity -- O log k (k is number of bit).
    Because k is specified, the complexity is O(1) */
    __builtin_popcountll(12);
    cout<< bpop(8) <<endl;

    bitset<32> k(1000000000);
    for(int i=30; i>=0; i--){
        cout<<bitset<32>(14 & (1<<i))<<endl;
    }
    cout<<(1<<31)-1<<endl;

    while(cin>>a>>b)
        cout<<getbit(a,b)<<endl;
    return 0;
}
