/*
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
};
*/
class Solution
{
public:
    vector<Node *> nodesAtOddLevels(Node *root)
    {
       vector<Node*>ans;
       int count=0;
       queue<Node*>q;
       if(root==NULL)
       return ans;
       q.push(root);
       while(!q.empty())
       {
           int size=q.size();
           count++;
           while(size>0)
           {
               Node* temp=q.front();
               q.pop();
               if(count%2!=0)
               ans.push_back(temp);
               if(temp->left!=NULL)
               q.push(temp->left);
               if(temp->right!=NULL)
               q.push(temp->right);
               size--;
           }
           
       }
       return ans;
    }
};
