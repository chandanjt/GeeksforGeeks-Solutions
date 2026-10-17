/*Complete the function below

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};
*/

class Solution{
    public:
    //Function to check whether all nodes of a tree have the value 
    //equal to the sum of their child nodes.
    int isSumProperty(Node *root)
    {
     if(root==NULL||(root->left==NULL && root->right==NULL))
       return 1;
       
       int lsum=0;
       int rsum=0;
       if(root->left!=NULL)
       lsum=root->left->data;
       if(root->right!=NULL)
       rsum=root->right->data;
       if(root->data==(lsum+rsum)&&isSumProperty(root->left) && isSumProperty(root->right))
       return 1;
       else
       return 0;
    }
};