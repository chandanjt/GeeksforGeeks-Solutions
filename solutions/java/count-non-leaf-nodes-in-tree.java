

//User function Template for Java

/*class Node
{
    int data;
    Node left,right;
    Node(int d){
        data=d;
        left=right=null;
    }
}*/

//function should return the count of total number of non leaf nodes in the tree.
class Solution
{
 int count =0;
 void postorder(Node root)
 {
     if(root==null)
        return ;
        if(root.left!=null || root.right!=null)
        count++;
        postorder(root.left);
        postorder(root.right);
        
 }
	int countNonLeafNodes(Node root) {
	    postorder(root);
	    return count;
	   
	}
}