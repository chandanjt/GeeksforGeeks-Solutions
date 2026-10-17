// User function Template for C++

class Solution{
public:
vector<int>ans;
    vector<int> pattern(int N){
        // code here
         int i=0;
        ans.push_back(N);
        while(ans[i]>0)
        {
             ans.push_back(ans[i]-5);
            i=i+1;
        }
        while(ans[i]<N)
        {
            ans.push_back(ans[i]+5);
            i=i+1;
        }
       return ans; 
    }
};