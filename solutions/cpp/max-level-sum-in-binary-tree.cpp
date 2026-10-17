/* Tree node structure  used in the program
 struct Node
 {
     int data;
     Node* left, *right;
}; */

class Solution{
  public:
    /*You are required to complete below method */
    int maxLevelSum(Node* root) {
        queue<Node*>q;
        int sum=INT_MIN,temp;
        if(root==NULL)
        return sum;
        q.push(root);
        while(!q.empty())
        {
            temp=0;
            int size=q.size();
            while(size>0)
            {
                Node* temp1=q.front();
                q.pop();
                temp=temp+temp1->data;
                if(temp1->left!=NULL)
                q.push(temp1->left);
                if(temp1->right!=NULL)
                q.push(temp1->right);
                size--;
            }
            sum=max(sum,temp);
            
        }
        return sum;
    }
};