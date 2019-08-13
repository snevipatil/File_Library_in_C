#include<stdio.h>

int main(){
	FILE *fp = fopen("new", "w");
	fwrite("sneha", 5, 1, fp);
	//fseek(fp, -2, 2);
	//fwrite("over", 4, 1, fp);
	while(1){
		printf("doing\n");		
	}
}
