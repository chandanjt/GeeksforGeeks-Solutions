class Solution
{
    public:
    vector<long long> prevsmaller(long long arr[],int n)
{
   vector<long long>v;
   stack<int>st;
   for(int i=0;i<n;i++)
   {
   while(st.empty()==false && arr[st.top()]>=arr[i])
  { st.pop();
  }
   long long temp=st.empty()?-1:st.top();
   v.push_back(temp);
   st.push(i);

   }
 return v;

}

vector<long long> nextsmaller(long long arr[],int n)
{
    vector<long long>v1;
     stack<int>st;
     
     for(int i=n-1;i>=0;i--)
     {
     while(st.empty()==false && arr[st.top()]>=arr[i])
     {st.pop();
     }
     long long temp=st.empty()?n:st.top();
     v1.push_back(temp);
     st.push(i);

     }
reverse(v1.begin(),v1.end());
return v1;
}
    //Function to find largest rectangular area possible in a given histogram.
    long long getMaxArea(long long arr[], int n)
    {
        // Your code here
         vector<long long>ps=prevsmaller(arr,n);
        vector<long long>ns=nextsmaller(arr,n);
       long long res=0;
        for(long i=0;i<n;i++)
        {
           long long curr=(ns[i]-ps[i]-1)*arr[i];
            res=max(res,curr);
        }
        return res;
    }
};