

/* Function to print corner node at each level */

/*
Structure of a node is as following
struct Node
{
     int data;
     struct Node* left;
     struct Node* right;
};
*/
void printCorner(Node *root)
{

// Your code goes here
if (!root) return;

    // Create a queue for level order traversal
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int n = q.size();

        for (int i = 0; i < n; i++) {
            Node* temp = q.front();
            q.pop();

            // If it's the first or last node of this level, print it
            if (i == 0 || i == n - 1)
                std::cout << temp->data << " ";

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }

}