

class GfG
{
    //Function to locate the occurrence of the string x in the string s.
    int strstr(String s, String x)
    {
       int lens=s.length();
       int lenx =x.length();
       int temp=0;
       if(s.contains(x))
               {
           for(int j=0;j<lens;j++)
           {
               temp=j;
               for(int i=0;i<lenx;i++)
               {
                   if(s.charAt(j)!=x.charAt(i))
                break;
               if(s.charAt(j)==x.charAt(i))
               {
               j++;
               
                   if(i==lenx-1)
                   return temp;
               
               } 
               
               }
               
               j=temp;
           }
               }  
       return -1;
    }
}