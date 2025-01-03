#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int replace_str(char* s, char* t, char* g) {
	int flag = 0;
	long long m = strlen(t);
	while(*s != '\0') {
		if (*s == *t) { 
			if (strncmp(s, t, m) == 0) {
				char* q = s + m; 
				char* p = q;  
				char* rep = g; 
				int remlen = 0;   
				while (*q++ != '\0') { 
					remlen++;  
				}
				char* temp = NULL;
				temp = (char*)malloc(remlen * sizeof(char) + 1);
				if (temp == NULL) {
					exit(EXIT_FAILURE);
				}
				for (int j = 0; j < remlen; j++) {  
					*(temp + j) = *(p + j);  
				}
				*(temp + remlen) = '\0';  
				while (*rep != '\0') {  
					*s++ = *rep++;  
				}
				p = s;  
				char* p_temp = temp;  
				while (*p_temp != '\0') {  
					*p++ = *p_temp++;  
				}
				*p = '\0';  
				flag++; 
			}
			else {
				s++; 
			}
		}
		else {
			s++;
		}
	}
	return flag;
}

int main() {
	char s[30], t[5], g[5];
	gets(s);
	gets(t);
	gets(g);
	int k = replace_str(s, t, g);
	puts(s);
	printf("count=%d", k);
	return 0;
}