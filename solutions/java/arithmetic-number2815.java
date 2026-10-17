

//User function Template for Java

class Solution{
    static int inSequence(int A, int B, int C){
        // code here
        if(A==B)
        return 1;
        if((B>A && C>0)|| (A>B && C<0))
        {
            if((B-A)%C==0)
            return 1;
        }
        return 0;
    }
}