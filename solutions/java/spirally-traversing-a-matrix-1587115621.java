

class Solution
{
    //Function to return a list of integers denoting spiral traversal of matrix.
    static ArrayList<Integer> spirallyTraverse(int matrix[][], int r, int c)
    {
        // code here 
        ArrayList<Integer>list=new ArrayList();
        int rowstart=0;
        int colstart=0;
        int rowend=r-1;
        int colend=c-1;
        while(rowstart<=rowend && colstart<=colend)
        {
            for(int i=colstart;i<=colend;i++)
            {
                list.add(matrix[rowstart][i]);
            }
            rowstart++;
            for(int i=rowstart;i<=rowend;i++)
            {
                list.add(matrix[i][colend]);
            }
            colend--;
            if(rowstart<=rowend)
            {
            for(int i=colend;i>=colstart;i--)
            {
                list.add(matrix[rowend][i]);
            }
            rowend--;
            }
            if(colstart<=colend)
            {
            for(int i=rowend;i>=rowstart;i--)
            {
                list.add(matrix[i][colstart]);
            }
            colstart++;
            
            }  
            
        }
        return list;
    }
}