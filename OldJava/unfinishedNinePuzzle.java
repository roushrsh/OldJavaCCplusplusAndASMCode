/////Soroush Hajizadeh
//// CSC 225
//// BFS attempt on NinePuzzle to determine best route
//unfinished Code
//// only functions on basic cases such as 123 456 708, 123 456 078, etc
////otherwise ends up looping, fails to remember as nodes keep references, they do not do deep copy to remember
//It can tell if a puzzle is solvable or not (when inputed) through the number of inputs



import java.util.Scanner;
import java.io.File;
import java.util.*;

public class NinePuzzle{

	public static class Node{ 			///set uP NODE
		int index;					//index of Puzzle
		int[][] attachedArray;		///WHERE THE ATTACHED ARRAY SHOULD GO INTO THE NODE
		int visited;				//has it been visited?
		int up;					//gone up yet?
		int down;
		int right;
		int left;
		int[][] fromLeft;		//state to jump to from location if rest occupied
		int[][] fromRight;
		int[][] fromUp;
		int[][] fromDown;
		int iPrev;				//where it just came from so it doesn't go back and forth repeatedly


		public Node() {
			index = 0;
			attachedArray = null;
			visited = 0;
			right = 0;
			left =0;
			up = 0;
			down = 0;
			int[][] fromLeft = null;
			int[][] fromRight = null;
			int[][] fromUp = null;
			int[][] fromDown = null;
			int iPrev = 0;
		}

		public Node (int index, int[][] attachArray, int visited, int right, int left, int up, int down, int[][] fromDown, int[][] fromLeft, int[][] fromUp, int[][] fromRight, int iPrev ){
			this.index = index;
			this.attachedArray = attachedArray;
			this.visited = visited;
			this.up=up;
			this.down=down;
			this.left=left;
			this.right=right;
			this.fromDown = fromDown;
			this.fromUp = fromUp;
			this.fromLeft = fromLeft;
			this.fromRight = fromRight;
			this.iPrev = iPrev;   ///1 = from right, 2 = from left, 3 = from up, 4 = from down
		}


	}


public static int BUILDGRAPH(int[][] B){		//graph generator


	Node [] test = new Node[362880];
		for (int i=0; i<362880;i++){
			int[][] C = getBoardFromIndex(i);												///THIS IS WHERE THE PROBLEM IS OCCURING.
			test[i] = new Node(getIndexFromBoard(getBoardFromIndex(i)),C,0,0,0,0,0,C,C,C,C,0);		//WHEN C IS PASSED IN HERE, IT IS A REFERENCE AND LOST AS NULL! :(
		}

/*															//Some of my attempts at fixing this.
	int[][] matrix = new int[3][3];
	for(int l = 0; l<3; l++){
		for(int m = 0; m<3; m++){
			matrix[l][m] = Integer.parseInt( F[l+m].charAt(l+m) ) ;
		}
	}

	String [] F = new String [362880];
	for (int i = 0; i<362880; i++){
		F[i] = ( Integer.toString(getBoardFromIndex(i)[0][0]) + Integer.toString(getBoardFromIndex(i)[0][1]) + Integer.toString(getBoardFromIndex(i)[0][2]) + Integer.toString(getBoardFromIndex(i)[1][0]) + Integer.toString(getBoardFromIndex(i)[1][1]) + Integer.toString(getBoardFromIndex(i)[1][2]) + Integer.toString(getBoardFromIndex(i)[2][0]) + Integer.toString(getBoardFromIndex(i)[2][1]) + Integer.toString(getBoardFromIndex(i)[2][2]));
	}
*/

	MrRECURSION(B, test, null);			///runs the recursion
	return 1;
}



public static int MrRECURSION(int[][] M, Node [] test, int [][] before){
	int [][] B = M;
	int[][] Z = new int [3][3];
	Z[0][0] = 1; Z[0][1] = 2; Z[0][2] = 3; Z[1][0] = 4; Z[1][1] = 5; Z[1][2] = 6;Z[2][0] = 7; Z [2][1] = 8; Z[2][2] = 0;
	test[getIndexFromBoard(B)].attachedArray = B;
	//int [][] before = prev;

/*	if (B == Z){
		System.out.println("DONE");
		return 1;
	}*/

	printBoard(B);
	if (!( (B[0][0]== Z[0][0]) &&(B[0][1]== Z[0][1])&&(B[0][2]== Z[0][2])  &&(B[1][0]== Z[1][0])  &&(B[1][1]== Z[1][1])  &&(B[1][2]== Z[1][2])  &&(B[2][0]== Z[2][0])  &&(B[2][1]== Z[2][1])  &&(B[2][2]== Z[2][2]) ))   {
//checks to make sure it isn't solved already AGAIN
															/////////		TOP LEFT CORNER	 //////
		if (B[0][0] == 0){ ///down, right
			test[getIndexFromBoard(B)].left = 1;									//CHECK THESE AS 1, means that top left corner can never go left or up
			test[getIndexFromBoard(B)].up = 1;

				if ( (test[getIndexFromBoard(B)].right == 0) && (test[getIndexFromBoard(B)].iPrev != 2) ) {			//ASSUMING IT HASN'T GONE RIGHT YET
					test[getIndexFromBoard(B)].right =1;															//it shall go right, then make sure it cannot again
					before = B;
					B[0][0] = B[0][1];															//doing the switch
					B[0][1] = 0;
////////////
					test[getIndexFromBoard(B)].fromRight = before;											//states the previous node for convenience
					test[getIndexFromBoard(B)].iPrev = 1;													//this guarantees once it goes right, at the next step it cannot go left/back

///////////
					MrRECURSION(B, test, before);																//Same thing for down possiblity
				}else if ( (test[getIndexFromBoard(B)].down == 0) && (test[getIndexFromBoard(B)].iPrev != 3) ){
					test[getIndexFromBoard(B)].down = 1;
					before = B;
					B[0][0] = B[1][0];
					B[1][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromDown = before;
					test[getIndexFromBoard(B)].iPrev = 4;

///////////

					MrRECURSION(B, test, before);
				}else{  //assuming all taken
////

					if (test[getIndexFromBoard(B)].fromRight != null){									//if fromRight is not null, then we can backtrack there
						MrRECURSION(test[getIndexFromBoard(B)].fromRight, test, before);
					}else if(test[getIndexFromBoard(B)].fromDown != null){								//else we try the other, one or the other should be available
						MrRECURSION(test[getIndexFromBoard(B)].fromDown, test, before);
					}
////////

				//	MrRECURSION(before, test, before);
				}
															/////////		TOP MIDDLE		//////

		}else if (B[0][1] == 0) { //left, down, right
			test[getIndexFromBoard(B)].up = 1;

				if ( (test[getIndexFromBoard(B)].right == 0) && (test[getIndexFromBoard(B)].iPrev != 2) ){
					test[getIndexFromBoard(B)].right =1;
					before = B;
					B[0][1] = B[0][2];
					B[0][2] = 0;

////////////
					test[getIndexFromBoard(B)].fromRight = before;
					test[getIndexFromBoard(B)].iPrev = 1;
///////////

					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].down == 0) && (test[getIndexFromBoard(B)].iPrev != 3) ){
					test[getIndexFromBoard(B)].down = 1;
					before = B;
					B[0][1] = B[1][1];
					B[1][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromDown = before;
					test[getIndexFromBoard(B)].iPrev = 4;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].left== 0)&& (test[getIndexFromBoard(B)].iPrev != 1) ){
					test[getIndexFromBoard(B)].left = 1;
					before = B;
					B[0][1] = B[0][0];
					B[0][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromLeft = before;
					test[getIndexFromBoard(B)].iPrev = 2;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					if (test[getIndexFromBoard(B)].fromRight != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromRight, test, before);
					}else if(test[getIndexFromBoard(B)].fromDown != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromDown, test, before);
					}else if(test[getIndexFromBoard(B)].fromLeft != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromLeft, test, before);
					}
			//		MrRECURSION(before, test, before);
				}
															/////////		TOP RIGHT 		//////

		}else if (B[0][2] == 0) { //left, down
			test[getIndexFromBoard(B)].right = 1;
			test[getIndexFromBoard(B)].up = 1;

				if ( (test[getIndexFromBoard(B)].down == 0) && (test[getIndexFromBoard(B)].iPrev != 3) ){
					test[getIndexFromBoard(B)].down = 1;
					before = B;
					B[0][2] = B[1][2];
					B[1][2] = 0;
//////////
					test[getIndexFromBoard(B)].fromDown = before;
					test[getIndexFromBoard(B)].iPrev = 4;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].left== 0) && (test[getIndexFromBoard(B)].iPrev != 1) ){
					test[getIndexFromBoard(B)].left = 1;
					before = B;
					B[0][2] = B[0][1];
					B[0][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromLeft = before;
					test[getIndexFromBoard(B)].iPrev = 2;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					if(test[getIndexFromBoard(B)].fromDown != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromDown, test, before);
					}else if(test[getIndexFromBoard(B)].fromLeft != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromLeft, test, before);
					}
				//	MrRECURSION(before, test, before);
				}

															/////////		MIDDLE LEFT 		//////

		}else if (B[1][0] == 0) {//up, right, down
			test[getIndexFromBoard(B)].left = 1;

				if ((test[getIndexFromBoard(B)].right == 0)&& (test[getIndexFromBoard(B)].iPrev != 2) ){
					test[getIndexFromBoard(B)].right =1;
					before = B;
					B[1][0] = B[1][1];
					B[1][1] = 0;

////////////
					test[getIndexFromBoard(B)].fromRight = before;
					test[getIndexFromBoard(B)].iPrev = 1;
///////////

					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].down == 0)&& (test[getIndexFromBoard(B)].iPrev != 3) ){
					test[getIndexFromBoard(B)].down = 1;
					before = B;
					B[1][0] = B[2][0];
					B[2][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromDown = before;
					test[getIndexFromBoard(B)].iPrev = 4;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].up == 0)&& (test[getIndexFromBoard(B)].iPrev != 4) ){
					test[getIndexFromBoard(B)].up = 1;
					before = B;
					B[1][0] = B[0][0];
					B[0][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromUp = before;
					test[getIndexFromBoard(B)].iPrev = 3;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					if (test[getIndexFromBoard(B)].fromRight != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromRight, test, before);
					}else if(test[getIndexFromBoard(B)].fromDown != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromDown, test, before);
					}else if(test[getIndexFromBoard(B)].fromUp != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromUp, test, before);
					}
					//MrRECURSION(before, test, before);
				}
															/////////		MIDDLE		//////

		}else if (B[1][1] == 0) { //up, down, left, right
				if ((test[getIndexFromBoard(B)].right == 0)&& (test[getIndexFromBoard(B)].iPrev != 2) ){
					test[getIndexFromBoard(B)].right =1;
					before = B;
					B[1][1] = B[1][2];
					B[1][2] = 0;
////////////
					test[getIndexFromBoard(B)].fromRight = before;
					test[getIndexFromBoard(B)].iPrev = 1;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].down == 0)&& (test[getIndexFromBoard(B)].iPrev != 3) ){
					test[getIndexFromBoard(B)].down = 1;
					before = B;
					B[1][1] = B[2][1];
					B[2][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromDown = before;
					test[getIndexFromBoard(B)].iPrev = 4;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].up == 0)&& (test[getIndexFromBoard(B)].iPrev != 4) ){
					test[getIndexFromBoard(B)].up = 1;
					before = B;
					B[1][1] = B[0][1];
					B[0][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromUp = before;
					test[getIndexFromBoard(B)].iPrev = 3;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].left == 0)&& (test[getIndexFromBoard(B)].iPrev != 1) ){
					test[getIndexFromBoard(B)].left = 1;
					before = B;
					B[1][1] = B[1][0];
					B[1][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromLeft = before;
					test[getIndexFromBoard(B)].iPrev = 2;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					if (test[getIndexFromBoard(B)].fromRight != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromRight, test, before);
					}else if(test[getIndexFromBoard(B)].fromDown != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromDown, test, before);
					}else if(test[getIndexFromBoard(B)].fromLeft != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromLeft, test, before);
					}else if(test[getIndexFromBoard(B)].fromUp != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromUp, test, before);
					}
					//MrRECURSION(before, test, before);
				}

															/////////		MIDDLE RIGHT 		//////

		}else if (B[1][2] == 0) { // up, left, down
			test[getIndexFromBoard(B)].right = 1;

				if ((test[getIndexFromBoard(B)].down == 0)&& (test[getIndexFromBoard(B)].iPrev != 3) ){
					test[getIndexFromBoard(B)].down = 1;
					before = B;
					B[1][2] = B[2][2];
					B[2][2] = 0;
//////////
					test[getIndexFromBoard(B)].fromDown = before;
					test[getIndexFromBoard(B)].iPrev = 4;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].up == 0)&& (test[getIndexFromBoard(B)].iPrev != 4) ){
					test[getIndexFromBoard(B)].up = 1;
					before = B;
					///////////////////////////////////////////////////////////////////////////////////////
					B[1][2] = B[0][2];
					B[0][2] = 0;
//////////
					test[getIndexFromBoard(B)].fromUp = before;
					test[getIndexFromBoard(B)].iPrev = 3;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].left == 0)&& (test[getIndexFromBoard(B)].iPrev != 1) ){
					test[getIndexFromBoard(B)].left = 1;
					before = B;
					B[1][2] = B[1][1];
					B[1][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromLeft = before;
					test[getIndexFromBoard(B)].iPrev = 2;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken

			 		if(test[getIndexFromBoard(B)].fromLeft != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromLeft, test, before);
					}else if(test[getIndexFromBoard(B)].fromDown != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromDown, test, before);
					}else if(test[getIndexFromBoard(B)].fromUp != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromUp, test, before);
					}
					//MrRECURSION(before, test, before);
				}
															/////////		BOTTOM LEFT 		//////

		}else if (B[2][0] == 0) {// up, right
			test[getIndexFromBoard(B)].left = 1;
			test[getIndexFromBoard(B)].down = 1;

				if ((test[getIndexFromBoard(B)].right == 0)&& (test[getIndexFromBoard(B)].iPrev != 2) ){
					test[getIndexFromBoard(B)].right =1;
					before = B;
					B[2][0] = B[2][1];
					B[2][1] = 0;
////////////
					test[getIndexFromBoard(B)].fromRight = before;
					test[getIndexFromBoard(B)].iPrev = 1;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].up == 0)&& (test[getIndexFromBoard(B)].iPrev != 4) ){
					test[getIndexFromBoard(B)].up = 1;
					before = B;
					B[2][0] = B[1][0];
					B[1][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromUp = before;
					test[getIndexFromBoard(B)].iPrev = 3;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					if (test[getIndexFromBoard(B)].fromRight != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromRight, test, before);
					}else if(test[getIndexFromBoard(B)].fromUp != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromUp, test, before);
					}
					//MrRECURSION(before, test, before);
				}
															/////////		BOTTOM MIDDLE		//////

		}else if (B[2][1] == 0) {// left, up, right
			test[getIndexFromBoard(B)].down = 1;

				if ((test[getIndexFromBoard(B)].right == 0)&& (test[getIndexFromBoard(B)].iPrev != 2) ){
					test[getIndexFromBoard(B)].right =1;
					before = B;
					B[2][1] = B[2][2];
					B[2][2] = 0;

////////////
					test[getIndexFromBoard(B)].fromRight = before;
					test[getIndexFromBoard(B)].iPrev = 1;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].up == 0)&& (test[getIndexFromBoard(B)].iPrev != 4) ){
					test[getIndexFromBoard(B)].up = 1;
					before = B;
					B[2][1] = B[1][1];
					B[1][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromUp = before;
					test[getIndexFromBoard(B)].iPrev = 3;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].left == 0)&& (test[getIndexFromBoard(B)].iPrev != 1) ){
					test[getIndexFromBoard(B)].left = 1;
					before = B;
					B[2][1] = B[2][0];
					B[2][0] = 0;
//////////
					test[getIndexFromBoard(B)].fromLeft = before;
					test[getIndexFromBoard(B)].iPrev = 2;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					if (test[getIndexFromBoard(B)].fromRight != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromRight, test, before);
					}else if(test[getIndexFromBoard(B)].fromLeft != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromLeft, test, before);
					}else if(test[getIndexFromBoard(B)].fromUp != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromUp, test, before);
					}
				//	MrRECURSION(before, test, before);
				}
															/////////		BOTTOM RIGHT 		//////

		}else if (B[2][2] == 0) { //up, left
			test[getIndexFromBoard(B)].right = 1;
			test[getIndexFromBoard(B)].down = 1;

				if ((test[getIndexFromBoard(B)].up == 0)&& (test[getIndexFromBoard(B)].iPrev != 4) ){
					test[getIndexFromBoard(B)].up = 1;
					before = B;
					B[2][2] = B[1][2];
					B[1][2] = 0;
//////////
					test[getIndexFromBoard(B)].fromUp = before;
					test[getIndexFromBoard(B)].iPrev = 3;
///////////
					MrRECURSION(B, test, before);
				}else if ((test[getIndexFromBoard(B)].left == 0)&& (test[getIndexFromBoard(B)].iPrev != 1) ){
					test[getIndexFromBoard(B)].left = 1;
					before = B;
					B[2][2] = B[2][1];
					B[2][1] = 0;
//////////
					test[getIndexFromBoard(B)].fromLeft = before;
					test[getIndexFromBoard(B)].iPrev = 2;
///////////
					MrRECURSION(B, test, before);
				}else{  						//assuming all taken
					System.out.println("WHEN IS IT GETTING HERE?");
					if(test[getIndexFromBoard(B)].fromLeft != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromLeft, test, before);
					}else if(test[getIndexFromBoard(B)].fromUp != null){
						MrRECURSION(test[getIndexFromBoard(B)].fromUp, test, before);
					}
				}
		}
	}

	return 1;
}

	int NUM_BOARDS = 362880;


	public static boolean SolveNinePuzzle(int[][] B){				//calculating if solvable or not
		/* ... Your code here ... */

	//getBoardFromIndex(getIndexFromBoard(B));
	int[] z = new int [9];
	int num = 0;

	for (int a = 0; a<3; a++){
		for(int b = 0; b<3; b++){
			z[num] = B[a][b];
			num = num+1;
		}
	}


	int inversions = 0;

	for(int i = 0; i < z.length; i++){
		for(int j = 0; j<i; j++){
			if(z[i] !=0 && z [j]!=0){
				if(z[i] < z[j]){
					inversions++;
				}
			}
		}
	}


	if(inversions%2 == 1){				///if number of inversions is odd then unsolvable
		return false;
	}else{								//else it is solvable
		BUILDGRAPH(B);
		return true;
	}
}


	/*  printBoard(B)
		Print the given 9-puzzle board. The SolveNinePuzzle method above should
		use this method when printing the sequence of moves which solves the input
		board. If any other method is used (e.g. printing the board manually), the
		submission may lose marks.
	*/
	public static void printBoard(int[][] B){
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++)
				System.out.printf("%d ",B[i][j]);
			System.out.println();
		}
		System.out.println();
	}


	/* Board/Index conversion functions
	   These should be treated as black boxes (i.e. don't modify them, don't worry about
	   understanding them). The conversion scheme used here is adapted from
		 W. Myrvold and F. Ruskey, Ranking and Unranking Permutations in Linear Time,
		 Information Processing Letters, 79 (2001) 281-284.
	*/
	public static int getIndexFromBoard(int[][] B){
		int i,j,tmp,s,n;
		int[] P = new int[9];
		int[] PI = new int[9];
		for (i = 0; i < 9; i++){
			P[i] = B[i/3][i%3];
			PI[P[i]] = i;
		}
		int id = 0;
		int multiplier = 1;
		for(n = 9; n > 1; n--){
			s = P[n-1];
			P[n-1] = P[PI[n-1]];
			P[PI[n-1]] = s;

			tmp = PI[s];
			PI[s] = PI[n-1];
			PI[n-1] = tmp;
			id += multiplier*s;
			multiplier *= n;
		}
		return id;
	}

	public static int[][] getBoardFromIndex(int id){
		int[] P = new int[9];
		int i,n,tmp;
		for (i = 0; i < 9; i++)
			P[i] = i;
		for (n = 9; n > 0; n--){
			tmp = P[n-1];
			P[n-1] = P[id%n];
			P[id%n] = tmp;
			id /= n;
		}
		int[][] B = new int[3][3];
		for(i = 0; i < 9; i++)
			B[i/3][i%3] = P[i];
		return B;
	}


	public static void main(String[] args){

		/* Code to test your implementation */
		/* You may modify this, but nothing in this function will be marked */

		Scanner s;

		if (args.length > 0){
			//If a file argument was provided on the command line, read from the file
			try{
				s = new Scanner(new File(args[0]));
			} catch(java.io.FileNotFoundException e){
				System.out.printf("Unable to open %s\n",args[0]);
				return;
			}
			System.out.printf("Reading input values from %s.\n",args[0]);
		}else{
			//Otherwise, read from standard input
			s = new Scanner(System.in);
			System.out.printf("Reading input values from stdin.\n");
		}

		int graphNum = 0;
		double totalTimeSeconds = 0;

		//Read boards until EOF is encountered (or an error occurs)
		while(true){
			graphNum++;
			if(graphNum != 1 && !s.hasNextInt())
				break;
			System.out.printf("Reading board %d\n",graphNum);
			int[][] B = new int[3][3];
			int valuesRead = 0;
			for (int i = 0; i < 3 && s.hasNextInt(); i++){
				for (int j = 0; j < 3 && s.hasNextInt(); j++){
					B[i][j] = s.nextInt();
					valuesRead++;
				}
			}
			if (valuesRead < 9){
				System.out.printf("Board %d contains too few values.\n",graphNum);
				break;
			}
			System.out.printf("Attempting to solve board %d...\n",graphNum);
			long startTime = System.currentTimeMillis();
			boolean isSolvable = SolveNinePuzzle(B);
			long endTime = System.currentTimeMillis();
			totalTimeSeconds += (endTime-startTime)/1000.0;

			if (isSolvable)
				System.out.printf("Board %d: Solvable.\n",graphNum);
			else
				System.out.printf("Board %d: Not solvable.\n",graphNum);
		}
		graphNum--;
		System.out.printf("Processed %d board%s.\n Average Time (seconds): %.2f\n",graphNum,(graphNum != 1)?"s":"",(graphNum>1)?totalTimeSeconds/graphNum:0);

	}
}
