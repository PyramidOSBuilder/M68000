#include <file.h>

size_t fileSize(FILE* fp){
	size_t size;
	
	fseek(fp,0L,SEEK_END);
	size = ftell(fp);
	rewind(fp);
	return size;
}

char* makeBuffer(const char* fn){
	FILE* fp = fopen(fn,"r");
	if(fp == NULL){
		printf("Error: fopen failed in makeBuffer\n");
		return NULL;
	}

	size_t fsize = fileSize(fp);
	char* buffer = (char*)malloc(sizeof(char)*fsize);
	int result = fread(buffer,sizeof(char),fsize,fp);
	if(result != fsize){
		printf("Error: file read error in makeBuffer!\n");
		free(buffer);
		fclose(fp);
		return NULL;
	}	
	fclose(fp);
	return buffer;
}

