

//User function Template for Java

class Solution
{
    
    ArrayList<Integer> rotate(int N, int D)
    {
        // your code here
        int left=0,right=0;
        int[] arr=new int[16];
        D=D%16;
         for(int i=0;i<16;i++)
         {
             arr[i]=(N&1)==1?1:0;
             N=N/2;
         }
         int j=0;
         int x=(16-D)%16;
         int y=D;
         while(j<16)
         {
             if(arr[x]==1)
             {
                 left+=1<<j;
             }
             if(arr[y]==1)
             right+=1<<j;
             
             x=(x+1)%16;
             y=(y+1)%16;
             j++;
         }
         ArrayList<Integer>res=new ArrayList<>();
         res.add(left);
         res.add(right);
         
         return res;
    }
}