/* Node structure
struct Node
{
    int data;
    Node* left, *right;
}; */

/* Given two trees, should return true if they are
   mirror of each other. */
class Solution
{
    public:
    int areMirror(Node* a, Node* b) {
    // Your code here
     if(a==NULL && b==NULL){
         return 1;
     }
     if(a==NULL || b==NULL){
         return 0;
    }
    if(a->data!=b->data){
        return 0;
    }
    int left=areMirror(a->left,b->right);
    int right=areMirror(a->right,b->left);
    if(left&&right){
        return 1;
    }
    return 0;
    }

};