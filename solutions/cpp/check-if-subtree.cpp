/* A binary tree node

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

class Solution
{
  public:
    //Function to check if S is a subtree of tree T.
    bool ans= false;
    bool match(Node* T, Node* S)
    {
        if(T!=NULL && S!=NULL)
        {
        bool a=match(T->left,S->left);
        bool b=match(T->right,S->right);
        if((T->data==S->data)&& a&&b)
        {
            return true;
        }
        else
        return false;
        }
        else if(T==NULL && S==NULL)
        return true;
        else 
        return false;
    }
    void inordert(Node* T, Node* S)
    {
        if(T!=NULL)
        {
            inordert(T->left,S);
            bool x=match(T,S);
            if(x)
            ans=x;
            inordert(T->right,S);
        }
    }
    bool isSubTree(Node* T, Node* S) 
    {
        // Your code here
        inordert(T,S);
        return ans;
        
    }
};