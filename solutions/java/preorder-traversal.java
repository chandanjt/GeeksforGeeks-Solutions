

//User function Template for Java



// class Node{
//     int data;
//     Node left,right;
//     Node(int d){
//         data=d;
//         left=right=null;
//     }
// }

class BinaryTree
{
   public static void preorder(Node root,ArrayList<Integer>list)
    {
        if(root==null)
        return;
        list.add(root.data);
        preorder(root.left,list);
        preorder(root.right,list);
    }
    //Function to return a list containing the preorder traversal of the tree.
    static ArrayList<Integer> preorder(Node root)
    {
        // Code here
        ArrayList<Integer> list=new ArrayList();
        preorder(root,list);
        return list;
    }

}