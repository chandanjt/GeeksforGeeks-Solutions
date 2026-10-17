//User function Template for C++
class Solution
{
public:
    void gfSeries(int N)
    {
        // Write Your Code here
            long long a=0,b=1,c=0;
            cout<<a<<" "<<b<<" ";
      while(N-2>0)
      {
          c=a*a-b;
          cout<<c<<" ";
          a=b;
          b=c;
          N--;
      }
      cout<<endl;
    }
    
};