

/*
class Node {
    int data;
    Node next;
    
    public Node(int data){
        this.data = data;
        this.next = null;
    }
}*/

class Solution {
    
    //Function to check whether two linked lists are identical or not.
    public boolean isIdentical (Node head1, Node head2){
        Node temp1=head1;
        Node temp2=head2;
         int len1=0,len2=0,count=0;
        while(temp1!=null)
        {
            len1++;
            temp1=temp1.next;
        }
        while(temp2!=null)
        {
            len2++;
            temp2=temp2.next;
        }
        Node temp3=head1;
        Node temp4=head2;
        if(len1==len2)
        {
            while(temp4!=null)
            {
                if(temp3.data==temp4.data)
                count++;
                else
                {
                    break;
                }
                temp3=temp3.next;
                temp4=temp4.next;
                
            }
        }
        else
            return false;
            
        if(len1==count)
        return true;
        
        return false;
    }
}