/*
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
}*head;
*/


class Solution
{
    public:
    //Function to delete a node without any reference to head pointer.
    void deleteNode(Node *del_node)
    {
       // Your code here
       Node* temp=del_node;
       if(temp==NULL)
       return ;
       temp->data=del_node->next->data;
       //temp=temp->next;
       del_node->next=del_node->next->next;
    }

};