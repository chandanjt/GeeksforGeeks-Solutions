

//User function Template for Java



class BinaryTree
{

    static int sumBT(Node head){
        //Code
        //traverse(head);
        if(head==null)
        return 0;
        return head.data+sumBT(head.left)+sumBT(head.right);
    }
}