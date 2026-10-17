



//User function Template for Java


class Solution
{
    //Function to return list containing first n fibonacci numbers.
    public static long[] printFibb(int n) 
    {
        //Your code here
        long[] ans  = new long[n];
    ans[0]=1;
    long a=0,b=1,c=0;
    for(int i=1;i<n;i++)
    {
        c=(a+b);
        a=b;
        b=c;
        ans[i]=c;
    }
    return ans;
    }
}