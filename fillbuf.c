
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
				fp->cnt = fp->total = lseek(fp->fd, 0, SEEK_END);
				break;
			case W: case WR: case A:
				fp->cnt = fp->total = 0;			
		}

		if(fp->cnt == -1)
			fp->flag = ERR;
			return EOF;
		}
		return 0;
	}
