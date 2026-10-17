//function Template for C++

//Function to reverse the queue.
class Solution
{
    public:
    void reverseq(queue<int>&q)
    {
        if(q.empty())
        return;
        int temp=q.front();
        q.pop();
        reverseq(q);
        q.push(temp);
    }
    queue<int> rev(queue<int> q)
    {
        // add code here.
       /* stack<int>st;
       while(!q.empty())
       {
           st.push(q.front());
           q.pop();
       }
       while(!st.empty())
       {
           q.push(st.top());
           st.pop();
       }
       return q;*/
       reverseq(q);
       return q;
       
    }
};