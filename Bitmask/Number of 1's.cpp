//Number of 1's between 0 to 2^n-1


#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long int64;
int main(){
    int64 O[65],two;
    int i;

    O[1]=1;
    two = 1;
    printf("Total Number of 1's bits between 0 and %llu:%llu\n",(two<<1)-1,O[1]);
    for (i=2;i<64;i++){
        two = two<<1;
        O[i] = two + 2*O[i-1];
        //cout<<i<<"    "<<O[i]<<endl;
        printf("Total Number of 1's bits between 0 and %llu:%llu\n",(two<<1) -1,O[i]);
    }
    return 0;
}



//Number of 1's between 1 to n

/*#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long int64;
int main(){
   int64 O[65],V[65],two,n,Nn,T1=0,msb_one;
   int i;

   O[1]=1;
   V[1]=1;
   two = 1;
   for (i=2;i<64;i++){
       two = two<<1;
       O[i] = two + 2*O[i-1];
       V[i] = (two<<1)-1;
       printf("O[%d]= %llu V[%d]: %llu\n",i,O[i],i,V[i]);
   }
   printf("Enter 0 to break\n");
   while(1){
       scanf("%llu",&n);
       if (n==0) break;
       T1 = 0;
       Nn = n;
       while(Nn>0){

            for(i=1;;i++){
               if(V[i]>Nn)
                    break;
            }
            i = i-1;
            T1=T1+O[i];cout<<T1<<endl;
            msb_one=(Nn-V[i]);
            T1=T1+msb_one;
            if( msb_one == 0) break; //safety Purpose: Usigned Nn
            Nn=msb_one-1;
        }
        printf("Total Number of 1's between 0 to %llu : %llu\n",n,T1);
   }
   return 0;
}
*/
