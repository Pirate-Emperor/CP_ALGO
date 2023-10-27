#include <bits/stdc++.h>
using namespace std;

set<long long>st;

void divisors(long long n)
{
	for (long long i=1; i<=sqrt(n)+1; i++)
	{
		if (n%i==0)
		{
			if (n/i == i){
				st.insert(i);
			}
			else{
				st.insert(i);
				st.insert(n/i);
			}
		}
	}
}

int main()
{
	long long n;
	while(cin>>n){
        long long cnt=0;
        divisors(n);
        set<long long>::iterator it=st.begin();
        for(it; it!=st.end(); it++){    //cout<<*it<<endl;
            if((n-(*it))!=0 && (n-(*it))%(*it)==0){
                ++cnt;
            }
        }
        cout<<cnt<<endl;
        st.clear();
	}
	return 0;
}
