#include <stdio.h>
#include <stdint.h>
#include <file.h>
#include <list.h>
#include <token.h>
#include <lexer.h>
int main(int argc,char** argv){
	if(argc > 1){
		char* buffer = makeBuffer(argv[1]);
		if(buffer == NULL)
			return 1;

		List* tokens = generateTokens(buffer);
		printTokenList(tokens);
		uint8_t* code = malloc(sizeof(uint8_t)* 1024);
		uint8_t* og = code;
		uint32_t ptr = 0;
		uint16_t op = 0;
		uint16_t sizeField = 0;
		uint16_t srcReg = 0;
		uint16_t dstReg = 0;
		uint16_t srcMode = 0;
		uint16_t dstMode = 0;
		uint16_t immed0 = 0;
		uint32_t immed1 = 0;
		listNode* n;
		for(n = tokens->head; n != NULL;n = n->next){
			Token* t = (Token*)n->data;
			
			if(strcmp(t->token,"move") == 0){
				immed0 = 0;
				immed1 = 0;
				op = 0;
				sizeField = 0;
				srcReg = 0;
				dstReg = 0;
				srcMode = 0;
				dstMode = 0;

				n = n->next->next;
				t = (Token*)n->data;
				if(t->token[0] == 'b'){
					sizeField = 0x1;
				}else if(t->token[0] == 'w'){
					sizeField = 0x3;
				}else if(t->token[0] == 'l'){
					sizeField = 0x2;
				}
				n = n->next;
				listNode* operandStart = n;
				srcMode = addrMode(n);
				srcReg = registerNum(n);
				t = (Token*)n->data;
				if(t->token[0] != '('){
					while(((Token*)(n = n->next)->data)->token[0] != ','){
						t = (Token*)n->data;
						if(strcmp(t->token,"EOL") == 0){
							printf("Error: Missing operand in move\n");
							exit(1);
						}
					}
				}else{
					while(((Token*)(n = n->next)->data)->token[0] != ')');
					n = n->next;
				}
				n = n->next;
				dstMode = addrMode(n);
				dstReg = registerNum(n);

				printf("SRC MODE: %x|SRC REG: %x\n",srcMode,srcReg);
				printf("DST MODE: %x|DST REG: %x\n",dstMode,dstReg);
				op = (sizeField << 12) | ( (dstReg & 0x07) << 9) | ( dstMode << 6) | (srcMode << 3) | (srcReg & 0x07);
				*code++ = (op & 0xff00) >> 8;
				*code++ = op & 0x00ff;
				if(srcMode == 0x7){
					if(srcReg == 0x4){
						t = (Token*)operandStart->next->data;
						switch(sizeField){
							case 0x1:	//b
								immed0 = strtol(t->token,NULL,0);
								*code++ = 0x00;
								*code++ = immed0 & 0x00ff;
								break;
							case 0x3:	//w
								immed0 = strtol(t->token,NULL,0);
								*code++ = (immed0 & 0xff00) >> 8;
								*code++ = (immed0 & 0x00ff);
								break;
							case 0x2:	//l
								immed1 = strtol(t->token,NULL,0);
								*code++ = (immed1 & 0xff000000) >> 24;
								*code++ = (immed1 & 0x00ff0000) >> 16;
								*code++ = (immed1 & 0x0000ff00) >> 8;
								*code++ = (immed1 & 0x000000ff);
								break;
							default:
								break;
						}
					}
				}else if(srcMode == 0x5){
					t = (Token*)operandStart->next->data;
					immed0 = strtol(t->token,NULL,0);
					*code++ = (immed0 & 0xff00) >> 8;
					*code++ = (immed0 & 0x00ff);
				}else if(srcMode == 0x6){
					t = (Token*)operandStart->next->data;
					immed0 = strtol(t->token,NULL,0);
					printf("displacement: %02x\n",immed0);
					*code++ = 0x00;
					*code++ = (immed0 & 0xff);
				}

			}

		}
		FILE* fp = NULL;
		if(argc < 3)
			fp = fopen("test.bin","wb");
		else
			fp = fopen(argv[2],"wb");
		fwrite(og,sizeof(uint8_t),(size_t)(code-og),fp);
		fclose(fp);
		free(og);
		deleteList(tokens);
	}
	return 0;
}

