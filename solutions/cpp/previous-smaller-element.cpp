// User function Template for C++

class Solution{
public:
    vector<int> leftSmaller(int n, int a[]){
        // code here
        vector<int>v;
        stack<int>st;
        for(int i=0;i<n;i++)
        {
            while(!st.empty()&& st.top()>=a[i])
            st.pop();
            int temp=st.empty()?-1:st.top();
            v.push_back(temp);
            st.push(a[i]);
            
        }
        return v;
    }
};