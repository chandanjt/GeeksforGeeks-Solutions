/*The Node structure is
struct Node {
int data;
Node * right, * left;
};*/

/*You are required to complete below method */
class Solution{
  public:
  unordered_map<int,int> hash;
    bool isDeadEnd(Node *root)
    {
        //Your code here
        if(root == NULL) return false;
        if(root->left == NULL && root->right == NULL){
                if(root->data == 1) return true;
                if(hash.count(root->data-1) && hash.count(root->data+1)) 
                    return true;
        }else{
            hash[root->data] = 1;
            return isDeadEnd(root->left) || isDeadEnd(root->right);
        }
        
    
    }
};