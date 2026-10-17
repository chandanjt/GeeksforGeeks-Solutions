

//User function Template for Java

class Solution {
    int A[][]=new int[100][100];
    
    int removals(int[] arr, int n, int k) {
        // code here
        Arrays.sort(arr);
        for(int [] r:A)
        {
            Arrays.fill(r,-1);
        }
        return solution(arr,0,n-1, k);
    }
    int solution(int arr[],int i,int j,int k)
    {
        if(i>=j)
        return 0;
        if(arr[j]-arr[i]<=k)
        return 0;
        if(A[i][j]!=-1)
        {
            return A[i][j];
        }
        A[i][j]=1+Math.min(solution(arr,i+1,j,k),solution(arr,i,j-1,k));
        return A[i][j];
    }
    
}