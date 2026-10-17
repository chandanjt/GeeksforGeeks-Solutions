/*
 
  Node is defined as
  struct Node {
    int data;
    struct Node *next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

*/
class Solution
{
    public:
    //Function to sort a linked list of 0s, 1s and 2s.
    Node* segregate(Node *head) {
        
        // Add code here
       /* vector<int>store;
        Node* temp=head;
        while(temp!=NULL)
        {
            store.push_back(temp->data);
            temp=temp->next;
        }
        sort(store.rbegin(),store.rend());
        
        Node * newhead=NULL;
       
        for(int i=0;i<store.size();i++)
        {
            Node* newnode=new Node(store[i]);
            if(newhead==NULL)
            newhead=newnode;
            else
            {
                newnode->next=newhead;
                newhead=newnode;
            }
        }
        return newhead;*/
        Node *temp=head;
        int count[3]={0,0,0};
        while(temp!=NULL)
        {
            count[temp->data] +=1;
            temp=temp->next;
        }
        int i=0;
        temp=head;
        while(temp!=NULL)
        {
            if(count[i]==0)
            ++i;
            else
            {
                temp->data=i;
                --count[i];
                temp=temp->next;
            }
        }
        return head;
    }
};