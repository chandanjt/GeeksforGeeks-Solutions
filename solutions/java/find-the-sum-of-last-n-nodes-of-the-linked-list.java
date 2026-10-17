

/*
Node class is as follows:

class Node {
    int data;
    Node next;
    
    public Node (int data){
        this.data = data;
        this.next = null;
    }
}
*/

class Solution {
    
    //Return the sum of last k nodes
    public int sum(Node head, int k){
      int count=0,sum=0;
      Node temp1=head;
      while(temp1!=null)
      {
          count++;
          temp1=temp1.next;
      }
      Node temp=head;
      for(int i=1;i<=count-k;i++)
      {
          temp=temp.next;
      }
      while(temp!=null)
      {
          sum=sum+temp.data;
          temp=temp.next;
      }
      return sum;
    }
}