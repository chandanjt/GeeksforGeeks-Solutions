//User function template for C++

class Solution
{
    public:
    //Function to delete middle element of a stack.
    int curr=0; 
    void deleteMid(stack<int>&s, int sizeOfStack)
    {
        // code here.. 
       /* stack<int>st;
        int mid=sizeOfStack/2;
        for(int i=0;i<mid;i++)
        {
           st.push(s.top());
           s.pop();
        }
        s.pop();
        while(!st.empty())
        {
            s.push(st.top());
            st.pop();
        }*/
        if(curr==sizeOfStack/2)
        {
            s.pop();
            return;
        }
        curr++;
        int temp=s.top();
        s.pop();
        deleteMid(s, sizeOfStack);
        s.push(temp);
        
    }
};