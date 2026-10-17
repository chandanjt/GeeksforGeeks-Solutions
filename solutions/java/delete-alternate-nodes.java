

/*
class Node {
    int data;
    Node next;
    
    public Node(int data){
        this.data = data;
    }
}
*/
class Solution {
    
    public void deleteAlternate (Node head){
        Node temp1=head;
        
        Node temp2=head.next;
        if(temp2==null)
       { temp1.next=null;
       }
       else
       {
        temp2=temp2.next;
        while(temp2!=null)
        {
            
            temp1.next=temp2;
            
            temp2=temp2.next;
            temp1=temp1.next;
            if(temp2!=null)
            temp2=temp2.next;
            
        }}
        temp1.next=null;
    }
}