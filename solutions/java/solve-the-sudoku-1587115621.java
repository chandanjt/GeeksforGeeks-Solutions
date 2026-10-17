



//User function Template for Java

class Solution
{
    //Function to find a solved Sudoku.
    public static boolean isSafe(int board[][],int row,int col,int number)
    {
        for(int i=0;i<board.length;i++)
        {
            if(board[i][col]==number)
            {
                return false;
            }
        }
        for(int j=0;j<board.length;j++)
        {
            if(board[row][j]==number)
            {
                return false;
            }
        }
        int sr=3*(row/3);
        int sc=3*(col/3);
        for(int i=sr;i<sr+3;i++)
        {
            for(int j=sc;j<sc+3;j++)
            {
                if(board[i][j]==number)
            {
                return false;
            }
            }
        }
        return true;
    }
    public static boolean helper(int[][] board,int row ,int col)
    {
        if(row==board.length)
        {
            return true;
        }
        int nrow=0;
        int ncol=0;
        if(col==board.length-1)
        {
            nrow=row+1;
            ncol=0;
        }
        else
        {
            nrow=row;
            ncol=col+1;
        }
        if(board[row][col]!=0)
        {
            if(helper(board,nrow,ncol))
            {
                return true;
            }
        }
            else
            {
                for(int i=1;i<=9;i++)
                {
                    if(isSafe(board,row,col,i))
                    {
                        board[row][col]=i;
                        if(helper(board,nrow,ncol))
                        return true;
                        else
                        board[row][col]=0;
                    }
                }
            }
        return false;
    }
    static boolean SolveSudoku(int grid[][])
    {
        if(helper(grid,0,0))
        return true;
        return false;
    }
    
    //Function to print grids of the Sudoku.
    static void printGrid (int grid[][])
    {
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            System.out.print(grid[i][j]+" ");
        }
       // System.out.print("\n");
    }
}