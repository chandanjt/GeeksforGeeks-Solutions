/*The structure of Node

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

class Solution{
  public:
    // returns the inorder successor of the Node x in BST (rooted at 'root')
    void inorder(Node*root,vector<Node*> &v)
  {
      if(root==NULL){
          return;
      }
      inorder(root->left,v);
      v.push_back(root);
      inorder(root->right,v);
  }
    Node * inOrderSuccessor(Node *root, Node *x)
    {
        //Your code here
         vector<Node*> v;
        inorder(root,v);
        for(int i=0;i<v.size()-1;i++)
        {
            if(v[i]==x){
                return v[i+1];
            }
        }
        return nullptr;
    }
};