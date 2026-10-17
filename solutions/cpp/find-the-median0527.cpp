class Solution
{
public:
	public:
		int find_median(vector<int> v)
		{
		    // Code here.
		    sort(v.begin(),v.end());
		    int len =v.size();
		    int s=len/2;
		    if(len%2==0)
		    return ((v[s]+v[s-1])/2);
		    
		    return v[s];
		}
};