

class Solution
{
    public:
    //Function to find the nodes that are common in both BST. 
int myLeft(Node *root){
        
        if(root->left == NULL) return root->data;
        
        return myLeft(root->left);
    }
    
    int myRight(Node *root){
        
        if(root->right == NULL) return root->data;
        
        return myRight(root->right);
    }
    
    void solve(Node *root,int left,int right,unordered_map<int,bool>&mp){
        
        if(root == NULL) return;
        
        if(root->data >=left and root->data <= right){
            mp[root->data] = true;
            solve(root->left,left,right,mp);
            solve(root->right,left,right,mp);
        }
        else if(root->data > right){
            solve(root->left,left,right,mp);
        }
        else if(root->data < left){
            solve(root->right,left,right,mp);
        }
    }
    vector <int> findCommon(Node *root1, Node *root2)
    {
     //Your code here
     int left1 = myLeft(root1);
        int right1 = myRight(root1);
        
        int left2 = myLeft(root2);
        int right2 = myRight(root2);
        
        int left = max(left1,left2);
        int right = max(right1,right2);
        
        unordered_map<int,bool> mp1;
        unordered_map<int,bool> mp2;
        
        solve(root1,left,right,mp1);
        solve(root2,left,right,mp2);
        
        vector<int> ans;
        
        for(auto x:mp1){
            if(mp2[x.first] == true) ans.push_back(x.first);
        }
        
        sort(ans.begin(),ans.end());
        return ans;
    }
};

