/*The Node structure is defined as
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

// return the Kth largest element in the given BST rooted at 'root'
class Solution
{
    public:
    vector<int>vec;
    void inorder(Node* root)
    {
        if(root==NULL)
        {
            return;
        }
        inorder(root->left);
        vec.push_back(root->data);
        inorder(root->right);
    }
    int kthLargest(Node *root, int K)
    {
        inorder(root);
        int n=vec.size();
        return vec[n-K];
    }
};