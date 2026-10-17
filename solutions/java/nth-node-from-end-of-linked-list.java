

/* Structure of node

class Node
{
    int data;
    Node next;
    Node(int d) {data = d; next = null; }
}
*/

class GfG
{
    //Function to find the data of nth node from the end of a linked list.
    int getNthFromLast(Node head, int n)
    {
    int count=0;
    Node temp=head;
    while(temp!=null)
    {
        count++;
        temp=temp.next;
    }
    if(count<n)
    return -1;
    Node temp1=head;
    for(int i=1;i<count-n+1;i++)
    {
        temp1=temp1.next;
    }
    return temp1.data;
}
}