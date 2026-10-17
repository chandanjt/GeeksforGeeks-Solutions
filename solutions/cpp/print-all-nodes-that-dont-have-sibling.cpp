

//User function Template for C++

/* Tree node structure  used in the program
 struct Node
 {
     int data;
     Node* left, *right;
}; */

vector<int> noSibling(Node* node)
{
    // code here
    vector<int>ans;
    int flag=0;
    if(node==NULL)return {};
    queue<Node *>q;
    q.push(node);
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            Node *temp=q.front();
            q.pop();
            if(temp->left==NULL && temp->right!=NULL){
                flag=1;
                ans.push_back(temp->right->data);
            }
            if(temp->right==NULL && temp->left!=NULL){
                flag=1;
                ans.push_back(temp->left->data);
            }
            if(temp->left)q.push(temp->left);
            if(temp->right)q.push(temp->right);
        }
    }
    sort(ans.begin(),ans.end());
    if(flag==1){
        return ans;
    }
    else{
        return {-1};
    }
}