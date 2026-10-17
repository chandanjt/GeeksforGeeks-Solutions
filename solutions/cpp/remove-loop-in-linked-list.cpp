/*
structure of linked list node:

struct Node
{
    int data;
    Node* next;
    
    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

*/

class Solution
{
    public:
    //Function to remove a loop in the linked list.
   
    void removeLoop(Node* head)
    {
       if(!head || !head->next) return ;
        
        auto fast = head,slow=head;
        
        while(fast && fast->next){
            auto prv = slow;
            slow=slow->next;
            fast = fast->next->next;
            
            if(slow==fast) {
                fast = head;

                while(slow->next != fast->next){
                    slow=slow->next;
                    fast=fast->next;
                }
                
                if(slow == head and fast==head) prv->next=NULL;
                else slow->next=NULL;
                return ;
            }
        }
        return ;
   
    }
};