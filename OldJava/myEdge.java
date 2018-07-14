//package edu.princeton.cs.algs4;

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

import java.util.*;


 class MyEdge implements Comparable<MyEdge>{
    private final int v; // NOTE: ensure v < w.
    private final int w;
    private long weight;

    public int minv() { return v; }
    public int maxv() { return w; }
    public long weight() { return weight; }
    public void changeWeight( long weight ) { this.weight = weight; }

    MyEdge ( int v, int w, long weight ) {
  		if (v < 0) throw new IndexOutOfBoundsException("Vertex name must be a nonnegative integer");
        if (w < 0) throw new IndexOutOfBoundsException("Vertex name must be a nonnegative integer");
       this.v = v < w ? v : w;
       this.w = v < w ? w : v;
       this.weight = weight;
    }

    public String toString() {
       return String.format("%d-%d %d", v, w, weight);
    }

public int either() {
        return v;
    }

    public int other(int vertex) {
        if      (vertex == v) return w;
        else if (vertex == w) return v;
        else throw new IllegalArgumentException("Illegal endpoint");
    }

    public int compareTo(MyEdge that) {
   	 if      (this.weight() < that.weight()) return -1;
        else if (this.weight() > that.weight()) return +1;
        else                                    return  0;
    }

      public static void main(String[] args) {
	        MyEdge e = new MyEdge(12, 32, 23);
	      //  MyEdge e = new MyEdge(1, 31, 25);
	        StdOut.println(e);
    }

}
