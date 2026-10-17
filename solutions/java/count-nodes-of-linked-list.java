/*Complete the function below*/
/*
class Node{
    int data;
    Node next;
    Node(int a){  data = a; next = null; }
}*/

class Solution
{
    //Function to count nodes of a linked list.
   //static int count =0;
    
    public static int getCount(Node head)
    {
       int count=0;
       if(head==null)
       {
           return 0;
       }
       Node temp=head;
       while(temp!=null)
       {
           count++;
           temp=temp.next;
       }
       return count;
   /* if(head==null)
       return count;
       else
       {
       count++;
       return getCount(head.next);
       }*/
       
       
}
}