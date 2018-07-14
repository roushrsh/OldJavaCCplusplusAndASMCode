import edu.princeton.cs.algs4.In;
import java.util.*;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.UF;



public class MyKrustkal {
    private static final double FLOATING_POINT_EPSILON = 1E-12;

    private long weight;                        // weight of MST
    private Queue<MyEdge> mst = new Queue<MyEdge>();  // edges in MST

    /**
     * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
     * @param G the edge-weighted graph
     */

///////////////////////////

     public static long include( MyEdgeWeightedGraph G ) {
	       // FOR YOU TO FILL IN
	       return 1;
	    }

	    public static long exclude( MyEdgeWeightedGraph G ) {
	       // FOR YOU TO FILL IN
	       return 1;
   }


///////////////////////////
    public MyKrustkal(MyEdgeWeightedGraph G) {
        // more efficient to build heap by passing array of edges
        MinPQ<MyEdge> pq = new MinPQ<MyEdge>();
        for (MyEdge e : G.edges()) {
            pq.insert(e);
        }

        // run greedy algorithm
        UF uf = new UF(G.V());
        while (!pq.isEmpty() && mst.size() < G.V() - 1) {
            MyEdge e = pq.delMin();
            int v = e.either();
            int w = e.other(v);
            if (!uf.connected(v, w)) { // v-w does not create a cycle
                uf.union(v, w);  // merge v and w components
                mst.enqueue(e);  // add edge e to mst
                weight += e.weight();
            }
        }

        // check optimality conditions
        assert check(G);
    }

    /**
     * Returns the edges in a minimum spanning tree (or forest).
     * @return the edges in a minimum spanning tree (or forest) as
     *    an iterable of edges
     */
    public Iterable<MyEdge> edges() {
        return mst;
    }

    /**
     * Returns the sum of the edge weights in a minimum spanning tree (or forest).
     * @return the sum of the edge weights in a minimum spanning tree (or forest)
     */
    public long weight() {
        return weight;
    }

    // check optimality conditions (takes time proportional to E V lg* V)
    private boolean check(MyEdgeWeightedGraph G) {

        // check total weight
        double total = 0.0;
        for (MyEdge e : edges()) {
            total += e.weight();
        }
        if (Math.abs(total - weight()) > FLOATING_POINT_EPSILON) {
            System.err.printf("Weight of edges does not equal weight(): %f vs. %f\n", total, weight());
            return false;
        }

        // check that it is acyclic
        UF uf = new UF(G.V());
        for (MyEdge e : edges()) {
            int v = e.either(), w = e.other(v);
            if (uf.connected(v, w)) {
                System.err.println("Not a forest");
                return false;
            }
            uf.union(v, w);
        }

        // check that it is a spanning forest
        for (MyEdge e : G.edges()) {
            int v = e.either(), w = e.other(v);
            if (!uf.connected(v, w)) {
                System.err.println("Not a spanning forest");
                return false;
            }
        }

        // check that it is a minimal spanning forest (cut optimality conditions)
        for (MyEdge e : edges()) {

            // all edges in MST except e
            uf = new UF(G.V());
            for (MyEdge f : mst) {
                int x = f.either(), y = f.other(x);
                if (f != e) uf.union(x, y);
            }

            // check that e is min weight edge in crossing cut
            for (MyEdge f : G.edges()) {
                int x = f.either(), y = f.other(x);
                if (!uf.connected(x, y)) {
                    if (f.weight() < e.weight()) {
                        System.err.println("Edge " + f + " violates cut optimality conditions");
                        return false;
                    }
                }
            }

        }

        return true;
    }


    /**
     * Unit tests the <tt>KruskalMST</tt> data type.
     */
    public static void main(String[] args) {
        In in = new In(args[0]);
        MyEdgeWeightedGraph G = new MyEdgeWeightedGraph(in);
        MyKrustkal mst = new MyKrustkal(G);
        for (MyEdge e : mst.edges()) {
            StdOut.println(e);
        }
        StdOut.printf("%.5f\n", mst.weight());
    }

}
