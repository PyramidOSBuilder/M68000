#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printAscii(char* buffer){
	printf(" ");
	for(int i = 0; i < 16;i++){
		if(buffer[i] < 0x20 || buffer[i] > 0x7f)
			printf(".");
		else
			printf("%c",buffer[i]);
	}
	printf("\n");
}

int main(int argc,char** argv){
	int c = 0;
	int indx = 0;
	int bufsz = 0;
	char buffer[16];
	FILE* fp;

	if(argc < 2){
		printf("Usage: hex [in]\n");
		return 0;
	}
	
	fp = fopen(argv[1],"rb");
	if(fp == NULL){
		printf("Error opening %s\n",argv[1]);
		return 0;
	}

	printf("0x0000: ");
	while((c = fgetc(fp)) != EOF){
		if(bufsz == 16){
			printf("\n0x%4x:",indx);
			printAscii(buffer);
			bufsz = 0;
		}
		printf("%02x ",c);
		buffer[bufsz++] = c;
		indx++;
	}

	if(indx % 16 != 0){
		memset(&buffer[bufsz],'.',16-bufsz);
	}

	printAscii(buffer);
	
	
	fclose(fp);
	
	return 0;
	
}
