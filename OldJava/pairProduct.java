/* PairProduct.java
   
*/

import java.util.Scanner;
import java.util.Vector;
import java.util.Arrays;
import java.io.File;

//Do not change the name of the PairUp class
public class PairProduct{
	/* PairProduct225()
		The input array A will contain non-negative integers. The function
		will search the array A for a pair of elements which sum to 225.
		If such a pair is found, return true. Otherwise, return false.
		The function may modify the array A.
		Do not change the function signature (name/parameters).
	*/

		//		if((225 % A[i]) == 0){
	//		if ((A[i] = 3) || (A[i] = 5) || (A[i] = 9) || (A[i] = 15) || (A[i] = 25) || (A[i] = 45)|| (A[i] = 75) ){
	//				arrays[i] = A[i];
	//			}

//Soroush Hajizadeh 
	public static boolean PairProduct225(int[] A){
		int n = A.length;
		int[] arrays = new int[A.length];           //make copy of array
		int A1a = 1;                                //as we want O(n), we need it to be efficient
		int A1b = 225;								//so we make all possible combinations of 225
		int A2a = 3;								//which are multiples.
		int A2b = 75;								//this can also be calculated using an algorithm
		int A3a = 5;
		int A3b = 45;
		int A4a = 9;
		int A4b = 25;
		int A5a = 15;
		int A5b = 15;
		int testForA1a = 0;  						//set base for number of pairs found for each combo
		int testForA1b = 0;							//each a, is the opposite needed for b to multiply into 225
		int testForA2a = 0;
		int testForA2b = 0;
		int testForA3a = 0;
		int testForA3b = 0;
		int testForA4a = 0;
		int testForA4b = 0;
		int testForA5 = -1;							//as 15 multiplies itself, we need to have 2 of it, so we start it at -1

		for (int i = 0; i < n; i++){
			if (A[i] == 1){
				testForA1a++;						//if found, increment the amount found for each
			}
			if (A[i] == 225){
				testForA1b++;
			}
			if (A[i] == 3){
				testForA2a++;
			}
			if (A[i] == 75){
				testForA2b++;
			}
			if (A[i] == 5){
				testForA3a++;
			}
			if (A[i] == 45){
				testForA3b++;
			}
			if (A[i] == 9){
				testForA4a++;
			}
			if (A[i] == 25){
				testForA4b++;
			}
			if (A[i] == 15){
				testForA5++;
			}

			if (testForA1a > 0 && testForA1b > 0){			//if their combination is found/it is in the positive, return true for the presence of a pair
				return true;
			}
			if (testForA2a > 0 && testForA2b > 0){
				return true;
			}
			if (testForA3a > 0 && testForA3b > 0){
				return true;
			}
			if (testForA4a > 0 && testForA4b > 0){
				return true;
			}
			if (testForA5 > 0){
				return true;
			}
		}
		return false;								//if no combinations are found, it'll return false
	}
	/* main()
	   Contains code to test the PairProduct225 function. Nothing in this function
	   will be marked. You are free to change the provided code to test your
	   implementation, but only the contents of the PairProduct225() function above
	   will be considered during marking.
	*/
	public static void main(String[] args){
		Scanner s;
		if (args.length > 0){
			try{
				s = new Scanner(new File(args[0]));
			} catch(java.io.FileNotFoundException e){
				System.out.printf("Unable to open %s\n",args[0]);
				return;
			}
			System.out.printf("Reading input values from %s.\n",args[0]);
		}else{
			s = new Scanner(System.in);
			System.out.printf("Enter a list of non-negative integers. Enter a negative value to end the list.\n");
		}
		Vector<Integer> inputVector = new Vector<Integer>();

		int v;
		while(s.hasNextInt() && (v = s.nextInt()) >= 0)
			inputVector.add(v);

		int[] array = new int[inputVector.size()];

		for (int i = 0; i < array.length; i++)
			array[i] = inputVector.get(i);

		System.out.printf("Read %d values.\n",array.length);


		long startTime = System.currentTimeMillis();

		boolean pairExists = PairProduct225(array);

		long endTime = System.currentTimeMillis();

		double totalTimeSeconds = (endTime-startTime)/1000.0;

		System.out.printf("Array %s a pair of values which multiply to 225.\n",pairExists? "contains":"does not contain");
		System.out.printf("Total Time (seconds): %.4f\n",totalTimeSeconds);
	}
}
