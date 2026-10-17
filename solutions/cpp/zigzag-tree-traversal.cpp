//User function Template for C++
/*Structure of the node of the binary tree is as
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution{
    public:
    //Function to store the zig zag order traversal of tree in a list.
    vector <int> zigZagTraversal(Node* root)
    {
    	// Code here
        vector<int> res;
        queue<Node*> q;
        q.push(root);
        if(root==NULL)
        return res;
        int count=0;
        while(1)
        {
            int size=q.size();
            if(size==0)
            return res;
            vector<int>data;
            count++;
            while(size>0)
            {
                Node*temp=q.front();
                q.pop();
                data.push_back(temp->data);
                if(temp->left!=NULL)
                q.push(temp->left);
                if(temp->right!=NULL)
                q.push(temp->right);
                size--;
            }
            if(count%2==0)
            reverse(data.begin(),data.end());
            for(int i : data) res.push_back(i);
            //res.push_back(data);

        }
        return res;
    }
};