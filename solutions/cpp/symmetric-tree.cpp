/*
Structure of the node of the tree is as
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
    bool docheck(Node *head1 ,Node *head2){
        if(head1 == nullptr && head2 == nullptr)
         return true;
         if(head1 == NULL || head2 == NULL || head1 ->data != head2 -> data)
             return false;
          return docheck(head1 -> left,head2 -> right) 
                &&  docheck(head1 -> right,head2 -> left);
    }
    // return true/false denoting whether the tree is Symmetric or not
    bool isSymmetric(struct Node* root)
    {
	    // Code here
	       if(root == NULL)
	     return true;
	    return docheck(root -> left,root -> right);
    }
};