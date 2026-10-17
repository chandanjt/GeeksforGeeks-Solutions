

//User function Template for Java

class Solution {
    static int fillingBucket(int N) {
        if(N==1)
        return 1;
        long a=1;
        long b=1;
        long c=0;
        long mod=100000000;
        for(int i=2;i<=N;i++)
        {
            c=((a%mod)+(b%mod))%mod;
            a=b%mod;
            b=c%mod;
        }
        return (int)(c%mod);
    }
};