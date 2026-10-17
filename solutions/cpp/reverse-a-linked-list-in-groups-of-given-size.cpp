/*
  Reverse a linked list
  The input list will have at least one element  
  Return the node which points to the head of the new LinkedList
  Node is defined as 
    struct node
    {
        int data;
        struct node* next;
    
        node(int x){
            data = x;
            next = NULL;
        }
    
    }*head;
*/

class Solution
{
    public:
    struct node *reverse (struct node *head, int k)
    { 
        // Complete this method
          node* cur=head;

        node* prev=NULL;

        int count=0;

        while(count <k && cur!=NULL){

            node* next=cur->next;

            cur->next=prev;

            prev=cur;

            cur=next;

            count++;

        }

       if (cur != NULL) {

        head->next = reverse(cur, k);

    }

        return prev;
    }
};