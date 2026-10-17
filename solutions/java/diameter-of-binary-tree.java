

// User function Template for Java

/*class Node {
    int data;
    Node left;
    Node right;
    Node(int data) {
        this.data = data;
        left = null;
        right = null;
    }
}*/

class Solution {
    // Function to return the diameter of a Binary Tree.
    int height(Node root)
    {
        if(root==null)
        {
            return 0;
        }
        else
        return Math.max(height(root.left),height(root.right))+1;
    }
    int diameter(Node root) {
        // Your code here
        if(root==null)
        return 0;
        int d1=1+height(root.left)+height(root.right);
        int d2=diameter(root.left);
        int d3=diameter(root.right);
        int max1=Math.max(d1,d2);
        return Math.max(max1,d3);
    }
}