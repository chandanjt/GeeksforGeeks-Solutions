

class Solution{
    public:
    long countSubarrays(int a[], int n, int L, int R)
    {
        // Complete the function
       long long int ans = 0;
        long long int l = 0,tot = 0,lsum = 0,i = 0;
    
        while(i<n){
            if(a[i]>R){
                lsum = lsum + ((l*(l+1))/2);
                ans = ans + (((tot)*(tot+1))/2) - lsum;
                l = 0,lsum = 0,tot=0;
                ++i;
                continue;
            }
            else if(a[i]<L){
                ++l;
                ++tot;
                ++i;
            }
            else{
                lsum = lsum + ((l*(l+1))/2);
                l = 0;
                ++tot;
                ++i;
            }
        }
        lsum = lsum + ((l*(l+1))/2);
        ans = ans + (((tot)*(tot+1))/2) - lsum;
        return ans;
        
    }
};