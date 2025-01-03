#include<stdio.h>
#include<ctype.h>
#include<string.h>
int fun(char a[]){
    int ans=0,i=0,j=0,n=strlen(a);
    while(a[i]!='\0'){
        if(isdigit(a[i])){
            ans++;
            for(j=i;j<n;j++){
                a[j]=a[j+1];
            }
            n--;
        }
        else{
            i++;
        }
    }
    return ans;
}
int main(){
    char arr[100];
    int ans=0;
    scanf("%s",arr);
    ans=fun(arr);
    printf("%d:%s",ans,arr);
    return 0;
}