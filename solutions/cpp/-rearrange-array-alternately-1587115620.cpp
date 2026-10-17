class Solution{
    public:
    // This function wants you to modify the given input
    // array and no need to return anything
    // arr: input array
    // n: size of array
    //Function to rearrange  the array elements alternately.
    void rearrange(long long *arr, int n) 
    { 
    	
    	// Your code here
    	int max_indx=n-1;
    	int min_indx=0;
    	int maxval=arr[n-1]+1;//6+1=7
    	for(int i=0;i<n;i++)
    	{
    	    if(i%2==0)
    	    {
    	        //wrting two value at one place i.e. 6%7*7+1->43/7=6 & 43%7=1
    	        arr[i]=(arr[max_indx]%maxval)*maxval+arr[i];
    	        max_indx--;
    	    }
    	    else
    	    {
    	        //43%7*7+2=9 -->9/7=1 & 9%7=2
    	    arr[i]=(arr[min_indx]%maxval)*maxval+arr[i];
    	    min_indx++;
    	    }
    	}
    	for(int i=0;i<n;i++)
    	{
    	    arr[i]=arr[i]/maxval;
    	}
    	 
    }
};