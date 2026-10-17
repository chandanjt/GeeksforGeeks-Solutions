

/*
Structure of the binary Search Tree is as
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
// your task is to complete the Function
// Function should return median of the BST
void inorder(vector<int> &ans, Node* root){
    if(root==NULL){
        return;
    }
    
    inorder(ans, root->left);
    ans.push_back(root->data);
    inorder(ans, root->right);
}
float findMedian(struct Node *root)
{
      //Code here
       vector<int> ans;
      inorder(ans, root);
      if(ans.size()&1){
          int ind = ans.size()/2;
          return ans[ind];
      }
      int ind1 = ans.size()/2;
      int ind2 = ind1-1;
      
      return (float)((float)(ans[ind1]+ans[ind2])/2.0);
}