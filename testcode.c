#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>

#include"files.h"

//	TEST 1:

/*int main(){
	printf("\nMY FUNCTION\n");
	FILES *fp = fOpen("abc", "w+");
	if(fp == NULL){
		printf("An error occured while opening the file\n");
		return ERR;
	}
	int a[5] = {1, 2, 3, 4, 5}, b[5] = {10, 12, 14, 16, 18}, c[10], d[10];
	fWrite(a, 4, 5, fp);
	fWrite(b, 4, 5, fp);
	fSeek(fp, 0, 0);
	fRead(c, 4, 10, fp);
	for(int i = 0; i < 10; i++){
		printf("%d\t", c[i]);
	}	
	fClose(fp);
	printf("\n\nINBUILT FUNCTION\n\n");
	FILE *fq = fopen("num", "w+");
	if(fq == NULL){
		printf("An error occured while opening the file\n");
		return ERR;
	}
	fwrite(a, 4, 5, fq);
	fwrite(b, 4, 5, fq);
	fseek(fq, 0, 0);
	fread(d, 4, 10, fq);
	for(int i = 0; i < 10; i++)
		printf("%d\t", d[i]);
	fclose(fq);
}
*/

//TEST 2: 
/* Writing a structure in a file and then readind it*/
/*
typedef struct data{
	int i;
	char name[10];
	float j;
}DATA;

int main(){
	//MY FUNCTIONS

	DATA a = {1, "sneha", 2.3}, b, c;
	FILES *fp = fOpen("abc", "w+");
	fWrite(&a, sizeof(a), 1, fp);
	fSeek(fp, 0, 0);
	fRead(&b, sizeof(b), 1, fp);
	printf("MY FUNCTIONS\n%d\t %s\t%f\n\n", b.i, b.name, b.j);
	fClose(fp);
	
	//INBUILT	

	FILE *fq;
	fq = fopen("num", "w+");
	fwrite(&a, sizeof(a), 1, fq);
	fseek(fq, 0, 0);
	fread(&c, sizeof(c), 1, fq);
	printf("INBUILT\n%d\t %s \t %f\n\n", c.i, c.name, c.j);
	fclose(fq);
  		
}
*/
//TEST 3:
/* Writing in a file and reading from that file using other file pointer*/
/*
int main(){
	//MY FUNCTION	
		
	FILES *fw, *fr;
	char a[50];
	fw = fOpen("abc", "w");
	fWrite("Writing first and then reading", 30, 1, fw);
	fClose(fw);//The buffer gets written only on closing it.
	fr = fOpen("abc", "r");
	fRead(a, 50, 1, fr);//HERE THE SIZE OF THE ARRAY IS GREATER THAN THE SIZE OF THE FILE
	printf("MY FUNCTION \n %s \n\n", a);
	fClose(fr);  
	
	//INBUILT

	FILE *fpw, *fpr;
	char b[50];
	fpw = fopen("num", "w");
	fwrite("Writing first and then reading", 30, 1, fpw);
	fclose(fpw);//The buffer gets written only on closing it.
	fpr = fopen("abc", "r");
	fread(b, 50, 1, fpr);
	printf("INBUILT \n %s \n\n", b);
	fclose(fpr);  

}*/

//TEST 4:
/*
 Writing contents to a file using INBUILT FUNCTIONS and then operating it with r+ mode using MY FILE FUNCTIONS
*/
/*int main(){
	FILE *fw = fopen("abc", "w");
	if(fw == NULL){
		printf("An error occured, couldn't open the files\n");
		return ERR;
	}
	float a[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
	fwrite(a, 4, 5, fw);
	fclose(fw);
	//now doing using MY FILE FUNCTIONS
	FILES *fp = fOpen("abc", "r+");
	if(fp == NULL){
		printf("An error occured, couldn't open the files\n");
		return ERR;
	}
	float b[5], c[5] = {10.1, 10.2, 10.3, 10.4, 10.5};
	fRead(b, 4, 5, fp);
	printf("Reading and printing the previous contents of the file\n");
	for(int i = 0; i < 5; i++)
		printf("%f\t", b[i]);
	fSeek(fp, 0, SEEK_START);
	fWrite(c, 4, 5, fp);
	fSeek(fp, 0, SEEK_START);
	fRead(b, 4, 5, fp);
	printf("\n\nPrinting the over written contents of the file\n");
	for(int i = 0; i < 5; i++)
		printf("%f\t", b[i]);
	fClose(fp);		
}*/

//TEST 5:	
/* Testing the append mode*/

/*
int main(){
	FILES *fp = fOpen("abc", "a");
	fWrite("append", 6, 1, fp);
	fClose(fp);
}
*/

//TEST 6:
/* Using fgetpos and fsetpos*/

/*int main(){
	FILES *fp, *fp2;
	//fp = fOpen("abc", "w");
	fp2 = fOpen("xyz", "w");
	fp = fOpen("abc", "w");
}*/
/*
int main(){
	FILES *fp = fOpen("abc", "a+");
	char a[10];
	printf("%u\n", fp->ptr);
	fRead(a, 10, 1, fp);
	printf("%u\n", fp->ptr);
	fSeek(fp, -5, 2);
	printf("%u\n", fp->ptr);
	fWrite("new", 3, 1, fp);
	printf("%u\n", fp->ptr);
	fClose(fp);
}
*/
/* TEST_01
Trying to open various files in diffeent modes and print errors when required
*//*
#include<stdio.h>

int main(){
	FILES *f1, *f2, *f3, *f4, *f5, *f6;
	f1 = fOpen("abc", "r");
	//Would occur when we try to open a non existing file.
	if(f1 == NULL){
		printf("\nError occured to open the file in ""r"" mode\n");
//		return -1;	
	}
	else
		printf("\nFor ""r"" file fp->fd %d\n", f1->fd); 
	f2 = fOpen("abc2", "w");
	//Would create a new file abc2 in "w".
	if(f2 == NULL){
		printf("\nError occured in ""w"" mode \n");
//		return -1;
	}
	else
		printf("\nCreated new file in ""w"" mode %d\n", f2->fd);
		
	f3 = fOpen("abc3", "r+");
	//Would give r/w access to the file if it exists else gives an error if the file does not exist	
	if(f3 == NULL){
		printf("\nError occured to open the file in ""r+"" mode\n");
//		return -1;
	}
	else
		printf("\nFor ""r+"" file fp->fd %d\n", f3->fd);
	
	f4 = fOpen("abc4", "w+");	
	//Would create a new file and give it write and read access	
	if(f4 == NULL){
		printf("\nError occured to open the file in ""w+"" mode\n");
//		return -1;
	}
	else
		printf("\nFor ""w+"" mode fp->fd %d\n", f4->fd);
	
	f5 = fOpen("abc5", "a");
	//append the text to end or write at the start in the new file
	if(f5 == NULL){
		printf("\nError occured to open the file in ""a"" mode\n");
//		return -1;
	}
	else
		printf("\nFile opened in ""a"" mode fp->fd %d\n", f5->fd);
	f6 = fOpen("abc6","a+");
	//append the text to the end and also read the file and create if does not exists
	if(f6 == NULL){
		printf("\nError occured to open the file in ""a+"" mode\n");
//		return -1;
	}
	else
		printf("\nFile opened in ""a+"" mode fp->fd %d\n", f6->fd);
	
	return 0;	
				
}
*/
/*	
#include<stdio.h>
typedef struct data{
	int i;
	char name[10];
}DATA;
int main(){
	FILES *fc, *fi, *ff, *fs;

//	READS AND WRITE STRING IN FILE
	char x[10];
	fc = fOpen("char", "w+");
	fWrite("writing", 7, 1, fc);
	fSeek(fc, 0, SEEK_START);
	fRead(x, 10, 1, fc);
	printf("\nCHAR FILE OUTPUT:\n%s\n", x);
	fClose(fc);

//	READS AND WRITE INTEGERS IN FILE
	fi = fOpen("int", "w+");
	int a[5] = {1, 2, 3, 4, 5}, b[5];
	fWrite(a, 4, 5, fi);
	fSeek(fi, 0, SEEK_START);
	fRead(b, 4, 5, fi);
	printf("\nINTEGER FILE\n");	
	for(int i = 0; i < 5; i++)
		printf("%d\t", b[i]);
	printf("\n");
	fClose(fi);

//	READS AND WRITE FLOATS IN FILE
	ff = fOpen("float", "w+");
	float c[5] = {1.1, 2.2, 3.3, 4.4, 5.5}, d[5];
	fWrite(c, 4, 5, ff);
	fSeek(ff, 0, SEEK_START);
	fRead(d, 4, 5, ff);
	printf("\nFLOAT FILE FILE\n");	
	for(int i = 0; i < 5; i++)
		printf("%f\t", d[i]);
	printf("\n");
	fClose(ff);

//	READS AND WRITE STRUCTURES IN FILE
	fs = fOpen("struct", "w+");
	DATA e = {1, "sneha"}, f;
	fWrite(&e, sizeof(e), 1, fs);
	fSeek(fs, 0, SEEK_START);
	fRead(&f, sizeof(f), 1, fs);
	printf("\n STRUCT\n %d %s", f.i, f.name);
	fClose(fs);		
}*/
/*
//PASS LESS BYTES TO READ THEN THERE ARE IN FILE
int main(){
	FILES *fp;
	fp = fOpen("test4", "r");
	char a[5];
	int read = fRead(a, 1, sizeof(a), fp); 
	printf("Size of the file %d bytes\n", fp->total);
	printf("Bytes read from the file %d a is %s\n", read, a);
	fClose(fp); 
}
*/

/*PASS MORE THAN IN FILE*/
/*int main(){
	FILES *fp;
	fp = fOpen("test4", "r");
	char a[30];
	int read = fRead(a, 1, sizeof(a), fp); 
	printf("Size of the file %d bytes\n", fp->total);
	printf("Bytes read from the file %d a is %s\n", read, a);
	fClose(fp);  

}
*/

//READING FROM ONE FILE AND APPENDING IT TO OTHER/*

/*int main(){
	FILES *f1, *f2, *f3;
//	reads from this file
	f1 = fOpen("test4", "r");
	char  a[5];
	fRead(a, 5, 1, f1);
	fClose(f1);
//	reads the previous contents of the file where we append
	f3 = fOpen("append", "r");
	char b[50];
	fRead(b, 50, 1, f3);
	printf("FILE BEFORE APPENDING \n %s", b);
	fClose(f3);
	
//	appends to this file
	f2 = fOpen("append", "a");
	fWrite(a, 5, 1, f2);
	fClose(f2);
//	will print the contents of the file after it has appended
	f3 = fOpen("append", "r");
	b[50];
	fRead(b, 50, 1, f3);
	printf("\n\nFILE AFTER APPENDING \n %s", b);
	fClose(f3);
	 
}*/

/*int main(){
	FILES *fp = fOpen("test4", "a+");
	char a[80];
	fRead(a, 80, 1, fp);
	printf("PRINTING THE CONTENTS OF THE FILE test4\n\n %s\n\n", a);
	fClose(fp);
}*/
//TEST 09
/*int main(){
	FILES *fp = fOpen("test4", "r+");
	char a[30];
	pos p;
	fRead(a, 1, 30, fp);
	fGetpos(fp ,&p);
	printf("FILE BEFORE \n\n %s\n\n", a);
//	Sets to the Start
	fSeek(fp, 0, 0);
//	Setting the file to the end and then writing
	fSetpos(fp, &p);
	fWrite("append", 6, 1, fp);
	fSeek(fp, 0, 0);
	fRead(a, 30, 1, fp);
	printf("AFTER THE fSetpos ,i.e., after appending\n\n %s", a);
	fClose(fp);

}*/

//TEST 10

/*int main(){
	FILES *fp = fOpen("test4", "w");
	int a[5] = {1, 2, 3, 4, 5}, b;
	fWrite(a, 4, 5, fp);
	fClose(fp);

	fp = fOpen("test4", "r");
		while(!fEof(fp)){
			fRead(&b, 4, 1, fp);
			printf("doing%d\t", b);	
		}	
	
	fClose(fp);
}
*/
