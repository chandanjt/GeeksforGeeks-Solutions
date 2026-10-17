

/*node class of the linked list is as:
class Node {
	int data;
     Node next;
     Node(int key)
     {
         data = key;
         next = null;
     }
}
*/
// Your task is to complete the function
// function should return the modular Node
// if no such node is present then return -1
class GfG
{
    public static int moduarNode(Node head, int k)
    {
        int count=0;
        Node temp=head;
        while(temp!=null)
        {
            count++;
            temp=temp.next;
        }
        while(count%k!=0)
        {
            count=count-1;
            if(count==0)
            break;
        }
        int len=count;
        Node temp1=head;
        for(int i=1;i<len;i++)
        {
            temp1=temp1.next;
        }
        if(count==0)
        return -1;
        return temp1.data;
    }
}