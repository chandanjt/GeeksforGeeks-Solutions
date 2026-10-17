//User function Template for C++
class Solution
{
    public:
    int countFractions(int n, int numerator[], int denominator[])
    {
       unordered_map<float,int>mp;
       int count=0;
        for(int i=0;i<n;i++)
        {
           float x=(float)(denominator[i]-numerator[i])/denominator[i];
           float y=(float)numerator[i]/denominator[i];
      if(mp.find(x)!=mp.end())
      count+=mp[x];
      
      mp[y]++;
            
        }
       return count;
    }
};