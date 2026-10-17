
class Solution{
    public:
    int DivisibleByEight(string s){
        //code here
        if(s.length()<3)
        return stoi(s)%8?-1:1;
        
        string temp="";
        int n=s.length()-1;
        for(int i=n-2;i<=n;i++)
        {
            temp+=s[i];
        }
        int x=stoi(temp);
        if(x==0)
        return 1;
        if(x%8==0)
        return 1;
        
        return -1;
    }
};