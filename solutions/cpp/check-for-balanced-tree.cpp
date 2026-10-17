/* A binary tree node structure

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
    //Function to check whether a binary tree is balanced or not.
    int height(Node *root)
    {
        if(root==NULL)
        return 0;
        else
        return max(height(root->left),height(root->right))+1;
    }
    void inordert(Node *root,bool &ans)
    {
      
        if(root!=NULL)
        {
        inordert(root->left,ans);
        int leftht= height(root->left);//isBalanced(root->left);
        int rightht=height(root->right);//isBalanced(root->right);
        if(abs(leftht-rightht)>1)
        ans=ans && false;
        inordert(root->right,ans);
        }
    }
    bool isBalanced(Node *root)
    {
        //  Your Code here
       bool ans=true;
       inordert(root,ans);
        
        return ans;
    }
};

