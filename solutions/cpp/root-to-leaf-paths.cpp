

/* Structure of Node
struct Node
{
    int data;
    Node* left;
    Node* right;
};*/

/* The function should print all the paths from root
 to leaf nodes of the binary tree */
 void helper( Node*root, vector<vector<int>> &ans, vector<int> temp ){
    if( root==NULL )
        return;
    temp.push_back(root->data);
    if(root->left==NULL && root->right==NULL ){
        ans.push_back(temp);
        return;
    }
    helper( root->left, ans, temp );
    helper( root->right, ans, temp );
    temp.pop_back();
}
 
vector<vector<int>> Paths(Node* root)
{
    // Code here
  
    vector<vector<int>> ans;
    helper( root, ans, {} );
    return ans;
}