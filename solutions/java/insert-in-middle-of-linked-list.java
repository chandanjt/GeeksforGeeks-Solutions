

/*
Structure of node class is:
class Node {
    int data;
    Node next;
    
    public Node(int data){
        this.data = data;
        this.next = null;
    }
}
*/
class Solution {
    
    public Node insertInMid(Node head, int data){
        Node newnode=new Node(data);
        Node temp=head;
        int count=0,mid=0;
        while(temp!=null)
        {
            count++;
            temp=temp.next;
        }
        if(count%2!=0)
        count=count+1;
        mid=count/2;
         Node temp1=head;
        for(int i=1;i<mid;i++)
        {
            temp1=temp1.next;
        }
        newnode.next=temp1.next;
        temp1.next=newnode;
        
        return newnode;
    }
}