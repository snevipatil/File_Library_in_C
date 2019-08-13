int fRead(void *buffer, int size, int count, FILES *fp){
		char *data;
		unsigned int total;
		unsigned int left;
		unsigned int nbytes;
		unsigned int nread;
		
		if(fp->flag == AA || fp->flag == W)
			return ERR;		
		
		data = buffer;
	
		if(!fp->buf_filled){
			if(fillbuf(fp))
				return _EOF;	
		}
	
		left = total = size * count;
		while(left != 0){
			if(fp->cnt){
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
					return EOF;
				break;
			}
		}
}

