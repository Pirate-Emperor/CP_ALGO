class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int> dif;
        int a=0;
        for (int i=0;i<n;i++)
        {
            if (i==0) a++;
            else
            {
                if (arr[i]<=arr[i-1])
                {
                    dif.push_back(a);
                    a=1;
                }
                else a++;
            }
        }
        if (a>0) dif.push_back(a);
        int resu=0;
        int b=0;
        for (int i=0;i<dif.size();i++)
        {
            if (i!=0) resu=max(resu,min(dif[i],dif[i-1]));
            b=max(dif[i],b);
        }
        resu=max(resu,b/2);
        return resu>=k;
}
};