

//User function Template for Java

class Solution{
    //Function to check if two arrays are equal or not.
    public static boolean check(long A[],long B[],int N)
    {
        Arrays.sort(A);
        Arrays.sort(B);
        int count=0;
        for(int i=0;i<N;i++)
        {
            if(A[i]==B[i])
            count++;
        }
        if(count==N)
        return true;
        
        return false;
    }
}