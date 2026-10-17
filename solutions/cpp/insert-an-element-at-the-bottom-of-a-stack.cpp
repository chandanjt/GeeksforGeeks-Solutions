//User function Template for C++

class Solution{
public:
    void insertbottom(stack<int>&st,int element)
{
    if(st.empty())
    {
        st.push(element);
        return;
    }
    int top=st.top();
    st.pop();
    insertbottom(st,element);
    st.push(top);
}
    stack<int> insertAtBottom(stack<int> st,int x){
        insertbottom(st,x);
        return st;
    }
};