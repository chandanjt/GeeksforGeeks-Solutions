class Solution{
	
	
	
	public:
	void shuffleArray(int arr[],int n)
	{
	    // Your code goes here
	    int mod=(int)(1e4)+1;
	    for(int i=0;i<n;i++)
	    {
	        arr[i]=arr[i]*mod;
	    }
	    int x=n/2;
	    int y=1;
	    for(int i=1;i<n-1;i++)
	    {
	        if(i%2)
	        {
	            int z1=arr[i]/mod;
	            int z2=arr[x]/mod;
	            x++;
	            arr[i]=(z1)*mod+z2;
	        }
	        else
	        {
	            int z1=arr[i]/mod;
	            int z2=arr[y]/mod;
	            y++;
	           arr[i]=(z1)*mod+z2;
	        }
	    }
	    arr[0]/=mod;
	    arr[n-1]/=mod;
	    for(int i=1;i<n-1;i++)
	    {
	        arr[i]=arr[i]%mod;
	    }

	}
		 

};