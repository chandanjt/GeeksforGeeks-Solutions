//User function template for C++
class Solution{
public:	
	int longSubarrWthSumDivByK(int arr[], int n, int k)
	{
	    // Complete the function
	    unordered_map<int, int> mp;
	    /*
	    int max_len=0;
	    mp[0] = -1;
	    int sum=0;
	    for(int i = 0;i<n;i++) {
	        sum = (sum + arr[i]%k)%k;
	        
	        if(sum < 0)
	            sum += k;
	        if(mp.find(sum) != mp.end())
	            max_len = max(max_len, i-mp[sum]);
	        else
	            mp[sum] = i;
	           
	    }

	    return max_len;*/
	    int sum=0,rem,mx=0;
	    for(int i=0;i<n;i++)
	    {
	        sum=sum+arr[i];
	        rem=sum%k;
	        
	        if(rem==0)
	        mx=max(mx,i+1);
	        if(rem<0)
	        rem=rem+k;
	        
	        if(mp.find(rem)!=mp.end())
	        {
	            mx=max(mx,i-mp[rem]);
	        }
	        else
	        mp[rem]=i;
	    }
	    return mx;
	}
};