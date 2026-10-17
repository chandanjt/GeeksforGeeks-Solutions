//User function Template for C++
class Solution
{
    public:
    string reverseWord(string str)
    {
        // string ans="";
        int n=str.length();
      for(int i=0; i<str.length()/2;i++)
      {
          swap(str[i],str[n-i-1]);
      }
      //return ans;
    //reverse(str.begin(),str.end());
    return str;
    }
};
