

/*
class Node{
    int data;
    Node next;
    
    Node(int x){
        data = x;
        next = null;
    }
}
*/
class Solution
{
    //Function to insert a node at the beginning of the linked list.
    Node insertAtBeginning(Node head, int x)
    {
        Node newnode=new Node(x);
        if(head==null)
        head=newnode;
        else
        {
            newnode.next=head;
            head=newnode;
        }
        return head;
    }
    
    //Function to insert a node at the end of the linked list.
    Node insertAtEnd(Node head, int x)
    {
        Node newnode=new Node(x);
        if(head==null)
        head=newnode;
        
        else
        {
            Node temp=head;
            while(temp.next!=null)
            {
                temp=temp.next;
            }
            temp.next=newnode;
        }
        return head;
    }
}