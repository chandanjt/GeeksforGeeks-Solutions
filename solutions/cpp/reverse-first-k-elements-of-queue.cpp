

// User function Template for C++

// Function to reverse first k elements of a queue.
void reverseq(queue<int>&q)
{
   if(q.empty())
   return;
   int temp=q.front();
   q.pop();
   reverseq(q);
   q.push(temp);
   
}
queue<int> modifyQueue(queue<int> q, int k) {
    // add code here.
    queue<int>ans;
    for(int i=0;i<k;i++)
    {
        ans.push(q.front());
        q.pop();
    }
    reverseq(ans);
    while(!q.empty())
    {
        ans.push(q.front());
        q.pop();
    }
    return ans;
}