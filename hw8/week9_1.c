#include<stdio.h>
#include<stdlib.h>
int *count(char *ch_p){
	static int ans=0;
	if(*ch_p>='A' && *ch_p<='Z'){
		*ch_p=*ch_p-'A'+'a';
	}
	if(*ch_p=='a' || *ch_p=='e' || *ch_p=='i' || *ch_p=='o' || *ch_p=='u'){
		ans++;
	}
	return &ans;
}
int main(){
	char c;
	int a;
	while((c=getchar())!='\n'){
		a=*(count(&c));
		printf("%c",c); 
	}
	printf(", %d",a);
	system("pause");
}
