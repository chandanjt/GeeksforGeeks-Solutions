/*
  reverse alternate nodes and append at the end
  The input list will have at least one element  
  Node is defined as 
  struct Node
  {
      int data;
      struct Node *next;
    
      Node(int x){
        data = x;
        next = NULL;
      }
    
   };

*/
class Solution
{
    public:
    void rearrange(struct Node *head)
    {
        //add code here
        Node* odd = head;
        Node* even = head->next;
        Node* even1=even;
    while(even!=NULL && even->next!=NULL)
    {
        odd->next = odd->next->next;
        even->next=even->next->next;
        odd=odd->next;
        even=even->next;
    }
     Node *current,*nextnode,*prev;
     current=nextnode=even1;
     prev=NULL;
     while(current!=0)
     {
         nextnode=current->next;
         current->next=prev;
         prev=current;
         current=nextnode;
     }
     odd->next=prev;
    }
    
};

