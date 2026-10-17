

/*node class of the linked list
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
   
    public static int getNth(Node node, int ind)
    {
      int count =1;
      Node temp=node;
      while(count!=ind)
      {
          temp=temp.next;
          count++;
      }
      return temp.data;
    }
}