

//User function Template for Java

class Solution
{
    
    static int majorityElement(int a[], int size)
    {
        HashMap<Integer,Integer> map=new HashMap<>();
        int value=-1;
        
        for(int i=0;i<size;i++)
        {
            if(map.containsKey(a[i]))
            {
                map.put(a[i],map.get(a[i])+1);
            }
            else
            {
                map.put(a[i],1);
            }
        }
        for(int key :map.keySet())
        {
            if(map.get(key)>size/2)
            {
             value=key;
            }
        }
        return value;
        
    }
}