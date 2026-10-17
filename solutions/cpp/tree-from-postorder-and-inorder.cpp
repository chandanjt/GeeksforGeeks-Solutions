

/* Tree node structure

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};*/

//Function to return a tree created from postorder and inoreder traversals.
Node* cTree(int in[],int post[],int ins,int ine,int &posIn){
    if(ins>ine) 
    return NULL;
    Node* head=new Node(post[posIn--]);
    int inInd;
    for(int i=ins;i<=ine;i++){
        if(in[i]==head->data){
            inInd=i;
            break;
        }
    }
    head->right=cTree(in,post,inInd+1,ine,posIn);
    head->left=cTree(in,post,ins,inInd-1,posIn);
    return head;
}
Node *buildTree(int in[], int post[], int n) {
    // Your code here
    int poslen=n-1;
    return cTree(in,post,0,n-1,poslen);
}