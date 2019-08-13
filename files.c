#include"files.h"
#include<stdio.h>
#include<string.h>
#include<strings.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>


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
		fd = open(name, O_RDWR, S_IRUSR|S_IWUSR);
		_mode = RW;
	}
	
	else if(!strcmp(mode, "w")){
		fd = creat(name, O_WRONLY|S_IRUSR|S_IWUSR);		
		_mode = W;
	}
	else if(!strcmp(mode, "w+")){
		fd = creat(name, S_IRUSR|S_IWUSR);
		_mode = WR;
	}	
	else if(!strcmp(mode, "a")){
		fd = open(name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
			if(fd == -1)
				fd = creat(name, O_WRONLY|S_IRUSR|S_IWUSR);
		lseek(fd, 0L, SEEK_END);	
		_mode = A;
	}
	
	else if(!strcmp(mode, "a+")){
		fd = open(name, O_RDWR, S_IRUSR|S_IWUSR);
		if(fd == -1)
			fd = creat(name, O_RDWR|S_IRUSR|S_IWUSR);
//		lseek(fd, 0L, SEEK_END);
		_mode = AA;
	}	
	
	if(fd == -1){ //if the file does not open 
		return NULL;	
	}
//	printf("%d\n", fd);
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = _mode;
	fp->buf_filled = 0;
	return fp;
}


	int fillbuf(FILES *fp){
		fp->buf_filled = 1;
		fp->base = (char *)malloc(BUF_SIZE);
		if(fp->base == NULL)//can't get the buffer
			return EOF;
		fp->ptr = fp->base;
		switch(fp->flag){
			case R: case RW: 
				fp->cnt = read(fp->fd, fp->ptr, BUF_SIZE);
				fp->total = fp->cnt;
				break;
			case AA:
				printf("%ld\n",read(fp->fd, fp->ptr, BUF_SIZE));
				fp->cnt = fp->total = lseek(fp->fd, 0, SEEK_END);/*To get the size of the file*/
				lseek(fp->fd, 0, SEEK_START);/*Again sets it to the start of the file so that it can be read*/
				break;

			case W: case WR: case A: 
				fp->cnt = fp->total = 0;			
		}
		if(fp->cnt == -1){
			fp->flag = ERR;
			return EOF;
		}
		return 0;
	}
	int fSeek(FILES *fp, int offset, int _POS){
		int cur;
		cur = fp->ptr - fp->base;
		if(_POS == 0){
			if(offset > (cur + fp->cnt))
				return ERR;
			fp->ptr += (offset - cur);
			fp->cnt -= (offset - cur);			
		}
	
		else if(_POS == 1){
			if(offset > fp->cnt){
				return ERR;//Can't access beyond the file
			}
			if((offset < 0) && ((offset * -1) > cur))
				return ERR;
			fp->cnt -= offset;
			fp->ptr += offset;
		}
		else if(_POS == 2){
			if(fp->cnt == 0){
				fp->ptr += offset;
			}
			else{
				fp->ptr += (fp->cnt + offset);
			}
			if(offset <= 0)
				fp->cnt = offset*-1;
	
			else 
				fp->cnt = 0;
		}
		return 0;
}


int fRead(void *buffer, int size, int count, FILES *fp){
		char *data;
		unsigned int total;
		unsigned int left;
		unsigned int nbytes;
		unsigned int nread;
		
		if(fp->flag == A || fp->flag == W){
			return ERR;		
		}
		data = buffer;
	
		if(!fp->buf_filled){
			if(fillbuf(fp))
				return _EOF;	
		}
		left = total = size * count;
		printf("%d\n", fp->total);
		while(left != 0){
			if(fp->cnt > 0){
				nbytes = (left < fp->cnt ? left : fp->cnt);
				memcpy(data, fp->ptr, nbytes);
				fp->cnt -= nbytes;
				fp->ptr += nbytes;
				left -= nbytes;
				data += nbytes;
			}
			else if(total > BUF_SIZE){
				fp->cnt = read(fp->fd, fp->ptr, BUF_SIZE);
				if(fp->cnt <= 0){
					if(fp->cnt == -1)//error occured
						fp->flag = _ERR;
					else if(fp->cnt == 0)//end of file
						fp->flag = _EOF;
					return fp->flag;	
				}	
				nbytes = (left < fp->cnt ? left : fp->cnt);
				memcpy(data, fp->ptr, nbytes);
				total -= BUF_SIZE;
				fp->cnt -= nbytes;
				fp->ptr += nbytes;
				left -= nbytes;
				data += nbytes; 
			}
			else{
				if(fp->cnt == 0)
				
				break;
			}
		}
		return (total - left)/size;
}
int fWrite(void *buffer, int size, int count, FILES *fp){

		void *name;
		unsigned nwrite;
		int x;
	
		if(!fp->buf_filled){
			if(fillbuf(fp)){
				return _EOF;
			}	
		}
		if(fp->flag == AA)
			if((x = (fp->ptr - fp->base)) <= lseek(fp->fd, 0, 2)){
				fp->ptr += (lseek(fp->fd, 0, 2) - x);
				fp->cnt = 0;
			}
		nwrite = size*count;
		memcpy(fp->ptr, buffer, nwrite);
		fp->ptr += nwrite;	
		if(nwrite < fp->cnt){
			fp->cnt -= nwrite;		
		}
		
		else if(nwrite >= fp->cnt){
			fp->total += (nwrite - fp->cnt);			
			fp->cnt = 0;//As now the file would be in the end
		}
		return nwrite/size;	
	}
int fClose(FILES *fp){
	int ret_val;
	int x = 0;
	if(fp->flag != AA && fp->flag != A){
		fSeek(fp, 0, SEEK_START);	
	}
	if(fp->flag == AA){
		x = lseek(fp->fd, 0, 2);
		fSeek(fp, x, 0);
	}else if(fp->flag == A){
		fp->ptr = fp->base;
		lseek(fp->fd, 0, 2);
	}
	else
		lseek(fp->fd, 0, 0);
	
	write(fp->fd, fp->ptr, fp->total-x);
	free(fp->base);
	ret_val = close(fp->fd);
	if(ret_val == -1)
		return ERR;
	else
		return 0;
}
int fGetpos(FILES *fp, pos *remind){
	if(!fp->buf_filled){
		if(fillbuf(fp)){
			return _EOF;
		}
	}	
	remind->cur_pos = fp->ptr - fp->base;
	remind->ptr = fp->ptr;
	return remind->cur_pos;
}

int fSetpos(FILES *fp, pos *remind){
	int x;
	x = fp->ptr - remind->ptr; 
	fp->cnt +=  x;
	fp->ptr = remind->ptr;
	return remind->cur_pos;
}

int fTell(FILES *fp){
	return (fp->ptr-fp->base);
}

int fEof(FILES *fp){
	if(fp->cnt == 0)
		return EOF;
	else
		return 0;
}

