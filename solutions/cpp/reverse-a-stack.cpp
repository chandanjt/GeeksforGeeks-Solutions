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
    void Reverse(stack<int> &St){
        if(St.empty())
        return;
        int top=St.top();
        St.pop();
        Reverse(St);
        insertbottom(St,top);
    }
};