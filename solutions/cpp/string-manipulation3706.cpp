//User function Template for C++

class Solution{
    public:
    int removeConsecutiveSame(vector <string > v) 
    {
        // Your code goes here
        stack<string>st;
        for(int i=0;i<v.size();i++)
        {
            if(st.empty()||st.top()!=v[i])
            st.push(v[i]);
            else if(v[i]==st.top())
            st.pop();
        }
        return st.size();
    } 
};