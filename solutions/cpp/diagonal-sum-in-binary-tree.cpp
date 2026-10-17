/*Complete the function below
Node is as follows:
struct Node{
    int data;
    Node *left,*right;
};
*/

class Solution
{
    public:
    vector <int> diagonalSum(Node* root) {
        if(root==NULL)
        return {};
        // Add your code here
        vector<int>res;
        queue<Node*>q;
        q.push(root);
        while(!q.empty())
        {
            int size=q.size();
            // if(size==0)
            // break;
            int sum=0;
            while(size>0)
            {
                Node* temp=q.front();
                q.pop();
                while(temp!=NULL)
                {
                    sum=sum+temp->data;
                    if(temp->left!=NULL)
                    q.push(temp->left);
                    temp=temp->right;
                }
                size--;
            }
            res.push_back(sum);
        }
        return res;
    }
};