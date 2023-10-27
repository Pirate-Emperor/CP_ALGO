#include<stdio.h>

int phi(int n)
{
    float res=n;
    int i;
    if(n%2==0){
        while(n%2==0)
            n/=2;
        res*=(1-1/2.0);//making it floating point number
    }
    for(i=3; i*i<=n; i+=2){
        if(n%i==0){
            while(n%i==0)
                n/=i;
            res*=(1-1/(float)i);//making it floating point number
        }
    }
    if(n>2)
        res*=(1-1/(float)n);//making it floating point number
    return (int)res;
}

int main()
{
    int t,n,b,i,c=0;
    scanf("%d",&t);
    while(t--){
        scanf("%d %d",&n,&b);
        for(i=n; i<=b; i++)
            c+=phi(i);
        printf("%d\n",c);
    }
    return 0;
}
