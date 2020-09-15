#include <stdio.h>
#include <token.h>
#include <stdint.h>
Token* newToken(char* text,int type){
	Token* token = malloc(sizeof(Token));
	token->token = text;
	token->type = type;
	return token;
}

void freeToken(void* token){
	free(((Token*)token)->token);
	free(token);	
}

void printToken(void* token){
	printf("%s\n",((Token*)token)->token);
}

int cmpToken(void* token0,void* token1){
	Token* t0 = (Token*)token0;
	Token* t1 = (Token*)token1;

	if(t0->type == t1->type && strcmp(t0->token,t1->token) == 0){
		return 1;
	}
	return 0;
}

int isNotWhtSpace(char c){
	if(c == ' ' || c == '\t' || c == '\n')
		return 0;
	return 1;
}

#define NUM_OPERATORS 8
const char operators[] = {'.',',','(',')','-','+','*','#'};

int isOperator(char c){
	int i;
	for(i = 0; i < NUM_OPERATORS;i++){
		if(operators[i] == c)
			return 1;
	}
	return 0;
}

void printTokenList(List* tokens){
	listNode* n;
	for(n = tokens->head;n != NULL; n = n->next){
		tokens->printNode(n->data);
	}
}

List* generateTokens(char* buffer){
	char cur = 0;
	char last = 0;
	int i = 0;
	List* tokenList = newList(freeToken,printToken);
	int captureIndex = 0;
	Token* curToken = NULL;
	char* curBuffer = NULL;
	uint8_t comment = 0;
	do {
		if(cur == ';'){
			comment = 1;
				
		}
		if(comment == 0){
			if(!isNotWhtSpace(cur)){
				if(captureIndex+1 != i && isNotWhtSpace(last)){
					curBuffer = malloc(sizeof(char)* (i-captureIndex));
					strncpy(curBuffer,&buffer[captureIndex],(i-captureIndex));
					curBuffer[i-captureIndex-1] = '\0';
					curToken = newToken(curBuffer,TOKEN_OP);
					addList(tokenList,curToken);
					if(cur == '\n'){  
						curBuffer = malloc(sizeof(char)*4);
						strcpy(curBuffer,"EOL");
						curBuffer[3] = '\0';
						curToken = newToken(curBuffer,TOKEN_EOL);
						addList(tokenList,curToken);
					}
				}
				captureIndex = i;
			}
		
			if(isOperator(cur)){
				if(i-captureIndex > 0 && isNotWhtSpace(last) && !isOperator(last)){
					curBuffer = malloc(sizeof(char)* (i-captureIndex));
					strncpy(curBuffer,&buffer[captureIndex], (i-captureIndex));
					curBuffer[i-captureIndex-1] = '\0';
					curToken = newToken(curBuffer,TOKEN_OP);
					addList(tokenList,curToken);
				}
				curBuffer = malloc(sizeof(char)*2);
				curBuffer[0] = cur;
				curBuffer[1] = '\0';
				curToken = newToken(curBuffer,TOKEN_OPERATOR);
				addList(tokenList,curToken);
				captureIndex = i;
			}
		}else{
			if(cur == '\n')
				comment = 0;
			captureIndex = i;
		}
		last = cur;
	}while((cur = buffer[i++]) != '\0');
	return tokenList;
}

