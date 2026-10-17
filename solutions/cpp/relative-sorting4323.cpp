//User function template in C++


class Solution{
    public:
    // A1[] : the input array-1
    // N : size of the array A1[]
    // A2[] : the input array-2
    // M : size of the array A2[]
    
    //Function to sort an array according to the other array.
    vector<int> sortA1ByA2(vector<int> &A1, int N, vector<int> &A2, int M) 
    {
        vector<int>res;
         map<int,int>mp;
         for(auto x: A1)
         {
             mp[x]++;
         }
         for(auto y: A2)
         {
         if(mp.find(y)!=mp.end())
         {
             auto x=mp.find(y);
             int count=x->second;
             vector<int>v(count,y);
             res.insert(res.end(),v.begin(),v.end());
             mp.erase(y);
         }}
         for(auto x:mp)
         {
             int element=x.first;
             int count=x.second;
             vector<int>v(count,element);
              res.insert(res.end(),v.begin(),v.end());
         }
         return res;
    } 
};