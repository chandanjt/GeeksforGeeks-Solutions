

//User function Template for Java

class Solution{
    public static ArrayList<Integer> common_element(int v1[], int v2[])
    {
        //Your code here
        HashMap<Integer,Integer>hm=new HashMap<>();
        ArrayList<Integer>res=new ArrayList<>();
        for(int i=0;i<v1.length;i++){
            int c=v1[i];
            if(hm.containsKey(c)){
                hm.put(c,hm.get(c)+1);
                
            }else{
                hm.put(c,1);
            }
        }
        
        Arrays.sort(v2);
        for(int num: v2) {
            if(hm.containsKey(num) && hm.get(num) != 0) {
                res.add(num);  
                hm.put(num, hm.get(num) - 1);
            }
        }
        return res;
    }
}