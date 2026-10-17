class Solution
{
    public:
    //Function to check if two strings are isomorphic.
    bool areIsomorphic(string str1, string str2)
    {
        
        // Your code here
        if(str1.length()!=str2.length())return false;
        unordered_map<char,char>mp;
        unordered_set<char>us;
        for(int i=0;i<str1.length();i++){
            if(mp.find(str1[i])==mp.end()){
                mp[str1[i]]=str2[i];
                if(us.find(str2[i])!=us.end())return false;
                else us.insert(str2[i]);
            }
            else {
                if(mp[str1[i]]!=str2[i])return false;
            }
        }
        return true;
    }
};