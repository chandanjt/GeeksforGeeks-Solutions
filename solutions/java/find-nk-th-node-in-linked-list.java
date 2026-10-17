

/*
class Node
{
    int data;
    Node next;
    
    Node(int key)
    {
        data = key;
        next = null;
    }
}
*/

class GfG
{
    public static int nknode(Node head, int k)
    {
      Node temp=head;
      int count=0;
      while(temp!=null)
      {
          count++;
          temp=temp.next;
      }
      if(count%k!=0)
      {
          count=count/k;
          count +=1;
      }
      else
      count=count/k;
      int len=1;
      Node temp1=head;
      while(len<count)
      {
          temp1=temp1.next;
          len++;
      }
      
      return temp1.data;
      
    }
}