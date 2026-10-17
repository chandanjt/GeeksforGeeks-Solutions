

class Solution{
    public:
    int maxOnes(int a[], int n)
    {
        // Your code goes here
        int sum = 0, maxi = 0;
        for(int i = 0; i < n; i++)
        {
            if(a[i] == 0)
                sum++;
            else
                sum--;
            maxi = max(maxi,sum);
            if(sum < 0)
                sum = 0;
        }
        
        for(int i = 0; i < n; i++)
            maxi += a[i];
        return maxi;
    }
};