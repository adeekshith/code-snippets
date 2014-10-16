//Integer to string conversion without any library
#include <stdio.h>
#define MAX_SIZE 10
main(){
	int integer=231,i=0;
	char str[MAX_SIZE]={0};
	while(integer){
		str[i++]=(char)((integer%10)+48);
		integer/=10;
	}
	printf("%s,",str);
	while(i--){
		printf("%c",str[i]);
	}
}
