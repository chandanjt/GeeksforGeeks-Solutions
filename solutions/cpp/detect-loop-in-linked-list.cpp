//User function template for C++

/*

struct Node
{
    int data;
    struct Node *next;
    Node(int x) {
        data = x;
        next = NULL;
    }

*/
class Solution
{
    public:
    //Function to check if the linked list has a loop.
    bool detectLoop(Node* head)
    {
        if(head==NULL)
        return false;
        Node *slow1=head;
        Node *fast1=head;
        while(fast1 && fast1->next)
        {
            slow1=slow1->next;
            fast1=fast1->next->next;
            if(slow1==fast1)
            return true;
            
        }
        return false;
    }
};