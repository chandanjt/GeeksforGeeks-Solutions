/*Complete the function below
Node is as follows:
struct Node{
int data;
Node *left,*right;
};
*/
class Solution{
  public:
    vector<int>ans;
    vector <int> verticalSum(Node *root) {
      map<int,vector<int>>mp;
      queue<pair<Node*,int>>q;
      if(root==NULL)
      return ans;
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
    
      int sum=0;
      for(auto &it:mp)
      {
          for(auto &ele:it.second)
          {
              sum=sum+ele;
          }
          ans.push_back(sum);
          sum=0;
      }
      return ans;
    }
};