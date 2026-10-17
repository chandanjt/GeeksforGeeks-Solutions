

/* A binary tree Node

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};
 */

//Function to return the level order traversal line by line of a tree.
vector<vector<int>> levelOrder(Node* node)
{
  //Your code here
  vector<vector<int>>ans;
  queue<Node*>q;
  if(node==NULL)
  return ans;
  q.push(node);
 
  while(!q.empty())
  {
      vector<int>data;
      int size=q.size();
      while(size>0)
      {
          Node* temp=q.front();
          q.pop();
          if(temp->left!=NULL)
          q.push(temp->left);
          if(temp->right!=NULL)
          q.push(temp->right);
          data.push_back(temp->data);
          size--;
      }
      
      ans.push_back(data);
      
  }
  return ans;
}
