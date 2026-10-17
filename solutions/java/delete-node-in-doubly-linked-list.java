

//User function Template for Java

/* Structure of linkedlist node
class Node
{
	int data;
	Node next;
	Node prev;
	Node(int d)
	{
		data = d;
		next = prev = null;
	}
}
*/
class Solution
{
    // function returns the head of the linkedlist
    Node deleteNode(Node head,int x)
    {
		Node temp=head;
		if(x==1)
		{
		    head=head.next;
		    head.prev=null;
		    return head;
		}
		Node temp1=head.next;
	
		int count=1;
		while(count<x-1)
		{
		    temp=temp.next;
		    temp1=temp1.next;
		    count++;
		}
		if(temp1.next==null)
		temp.next=null;
		temp.next=temp1.next;
		temp1.prev=temp1;
		
		return head;
    }
}