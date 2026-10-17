/*
struct Node
{
    int data;
    Node * next;
    Node * prev;
    Node (int x)
    {
        data=x;
        next=NULL;
        prev=NULL;
    }
        
};
*/
class Solution
{
    public:
    Node* reverseDLL(Node * head)
    {
        //Your code here
          Node *temp=head;
        while(head->next!=NULL){
            temp=head->prev;
            head->prev=head->next;
            head->next=temp;
            head=head->prev;
        }
        head->next=head->prev;
        head->prev=NULL;
        return head;
    }
};
