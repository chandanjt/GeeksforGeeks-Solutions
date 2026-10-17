//User function template for C++

class Solution{
  public:
    char nthCharacter(string s, int r, int n) {
        //code here
        int mid=s.size()/2;
        for(int i=0;i<r;i++)
        {
            string temp="";
            for(int j=0;j<mid+1;j++)
            {
                if(s[j]=='0')
                temp+="01";
                else
                temp+="10";
            }
            s=temp;
        }
       return s[n];
    }
};