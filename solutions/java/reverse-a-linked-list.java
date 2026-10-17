

//function Template for Java

/* linked list node class:

class Node {
    int data;
    Node next;
    Node(int value) {
        this.value = value;
    }
}

*/

class Solution
{
    //Function to reverse a linked list.
    Node reverseList(Node head)
    {
        Node newnode=null;
        while(head!=null)
        {
            Node next=head.next;
            head.next=newnode;
            newnode=head;
            head=next;
        }
        return newnode;
    }
}