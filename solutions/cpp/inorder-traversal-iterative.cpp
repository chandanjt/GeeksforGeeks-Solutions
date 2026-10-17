//User function Template for C++

/* Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
};*/
class Solution {
public:
vector<int>ans;
void inorder(Node *root)
{
     if(root==NULL)
        return;
        inorder(root->left);
        ans.push_back(root->data);
        inorder(root->right);
}
    vector<int> inOrder(Node* root)
    {
       inorder(root);
       return ans;
    }
};