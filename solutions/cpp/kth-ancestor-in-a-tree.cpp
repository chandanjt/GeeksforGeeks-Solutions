

//User function Template for C++
/*
Structure of the node of the binary tree is as
struct Node
{
	int data;
	struct Node *left, *right;
};
*/
// your task is to complete this function
Node *tar=NULL;
 unordered_map<Node*,Node*> mp ;
void store(Node *root ,int node){
    if(!root) return;
    mp[root->left] = root;
    mp[root->right] = root;
    
    if(root->data==node){
        tar=root;
    }
    
    store(root->left , node);
    store(root->right , node);
    
}
int kthAncestor(Node *root, int k, int node)
{
    // Code here
        int ans=0;
    store(root , node);
    while(mp.find(tar)!=mp.end() && k--){
        // cout<<mp[tar]->data<<endl;
        ans=mp[tar]->data;
        tar=mp[tar];
    }
    // cout<<k<<endl;
    if(k>0)
    return -1;
    
    return ans;
}