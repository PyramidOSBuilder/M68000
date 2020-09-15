#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char** argv){
	if(argc < 2){
		printf("Usage: hex [in]\n");
		return 0;
	}
	
	FILE* fp = fopen(argv[1],"rb");
	if(fp == NULL){
		printf("Error opening %s\n",argv[1]);
		return 0;
	}
	
	int c = 0;
	while((c = fgetc(fp)) != EOF)
		printf("%02x ",c);
	
	fclose(fp);
	
	return 0;
	
}
