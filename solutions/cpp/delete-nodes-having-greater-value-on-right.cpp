/*

The structure of linked list is the following

struct Node
{
    int data;
    Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};
*/
class Solution
{
    public:
    Node *compute(Node *head)
    {
        if(head==NULL|| head->next==NULL)
        return head;
       Node *nex=compute(head->next);
        Node *curr=head;
        if(curr->data<nex->data){
            curr=nex;
            head=curr;
        }else{
            curr->next=nex;
            head=curr;
        }
        return head;
    }
    
};
   