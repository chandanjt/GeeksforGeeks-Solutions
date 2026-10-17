// function Template for C++

/* A binary tree node has data, pointer to left child
   and a pointer to right child /
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
}; */

class Solution {
  public:
    // Function to convert a binary tree into its mirror tree.
    void mirror(Node* node) {
        if(node==NULL)
        return;
        stack<Node*>st;
        st.push(node);
        while(!st.empty())
        {
            Node* temp=st.top();
            st.pop();
            if(temp!=NULL)
            {
                st.push(temp->left);
                st.push(temp->right);
                swap(temp->left,temp->right);
            }
        }
    }
};