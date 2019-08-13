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
				fp->cnt = offset * -1;
			else {
				fp->cnt = 0;
			}
		}
		return 0;
}

