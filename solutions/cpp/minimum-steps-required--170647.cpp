// User function Template for C++

int minSteps(string str) {
    // Write your code here.
    	int count=0;
		for(int i=1;i<str.size();i++)
		{
		    if(str[i-1]!=str[i])
		    count++;
		}
		if(count%2!=0)
		return (count+1)/2 +1;
		
		return count/2+1;
}