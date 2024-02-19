#include <stdio.h>

int main(void){
	int a, b, c;
	printf("Please input three numbers: ");
	scanf("%d %d %d", &a, &b, &c);
	if ( a < b && b < c ){
		if ( b%a==0 && c%a==0 ){
			printf("Divisible & Increasing\n");
			return 0;
		}
		else {
			printf("Not divisible & Increasing\n");
			return 1;
		}
	}
	else {
		if ( b%a==0 && c%a==0 ){
             		printf("Divisible & Not increasing\n");
                        return 2;
		}
		else {
			printf("Not divisible & Not increasing\n");
                        return 3;
		}
	}
}
