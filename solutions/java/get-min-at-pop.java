

//User function Template for Java


class GetMin
{
    //Function to push all the elements into the stack.
    static int min;
    public static Stack<Integer> _push(int arr[],int n)
    {
     Stack<Integer> s = new Stack<>();
        s.add(arr[0]);
        min = arr[0];
        for(int i=1;i<n;i++){
            if(arr[i]<=min){
                s.push(2*arr[i] - min);
                min = arr[i];
            }else{
                s.push(arr[i]);
            }
        }
        return s;
    }
    
    //Function to print minimum value in stack each time while popping.
    static void _getMinAtPop(Stack<Integer>s)
    {
        // your code here
        while(s.isEmpty() == false ){
            System.out.print(min+" ");
            int t = s.peek();
            if(t<=min){
                min = (2*min) - t;
            }
            s.pop();
        }
    }
}