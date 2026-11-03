#include<stdio.h>
#include<stdlib.h>
int MIN(int *p,int n);
int MAX(int *p,int n);
int main(){
    int n;
    scanf("%d",&n);
    int *p=malloc(n*sizeof(int));
    if(p==NULL){
        return 1;
    }
    else{
    for(int i=0;i<n;i++){
        scanf("%d",&p[i]);
    }
        }
    int a=MIN(p,n);
    int b=MAX(p,n);
    printf("%d %d",a,b);
    free(p);
    p=NULL;
return 0;
}
    int MIN(int *p,int n){
        int min=p[0];
        for(int j=1;j<n;j++){
            if(p[j]<min){min=p[j];}
        }
        return min;
    }
    int MAX(int*p,int n){
        int max=p[0];
        for(int j=1;j<n;j++){
            if(p[j]>max){max=p[j];}
        }
        return max;
    }