
/*Complete the code here.
Node is as follows:
struct Node
{
  int data;
  Node* left;
  Node* right;
};
*/
class Solution{
    public :
    int preindx=0;
    Node* cTree(int in[],int pre[],int is,int ie)
    {
        if(is>ie)
        return NULL;
        Node* newnode=new Node(pre[preindx++]);
        //int index=find(in+is,in+ie,pre[preindx-1])-in;or
        int index=0;
        for(int i=is;i<=ie;i++)
        {
            if(in[i]==newnode->data)
            {
                index=i;
                break;
            }
        }
            newnode->left=cTree(in,pre,is,index-1);
            newnode->right=cTree(in,pre,index+1,ie);
            return newnode;
        
    }
    public:
    Node* buildTree(int in[],int pre[], int n)
    {
        return cTree(in,pre,0,n-1);
    }
};