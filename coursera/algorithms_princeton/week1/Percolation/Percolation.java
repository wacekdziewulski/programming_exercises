//import edu.princeton.cs.algs4.StdRandom;
//import edu.princeton.cs.algs4.StdStats;
import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
   public enum NodeState {
        NODE_CLOSED,
        NODE_OPEN
   }

   public Percolation(int n) { // create n-by-n grid, with all sites blocked
        size = n;
        nodes = new byte[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                nodes[i][j] = NodeState.NODE_CLOSED;
            }
        }
   }

   public void open(int row, int col) { // open site (row, col) if it is not open already
        // sanity check
        if (row >= size || col >= size || row < 0 || col < 0) {
            throw ArrayIndexOutOfBoundsException("Invalid row or column");
        }
        nodes[i][j] = NodeState.NODE_OPEN;

        if ((i > 0) && nodes[i-1][j] == NodeState.NODE_OPEN) {
            quickUnion.union(convertXYtoFlat(i-1, j), convertXYtoFlat(i, j));
        }
        if ((i < size-1) && nodes[i+1][j] == NodeState.NODE_OPEN) {
           quickUnion.union(convertXYtoFlat(i+1, j), convertXYtoFlat(i, j));
        }
        if ((j > 0) && nodes[i][j-1] == NodeState.NODE_OPEN) {
           quickUnion.union(convertXYtoFlat(i, j-1), convertXYtoFlat(i, j));
        }
        if ((j < size-1) && nodes[i][j+1] == NodeState.NODE_OPEN) {
           quickUnion.union(convertXYtoFlat(i, j+1), convertXYtoFlat(i, j));
        }
   }

   static int convertXYtoFlat(int row, int col) {
       return row * size + col;
   }

   public boolean isOpen(int row, int col) { // is site (row, col) open?

   }
   public boolean isFull(int row, int col) { // is site (row, col) full?

   }
   public int numberOfOpenSites() { // number of open sites

   }
   public boolean percolates() { // does the system percolate?

   }

   public static void main(String[] args) {

   }
   
   NodeState[][] nodes;
   int size;
   WeightedQuickUnionUF quickUnion;
}
