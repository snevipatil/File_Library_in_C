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
#define AA 6	//a+ mode
#define _EOF -1
#define ERR 10
#define _ERR 10
#define BUF_SIZE 1024

typedef struct file{
	int cnt;		//will keep the count of the characters left to read in a particular file
	char *ptr;		//is the pointer to the current location in the file
	char *base;		//it is the address of the starting byte of the file
	int flag;		//will set wrt to the modes in which the file is opened
	int fd;			//file pointer returned by open
	int buf_filled;		//will indicate whether the buffer is filled or not
	int total;		//total number of bytes in the file at anytime
}FILES;

typedef struct pos{
	int cur_pos;	//will give the current byte location wrt start
	char *ptr;	//will give pointer of that location
}pos;
FILES *fOpen(char *name, char *mode);

int fillbuf(FILES *fp);
	
int fSeek(FILES *fp, int offset, int _POS);

int fRead(void *buffer, int size, int count, FILES *fp);

int fWrite(void *buffer, int size, int count, FILES *fp);

int fClose(FILES *fp);

int fGetpos(FILES *fp, pos *remind);

int fSetpos(FILES *fp, pos *remind);

int fTell(FILES *fp);

int fEof(FILES *fp);

