class Solution
{
    public:
    //Function to find the vertical order traversal of Binary Tree.
  
   
    
    vector<int> verticalOrder(Node *root)
    {
         map<int,vector<int>>mp;
         queue<pair<Node*,int>>q;
          if(root==NULL)
          return {0};
          else
          {
              q.push({root,0});
              while(!q.empty())
              {
                  Node* temp=q.front().first;
                  int x=q.front().second;
                  q.pop();
                  mp[x].push_back(temp->data);
                  if(temp->left!=NULL)
                  q.push({temp->left,x-1});
                  
                  if(temp->right!=NULL)
                  q.push({temp->right,x+1});
              } 
              }
            vector<int>ans;
              for(auto &pri:mp){
            for(auto &ele:pri.second){
                ans.push_back(ele);
            }
        }
            return ans;
    }
};
