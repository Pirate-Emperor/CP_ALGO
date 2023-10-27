#include<stdio.h>

int main()
{
    long long int n,i,lpd,count=0;
    while(scanf("%lld",&n)==1)
    {
        if(n%2==0)
            ++count;
        while(n%2==0)
        {
            lpd=2;
            n=n/2;
        }
        for(i=3; i*i<=n; i+=2)
        {
            if(n%i==0)
                ++count;
            while(n%i==0)
            {
                if(n%i==0)
                    lpd=i;
                n=n/i;
            }
        }
        if(n>2)
        {
            lpd=n;
            ++count;
        }
        if(count>1)
            printf("%lld\n",lpd);
        else
            printf("-1\n");
        count=0;
    }
    return 0;
}
