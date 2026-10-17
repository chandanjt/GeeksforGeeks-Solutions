// User function Template for C++
class Solution {
  public:
    string armstrongNumber(int n) {
        // code here
        int temp=n;
        int sum=0;
        while(n>0)
        {
            int rem=n%10;
            n=n/10;
            sum+=pow(rem,3);
        }
        if(sum==temp)return "true";
        
        return "false";
    }
};