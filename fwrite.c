fWrite(void *buffer, int size, int count, FILES *fp){

		void *name;
		unsigned nwrite;
	
		if(!fp->buf_filled){
			if(fillbuf(fp)){
				return _EOF;
			}	
		}
		nwrite = size*count;
		memcpy(fp->ptr, buffer, nwrite);	
		if(fp->cnt == 0){
			fp->cnt = 0;		
		}
		else if(nwrite < fp->cnt){
			fp->cnt -= nwrite;		
		}
		
		else if(nwrite >= fp->cnt){
			fp->total += (nwrite - fp->cnt);			
			fp->cnt = 0;//As now the file would be in the end
		}
}

