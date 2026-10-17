//User function template for C++

class Solution
{
  public:
    //Function to find the minimum indexed character.
    int minIndexChar(string str, string patt)
    {
        // Your code here
              int index=-1;
        for (int i=0 ; i<str.length();i++)
        {
         
         index = patt.find(str[i]);
        if(index>=0){
            return i;
                  }
        }
        return -1;
    }
};