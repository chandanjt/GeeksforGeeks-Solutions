

// User function Template for Java

/* A Binary Tree node

class Node {
    int data;
    Node left, right;
   Node(int item)    {
        data = item;
        left = right = null;
    }
} */
class Solution {
    // Function to return a list containing the inorder traversal of the tree.
    void inorder(Node root,ArrayList<Integer>list)
    {
        if(root==null)
        return;
        inorder(root.left,list);
        list.add(root.data);
        inorder(root.right,list);
    }
    ArrayList<Integer> inOrder(Node root) {
         ArrayList<Integer> list=new ArrayList();
        inorder(root,list);
       return list;
    }
}