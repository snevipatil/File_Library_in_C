int fClose(FILES *fp){
	int ret_val, x = 0;
	if(fp->flag != AA || fp->flag != A){
		fSeek(fp, 0, SEEK_START);	
	}
	if(fp->flag == AA){
		x = lseek(fp->fd, 0, SEEK_END);
		fSeek(fp, x, 0);
	}
	else if(fp->flag == A){
		fp->ptr = fp->base;
		lseek(fp->fd, 0, SEEK_END);
	}
	else{
		fSeek(fp, 0, SEEK_START);
		lseek(fp->fd, 0, 0);
	}
		
	retval = write(fp->fd, fp->ptr, fp->total - x);
	free(fp->base);	
	if(retval == -1)
		return ERR;
	
	ret_val = close(fp->fd);
	if(ret_val == -1)
		return ERR;
	else
		return 0;
}


