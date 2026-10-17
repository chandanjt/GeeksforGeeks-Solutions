

class Solution
{
    public int NthTerm(int n)
    {
    
       long mod=1000000007;
       long a[]=new long[n+1];
       a[1]=2;
       for(int i=2;i<=n;i++)
       {
           a[i]=(a[i-1]*i+1)%mod;
       }
       return (int)(a[n]%mod);
    }
}