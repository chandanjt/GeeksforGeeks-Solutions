

//User function Template for Java

//User function Template for Java
class Solution
{
    public int[] twoOddNum(int Arr[], int N)
    {
        int all=0;
        for(int i=0;i<N;i++)
        {
            all=all^Arr[i];
        }
        int m=all & -all;
        int g1=0;
        int g2=0;
        for(int i=0;i<Arr.length;i++)
        {
            if((m&Arr[i])==0)
            {
                g1^=Arr[i];
            }
            else
            g2^=Arr[i];
        }
        int ans[]=new int[2];
        if(g1>g2)
        {
            ans[0]=g1;
            ans[1]=g2;
        }
        else
        {ans[0]=g2;
        ans[1]=g1;
        }
        return ans;
    }
}