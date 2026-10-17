

/*class Node
    {
        int data;
        Node next;
        Node(int d) {data = d; next = null; }
    }*/

// sortedInsert method should return the head of the modified linked list.
class Solution {
    Node sortedInsert(Node start, int key) {
        // Add your code here.
         Node p = start;
        Node temp = new Node(key);
        
        //for first Node
        if(key<p.data){
            temp.next = p;
            start = temp;
            return start;
        }
        //rest of all nodes.
        p = p.next;
        Node prev = start;
        while(p!=null){
            if(key<p.data){
                prev.next = temp;
                temp.next = p;
                return start;
            }
            prev = p;
            p = p.next;
        }
        prev.next = temp;
        return start;
    }
}