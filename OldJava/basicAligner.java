import java.io.*;
public class BasicAligner implements Aligner  {

private String[] sequence;
private char[][] cArray;
int minErrors;
int numberOfMoves;
//////////////////////////////////////////////////////
	public BasicAligner(String[] sequence){
		this.cArray = new char[sequence.length][];
		this.sequence = sequence;

		for (int i=0; i< sequence.length; i++){
			this.cArray[i]=this.sequence[i].toCharArray();
		}

	//	System.out.println(cArray.length);
		//System.out.println(cArray[0].length);
		//System.out.println(cArray[1].length);
		//System.out.println(cArray[0]);
		//System.out.println(cArray[1]);
		this.minErrors = cArray[1].length;
	}
/////////////////////////////////////////////////////////
								public static void main (String []args) throws IOException {
								String A = "AAAGGGC";
								String B = "AGGG";
										String[] str = {A,B};
										BasicAligner test = new BasicAligner(str);
										System.out.println("");
										//test.matchAt(3,0);
										//test.performAlignment();
										//test.Tm();
										//test.getNumErrors();
										//test.getOffset(1);
										//test.getSequence(0);
								}
///////////////////////////////////////////////////////////////
			public String Tm() {
				System.out.println("");
								System.out.println("Primer evaluator");

				int q;
				int Count = 0;
													for(q=0; q<cArray[1].length;q++){
															if (cArray[1][q] == 'G' ){
															Count++;
															}else if (cArray[1][q] == 'C') {
															Count++;
															}else{
															}
													}
				char[] str2 = cArray[1];
				System.out.print("Original code is: ");
				System.out.println(cArray[1]);
					for(int k = 0; k < cArray[1].length; k++){
				  	  	if (str2[k] == 'A'){
							str2[k] = 'T';
						}else if (str2[k] == 'T'){
							str2[k] = 'A';
						}else if (str2[k] == 'G'){
							str2[k] = 'C';
						}else if (str2[k] == 'C'){
							str2[k] = 'G';
						}
					}
					System.out.print("Complementary code is:  ");
					System.out.println(str2);


					double Temp = (81.5 + (0.41 * Count/cArray[1].length) - 675/(cArray[1].length + 1) - (cArray[1].length + 1));

					if (this.minErrors > 0){ //accounting for(%mismatch)
					Temp = Temp - ((cArray[1].length + 1)/this.minErrors * 100 );
					}

												System.out.println("");
												System.out.print("If primers were to be made for PCR the sequence would be : " );
												System.out.println(str2);
												System.out.println("The number of GC bases in the potential primer is :" + Count);
												System.out.println("The Temperature of Melting is "  + Temp + " Degrees Celcius" );
												if (Temp < 55){
													System.out.println("Increase number of bases, Tm is too low");
												}else if (Temp > 65){
													System.out.println("Decrease number of bases, Tm is too high");
											}
										return "S";
							}

							  /*Additional Test: Temperature of melting calculation for best match in degrees celcius
							   81.5 + 0.41 (%GC content) - 675/N - %mismatch
							   N = primer length in base pairs.  */

///////////////////////////////////////////////////////
	private int matchAt(int firstI, int secondI){
		System.out.println("");
				for(int y=0; y< cArray[1].length; y++){
					System.out.print(cArray[0][firstI + y] + "");
				}
							System.out.println("");

				for(int z=0; z< cArray[1].length; z++){
					System.out.print(cArray[1][secondI + z] + "");
				}
							System.out.println("");
	//System.out.println(cArray[0][firstI] + "" + cArray[0][firstI + 1] + "" + cArray[0][firstI + 2] + "" + cArray[0][firstI + 3]);
	//System.out.println(cArray[1][secondI] + "" + cArray[1][secondI + 1]+ "" + cArray[1][secondI + 2] + "" + cArray[1][secondI + 3]);
 		int numberOfMismatches = cArray[1].length;

				for(int j=0; j< cArray[1].length; j++){
					if (cArray[0][firstI + j] == cArray[1][secondI+ j]) {
					numberOfMismatches--;
					}}
									if (this.minErrors >= numberOfMismatches){
									 this.minErrors = numberOfMismatches;
									 this.numberOfMoves++;
									}
		System.out.println("The number of mismatches is " + numberOfMismatches);
		System.out.println("The lowest number of errors is: " + minErrors);
		System.out.println("");
		return minErrors;
		}
///////////////////////////////////////////////////////////////
		  public int getNumErrors(){
		 return minErrors;
	}
//////////////////////////////////////////////////////////////////////
    public void performAlignment(){
		for(int c=0; c< cArray[0].length - ((1 - cArray[1].length)* -1); c++){
			matchAt(c ,0);
		}
	}
/////////////////////////////////////////////////////////////////////
    public int getOffset(int sequenceNumber){
 return numberOfMoves;
    }
////////////////////////////////////////
    public String getSequence(int sequenceNumber){
 return sequence[sequenceNumber];
    }
}
