

class Solution
{
    public:
    //Function to calculate the span of stockâ€™s price for all n days.
    vector <int> calculateSpan(int price[], int n)
    {
       // Your code here
       stack<pair<int,int>>st;
       vector<int>v;
       
       for(int i=0;i<n;i++)
       {    int res=1;
           while(!st.empty()&&st.top().first<=price[i])
           {
               res +=st.top().second;
               st.pop();
           }
           st.push({price[i],res});
           v.push_back(res);
       }
       return v;
    }
};
