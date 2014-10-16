#include <stdio.h>

/*
 * Procedure:
 * Keep extracting common factors of the numbers and then keep dividing both the numbers with their common factors until there are no more common factors.
 * The resulting fraction is the simplified one.
 * */

main(){
	int num=256,den=1024, counter=2;
	/*
	 * num is Numerator, den is denominator. fration is num/den
	 * */
	printf("Actual fraction is: %d/%d\n",num,den);
	while(counter<=num){
		if( (num%counter)==0 ){
			if ( (den%counter)==0 ){
				num/=counter;
				den/=counter;
			}else{
				counter++; //incrementing as it is not divisible by denominator => not a factor
			}
			
		}else{
			counter++; //incrementing as it is not divisible by numerator => not a factor
		}
	}
	printf("simplified fraction is: %d/%d \n",num,den);
}
