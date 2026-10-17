//User function Template for C++


class Solution
{

public:
    int xmod11(string x)
    {
      int value=0,rem=0;
      for(int i=0;i<x.length();i++)
      {
          value=rem*10+x[i]-'0';
          rem=value%11;
      }
    return rem;
    }
};