

/*   
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */
vector<int> reverseLevelOrder(Node *root)
{
    vector<int>ans;
    queue<Node*>q;
    stack<int>st;
    if(root==NULL)
    return ans;
    q.push(root);
    while(!q.empty())
    {
        Node* temp=q.front();
        q.pop();
         if(temp->right!=NULL)
        q.push(temp->right);
        
        if(temp->left!=NULL)
        q.push(temp->left);
       
        st.push(temp->data);
    }
    while(!st.empty())
    {
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}