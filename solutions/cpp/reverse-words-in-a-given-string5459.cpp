
class Solution
{
    public:
    //Function to reverse words in a given string.
    string reverseWords(string S) 
    { 
        // code here 
        int n=S.length()-1;
        string res="";
        string temp="";
        for(int i=n;i>=0;i--)
        {
         temp=S[i]+temp;
         if(S[i]=='.')
         {
             res=res+temp;
             temp="";
         }
         
        }
        res=res+'.';
        res=res+temp;
        return res.substr(1,res.length());
    } 
};