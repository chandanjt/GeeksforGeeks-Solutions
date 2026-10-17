/* A binary tree node has data, pointer to left child
   and a pointer to right child 
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
}; */

// Should return  right view of tree
class Solution
{
    public:
    //Function to return list containing elements of right view of binary tree.
    vector<int> rightView(Node *root)
    {
       // Your Code here
        vector<int> res;
        queue<Node*>q;
        q.push(root);
        if(root==NULL)
        return res;
        while(1)
        {
            int size=q.size();
            if(size==0)
            return res;
            int data=0;
            while(size>0)
            {
                Node *temp=q.front();
                q.pop();
               data=temp->data;
                if(temp->left!=NULL)
                q.push(temp->left);
                if(temp->right!=NULL)
                q.push(temp->right);
                size--;
            }
            res.push_back(data);
        }
        return res;
    }
};
