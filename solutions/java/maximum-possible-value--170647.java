

//User function Template for Java
class Solution 
{ 
    long maxPossibleValue(int N, int A[] ,int B[]) { 
        long minlen=Integer.MAX_VALUE;
        long totstick=0;
        long totper=0;
        for(int i=0;i<N;i++)
        {
            if(B[i]%2==1)
            B[i]--;
            if(B[i]>=2)
            minlen=Math.min(minlen,A[i]);
            totstick+=B[i];
            totper+=B[i]*A[i];
        }
        if(totstick%4!=0)
        totper -=2*minlen;
        
        return totper;
        
    }
} 