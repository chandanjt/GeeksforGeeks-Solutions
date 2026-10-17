

/* Node of a linked list
 class Node {
   int data;
    Node next;
    Node(int d)  { data = d;  next = null; }
}
*/

class Solution
{
    int getMiddle(Node head)
    {
         Node temp=head;
         int count=0;
         while(temp!=null)
         {
             count++;
             temp=temp.next;
         }
         if(count%2!=0)
         {count +=1;
         count=count/2;}
         else
         {
             count=count/2;
             count +=1;
         }
         Node temp2=head;
         for(int i=1;i<count;i++)
         {
            temp2=temp2.next; 
         }
         return temp2.data;
    }
}