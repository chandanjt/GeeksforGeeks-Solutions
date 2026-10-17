//User function template for C++
class Solution{
public:	
         void solve(int n,vector<string>&ans,int count1,int count0,string s)
    {
        if(count0>count1)
        return;
        
        if(s.size()==n)
        {
            ans.push_back(s);
            return;
        }
        
        solve(n,ans,count1+1,count0,s+'1');
        solve(n,ans,count1,count0+1,s+'0');
    }
	vector<string> NBitBinary(int n)
	{
	    // Your code goes here
	     vector<string> ans;
    solve(n,ans,0,0,"");
    
    return ans;
	}
};