//User function template for C++
class Solution{
public:	
	// Function to check if array has 2 elements
	// whose sum is equal to the given value
	bool hasArrayTwoCandidates(int arr[], int n, int x) {
	    // code here
	    unordered_map<int,int>m;
	    for(int i=0;i<n;i++)
	    {
	      int key=arr[i];
	      m[key]++;
	    }
	    for(auto itr=m.begin();itr!=m.end();itr++)
	    {
	        int key= itr->first;
	        int val=itr->second;
	        
	        int pair=x-key;
	        if(pair==key)
	        {
	        if(val>1)
	        return true;
	        }
	        else
	        
	        {
	            if(m.find(pair)!=m.end())
	            return true;
	        }
	    }
	    return false;
	    
	}
};