#include <stdio.h>
#include <stdint.h>
#include <file.h>
#include <list.h>
#include <token.h>

int main(int argc,char** argv){
	if(argc > 1){
		char* buffer = makeBuffer(argv[1]);
		if(buffer == NULL)
			return 1;

		List* tokens = generateTokens(buffer);
		printTokenList(tokens);
	
	}
	return 0;
}

