/*
The structure of the class is as follows
class _stack{
stack<int> s;
int minEle;
public :
    int getMin();
    int pop();
    void push(int);
};
*/

class Solution{
    int minEle;
    stack<int> s;
    stack<int>s2;
    public:
    
       /*returns min element from stack*/
       int getMin(){
           if(s2.empty())
           return -1;
          return s2.top();
       }
       
       /*returns poped element from stack*/
       int pop(){
           if(s.empty())
           return -1;
           if(s.top()==s2.top())
           {
               s2.pop();
               
           }
         int x=s.top();
         s.pop();
         return x;
          
       }
       
       /*push element x into the stack*/
       void push(int x){
           
          if(s2.empty()||x<=s2.top())
          {
          s2.push(x);
          
          }
         s.push(x);
         
       }
};