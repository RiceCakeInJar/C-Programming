#include<stdio.h>
#include<stdlib.h> 
int main(){
	char first,second;
	printf("Please input first character");
	scanf("%c",&first);
	switch(first){
		case'M':
		case'm':
			printf("Monday\n");
			break;
		case'W':
		case'w':
			printf("Friday\n");
			break;
		case'F':
		case'f':
			printf("Friday\n");
			break;
		case'T':
		case't':
			printf("Please input second character");
			scanf(" %c",&second);
			switch(second){
				case'U':
				case'u':
					printf("Tuesday\n");
					break;
				case'H':
				case'h':
					printf("Thursday\n");
					break;
				default:
					printf("Illegal input\n");
					break;
			}
			break;
		case'S':
		case's':
			printf("Please input second character");
			scanf(" %c",&second);
			switch(second){
				case'A':
				case'a':
					printf("Saturday\n");
					break;
				case'U':
				case'u':
					printf("Sunday\n");
					break;
				default:
					printf("Illegal input\n");
					break;
			}
			break;
		default:
			printf("Illegal input");
			break;	
	}
	system("pause");
}


