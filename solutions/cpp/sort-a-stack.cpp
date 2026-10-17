

/*The structure of the class is
class SortedStack{
public:
	stack<int> s;
	void sort();
};
*/

/* The below method sorts the stack s 
you are required to complete the below method */
void insert(stack<int>&s,int x){

    if(s.empty()){
        s.push(x);
        return; 
    }  

    int a = s.top(); 
    if(a>x){ 
        s.pop(); 
        insert(s,x); 
        s.push(a); 
    } 

    else{
        s.push(x); 
    }
    
}
void SortedStack :: sort()
{
    if(s.empty())
    return;
   int x=s.top();
   s.pop();
   sort();
   insert(s,x);
}