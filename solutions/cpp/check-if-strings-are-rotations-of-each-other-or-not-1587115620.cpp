
class Solution
{
    public:
    //Function to check if two strings are rotations of each other or not.
    bool areRotations(string s1,string s2)
    {
        // Your code here
        int n1=s1.length();
        int n2=s2.length();
        if(n1!=n2)return 0;
        for(int i=0;i<n2;i++){
            if(s1.substr(i,n2)==s2)return 1;
            s1+=s1[i];
            
        }
        return 0;

    }
};