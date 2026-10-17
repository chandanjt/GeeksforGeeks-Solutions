
class Solution
{
    public:
    //Function to find the first non-repeating character in a string.
    char nonrepeatingCharacter(string S)
    {
       //Your code here
       map<char,int> count;
       for(int i=0; i<S.length(); i++){
           count[S[i]]++;
       }
       for(int i=0; i<S.length(); i++){
           if(count[S[i]]==1){
               return S[i];
           }
       }
       return '$';
       
    }

};