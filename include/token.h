#ifndef __M68_TOKEN_H__
#define __M68_TOKEN_H__

#define TOKEN_OP 0
#define TOKEN_OPERATOR 1
#define TOKEN_DIRECTIVE 2
#define TOKEN_LABEL 3
#define TOKEN_EOL 4
#include <list.h>
#include <stdint.h>
//Generic token struct
typedef struct Token{
	char* token;
	int type;
	
}Token;

//Constructor
Token* newToken(char* text,int type);
//Deconstructor
void freeToken(void* token);
//Print func
void printToken(void* token);
//Comparator
int cmpToken(void* token0,void* token1);
//Generates a list of tokens from a text buffer and returns
List* generateTokens(char* buffer);
//Prints out a list of tokens
void printTokenList(List* tokens);

#endif

