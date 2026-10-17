

/* Node is as follows:

struct Node
{
	int data, height;
	Node *left, *right;
	Node(int x)
	{
		data = x;
		height = 1;
		left = right = NULL;
	}
};

*/
vector<Node *>curr ; 
void inorder(Node * root , int data){
    if(!root) return ; 
    inorder(root->left , data) ; 
    if(root->data != data){
        curr.push_back(root) ; 
    }
    inorder(root->right , data) ; 
}

Node * build(int i , int j){
    if(i>j) return NULL ; 
    int mid = (i+j)/2 ; 
    Node * root = curr[mid] ; 
    root->left = build(i , mid-1) ; 
    root->right = build(mid+1 , j) ; 
    return root ; 
}
Node* deleteNode(Node* root, int data)
{
    //add code here,
       curr.clear() ; 
    inorder(root , data) ; 
    int i = 0 ; 
    int j = curr.size()-1 ; 
    return build(i,j) ; 
}