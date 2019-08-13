#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX 20

#define SEEK_START 0
#define SEEK_CUR 1
#define SEEK_END 2

	#define R 1
	#define W 2
	#define RW 3
	#define WR 4
	#define A 5
	#define AA 6
	#define _EOF -1
	#define ERR 10
	#define _ERR 10
	#define BUF_SIZE 1024

	typedef struct file{
		int cnt;
		char *ptr;
		char *base;
		int flag;
		int fd;
		int buf_filled;
		int total;
		//int pos;
	}FILES;


	FILES bus[MAX] = {{0, NULL, NULL, R, 0},
				 {0, NULL, NULL, W, 1},
				 {0, NULL, NULL, W, 2}};

 
FILES *fOpen(char *name, char *mode){
	int fd;
	FILES *fp;
	int found = 0, _mode;
	for(fp = bus; fp < bus + MAX; fp++){
		switch(fp->flag){
			case 1: case 2: case 3: case 4:case 5: case 6:
				break;
			default:
				found = 1;
			}
		if(found)
			break;//found the free slot
	}
	if(fp >= bus + MAX)
		return NULL;	
	
	if(!strcmp(mode, "r")){
		fd = open(name, O_RDONLY, S_IRUSR);
		_mode = R;
	}	
	
	else if(!strcmp(mode, "r+")){
		fd = open(name, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
		printf("fd = %d\n", fd);
		_mode = RW;
	}
	
	else if(!strcmp(mode, "w")){
		fd = open(name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
//		printf("%d opening\n", fd);
		_mode = W;
	}
	else if(!strcmp(mode, "w+")){
		fd = creat(name, S_IRUSR|S_IWUSR);
//		fd = open(name, O_CREAT);
		_mode = WR;
//		printf("%d\n", fd);
	}	
	else if(!strcmp(mode, "a")){
		fd = open(name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
		lseek(fd, 0L, SEEK_END);	
		_mode = A;
	}
	
	else if(!strcmp(mode, "a+")){
		fd = open(name, O_RDWR, S_IRUSR|S_IWUSR);
		if(fd == -1)
			fd = creat(name, O_RDWR);
		lseek(fd, 0L, SEEK_END);
		_mode = AA;
	}	
	
	if(fd == -1){
		printf("Can't open the file\n");
		return NULL;	
	}
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = _mode;
	fp->buf_filled = 0;
	return fp;
}


