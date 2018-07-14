//Soroush Hajizadeh

//Fibonnaci sequence with blinking bonus in AVR 2560
/////////////////////////////

#define F_CPU 16000000UL			
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


Fib(input){					//actual fibonacci calc
	  if (input ==0){	//doesn't take care of base cases 0 and 1
		  return 0;
	  }
	  if(input ==1){	//so they are returned seperately
		  return 1;
	  }
	  int count;
	  int t1=0;
	  int t2=1;
	  int display=0;
	  count=1;			//start count at 1 to account for base cases
	  while (count<input) { //do actual addition
	      display=t1+t2;
	      t1=t2;
	      t2=display;
	      ++count;		//incremement till desired value
	  }
  return display;		//return the obtained value
}

	int main(){
	int x =60;		//THIS IS WHERE THE Nth Number of Fib goes
	int n = 0;
	int counter =0;
		while(n <x){		//till the desired nth fib
	
		  DDRL = 0xFF;		//SETTING THINGS UP FOR BLINKS
		  DDRB = 0xFF;

			if (n==47){ ///stops working at n = 47, because the value becomes larger than the possible int.
				return(printf("error, reached largest integer size"));
			}
		
				if(n % 6 == 0){					//mod 6, blink light 1

					while(counter < Fib(n) ){	//while the count is less than the measured fib
						PORTL = 0x00;			//
						PORTB = 0b0010;			// this and the above line blink the led
						_delay_ms(100);			//cause blink with delay
						PORTL = 0x00;			//along with null light
						PORTB = 0b0000;
						_delay_ms(100);	
						counter = counter +1;	//count up till fib number
					}	
				counter = 0;				//reset counter back to 0
				_delay_ms(500);				//delay before switching to next light/number
				}

				if(n % 6 == 1){					//from here for the next 5 is the same as 1
					while(counter < Fib(n) ){
						PORTL = 0x00;
						PORTB = 0b1000;
						_delay_ms(100);
						PORTL = 0x00;
						PORTB = 0b0000;
						_delay_ms(100);
						counter = counter +1;
					}
				counter =0;
				_delay_ms(500);
				}

				if(n % 6 == 2){
					while(counter <Fib(n) ){
						PORTL = 0b0010;
						PORTB = 0b0000;
						_delay_ms(100);
						PORTL = 0x00;
						PORTB = 0b0000;
						_delay_ms(100);
						counter = counter +1;
						}
				counter = 0;
				_delay_ms(500);
				}

				if(n % 6 == 3){
					while(counter <Fib(n) ){
						PORTL= 0b1000;
						PORTB = 0b0000;
						_delay_ms(100);
						PORTL = 0x00;
						PORTB = 0b0000;
						_delay_ms(100);
						counter = counter +1;
						}
				counter = 0;
				_delay_ms(500);
				}

				if(n % 6 == 4){
					while(counter <Fib(n) ){
						PORTL = 0b00100000;
						PORTB = 0b0000;
						_delay_ms(100);
						PORTL = 0x00;
						PORTB = 0b0000;
						_delay_ms(100);
						counter = counter +1;
						}
					counter = 0;
					_delay_ms(500);
				}

				if(n % 6 == 5){
					while(counter <Fib(n)){
					PORTL = 0b10000000;
					PORTB = 0b0000;
					_delay_ms(100);
					PORTL = 0x00;
					PORTB = 0b0000;
					_delay_ms(100);
					counter = counter +1;
					}
				counter = 0;
				_delay_ms(500);
				}	

			printf("%d ", Fib(n));					//print fib number if on pc
			n = n+1;								//increment till desired number

		}
		
	}


