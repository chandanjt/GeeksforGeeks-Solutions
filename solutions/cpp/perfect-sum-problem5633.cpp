class Solution{
int mod=1e9+7;
	public:
		int tras(int arr[], vector<vector<int>>&dp,int sum,int index){
      
         if(index<0)return sum == 0;
	   
	    
	    if(dp[index][sum]!=-1)return dp[index][sum];

	    int count=0;
	 
	    
	if (arr[index] <= sum) {
    count += tras(arr, dp, sum - arr[index], index - 1);
    }
    count += tras(arr, dp, sum, index - 1);

	   
	    return dp[index][sum]= count%mod;
	}
  
	int perfectSum(int arr[], int n, int sum)
	{   vector<vector<int>>dp(n+1,vector<int>(sum+1,-1));
       
        
  
        int index=n-1;
        
        return tras(arr,dp,sum,index);
	}
	  
};