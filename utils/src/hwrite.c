#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc,char** argv){
	
	uint8_t in;
	in = 0;

	while(scanf("%x",&in) == 1){
		fwrite(&in,sizeof(uint8_t),1,stdout);
	}

	return 0;
}

