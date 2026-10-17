

/* Link list Node 
struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};
*/

/*You are required to complete below method*/
Node* deleteNode(Node *head,int x)
{
    //Your code here
    	if(x==1)
		{
		    head=head->next;
		    return head;
		}
	int i=1;
	Node * temp=head;
	while(i<x-1)
	{
	    temp=temp->next;
	    i++;
	}
	if(temp)
	{
	    Node*temp1=temp->next;
	    temp->next=temp->next->next;
	    free(temp1);
	}
	return head;
}