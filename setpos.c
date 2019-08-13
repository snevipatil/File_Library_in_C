int fGetpos(FILES *fp, pos *remind){
	fillbuf(fp);
	remind->cur_pos = fp->ptr - fp->name;
	remind->ptr = fp->ptr;
	return remind->cur_pos;
}

int fSetpos(FILES *fp, pos *remind){
	int x;
	x = fp->ptr - remind->ptr; 
	fp->cnt +=  x;
	fp->ptr = remind->ptr;
//	printf("%u", fp->ptr);
//	lseek(fp->fd, remind->cur_pos, 0);
	return remind->cur_pos;
};

