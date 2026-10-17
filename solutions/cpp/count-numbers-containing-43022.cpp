
class Solution {
  public:
  int count(int n)
  {
      int res=0;
      while(n>0)
      {
          if(n%10==4)
          {
          res++;
          break;
          }
          n=n/10;
      }
      return res;
  }
    int countNumberswith4(int n) {
        // code here
        int res=0;
        for(int i=3;i<=n;i++)
        {
            res+=count(i);
        }
        return res;
    }
};