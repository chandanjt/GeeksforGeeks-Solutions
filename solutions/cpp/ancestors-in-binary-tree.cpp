//User function template for C++

/*
Structure of a node is as following
struct Node
{
     int data;
     struct Node* left;
     struct Node* right;
};
*/

class Solution{
  public:
    // Function should return all the ancestor of the target node
    vector<int>ans;
    bool check(struct Node *root, int target)
    {
          if(root==NULL)
         return 0;
         if(root->data==target)
         return true;
         if(check(root->left,target)||check(root->right,target) )
         {
             ans.push_back(root->data);
           
         }
       
    }
    vector<int> Ancestors(struct Node *root, int target)
    {
         // Code here
       check(root,target);
       return ans;
    }
};