

/*
Structre of the node of the tree is as
struct Node
{
	int data;
	Node* left, *right;
};
*/
// you are required to complete this function

struct Node* deletionBT(struct Node* root, int key)
{
    // code here
    queue<Node*>q;
    if(root==NULL)
    return root;
    q.push(root);
    Node* keynode,*lastnode,*curr;
    while(!q.empty())
    {
         curr=q.front();
        q.pop();
        if(curr->data==key)
        keynode=curr;
        if(curr->left!=NULL)
        {
            q.push(curr->left);
            lastnode=curr;
        }
        if(curr->right!=NULL)
        {
        q.push(curr->right);
        lastnode=curr;
        }
    }
   keynode->data=curr->data;
   
   if(lastnode->left==curr)
   lastnode->left=NULL;
   
   if(lastnode->right==curr)
   lastnode->right=NULL;
    return root;
}