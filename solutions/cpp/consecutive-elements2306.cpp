class Solution{
    public:
    string removeConsecutiveCharacter(string S)
    {
        // code here
        string ans="";
        for(int i=0;i<S.size();i++)
        {
            if(S[i]!=S[i+1])
            ans=ans+S[i];
        }
        return ans;
    }
};