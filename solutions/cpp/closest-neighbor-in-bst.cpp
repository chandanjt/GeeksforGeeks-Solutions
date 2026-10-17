// Function to search a node in BST.
class Solution{

public:
    int floor(Node* root, int x) {
        // Code here
        int ans  = INT_MAX;
        int val = -1;
        while(root)
        {
            if(root->data == x) return x;
            else if(root->data > x)
            {
                root = root->left;
            }
            else 
            {
                int diff = x - root->data;
                if(ans > diff)
                {
                    ans = diff;
                    val = root->data;
                }
                root = root->right;
                
            }
        }
        return val;
    }
};