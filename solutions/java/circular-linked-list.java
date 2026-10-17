

/* Structure of LinkedList
class Node
{
	int data;
	Node next;
	Node(int d)
	{
		data = d;
		next = null;
	}
}
*/
class GfG
{
    boolean isCircular(Node head)
    {
       
		Node temp=head;
		if(head==null)
		return true;
		if(head.next==head)
		return true;
while(temp!=null)
{
    if(temp.next==head)
    return true;
    
    temp=temp.next;
}
	
	return false;
		
    }
}