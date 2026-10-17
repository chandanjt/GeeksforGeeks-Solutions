//User function template for C++

/* The Node structure is
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
}; 
*/

class Solution{
  public:
    // The given root is the root of the Binary Tree
    // Return the root of the generated BST
     void dfs(Node *root,vector<int>&vec){
        if(root==NULL){
            return;
        }
        vec.push_back(root->data);
        dfs(root->left,vec);
        dfs(root->right,vec);
    }
      Node *insert(Node *root,int data){
        if(root==NULL){
            return new Node(data);
        }
        if(data<root->data){
            root->left=insert(root->left,data);
        }
        else{
            root->right=insert(root->right,data);
        }
        return root;
    }
    Node *binaryTreeToBST (Node *root)
    {
        //Your code goes here
         vector<int>vec;
        dfs(root,vec); 
        Node *tree=NULL;
        for(auto ele:vec){
            tree=insert(tree,ele);
        }
        return tree;
    }
};