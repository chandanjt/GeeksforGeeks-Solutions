//User function Template for C++

class Solution
{
   public:
    int findSum(int A[], int N)
    {
    	//code here.
    	int mini=A[0],maxi=A[0];
    	for(int i=1;i<N;i++)
    	{
    	     mini = min(mini,A[i]);
            maxi = max(maxi,A[i]);
    	}
    	return mini+maxi;
    }

};