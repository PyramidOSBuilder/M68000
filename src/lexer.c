#include <stdio.h>
#include <lexer.h>

int isANumber(char* str){
	switch(str[0]){
		case '0' ... '9':
			return 1;
		default:
			return 0;
	}
}

int isHexNumber(char* str){
	if(str[1] == 'x')
		return 1;
	return 0;
}

uint8_t addrMode(listNode* start){
	Token* t = (Token*)start->data;
	uint8_t mode = -1;
	//printf("START TOKEN: %s\n",t->token);
	if(strcmp(t->token,"(") == 0){
		t = (Token*)start->next->data;
		if(t->token[0] == 'a'){
			t = (Token*)start->next->next->next->data;
			printf("token: %s\n",t->token);
			if(strcmp(t->token,"+") == 0){
				mode = 0x3;
			}else{
				mode = 0x2;
			}
		}else{
			//(d16,An) and (d8,An,Xn) and (xxx).w and (xxx).l
			t = (Token*)start->next->data;
			if(isANumber(t->token)){
				/*uint32_t num = 0;
				if(isHexNumber(t->token))
					num = strtol(t->token,NULL,0);
				else
					num = strtol(t->token,NULL,10);*/
				t = (Token*)start->next->next->data;
				if(t->token[0] == ','){
					// (d16,An) && (d8,An,Xn) && (d16,PC) && (d8,PC,Xn)
					t = (Token*)start->next->next->next->data;
					if(t->token[0] == 'a'){
						t = (Token*)start->next->next->next->next->data;
						if(t->token[0] == ')')
							mode = 0x5;
						else
							mode = 0x6;
					}else if(t->token[0] == 'p')
						mode = 0x7;
				}else{
					// (xxx).w && (xxx).l
					mode = 0x7;
				}
			}
			//(d16,PC) (d8,PC,Xn)
		}
	}else if(t->token[0] == 'd'){
		mode = 0x0;
	}else if(t->token[0] == 'a'){
		mode = 0x1;
	}else if(strcmp(t->token,"-") == 0){
		mode = 0x4;
	}else if(strcmp(t->token,"#") == 0){
		mode = 0x7;
	}
	return mode;
}

uint8_t registerNum(listNode* start){
	Token* t = (Token*)start->data;
	//printf("Token: %s\n",t->token);
	uint8_t regNum = -1;
	uint8_t mode = addrMode(start);
	switch(mode){
		case 0x0 ... 0x01:
			regNum = t->token[1] - 0x30;
			break;
		case 0x2 ... 0x03:
			t = (Token*)start->next->data;
			regNum = t->token[1] - 0x30;
			break;
		case 0x4:
			t = (Token*)start->next->next->data;
			regNum = t->token[1] - 0x30;
			break;
		case 0x5:
		case 0x6:
		case 0x7:
			if(strcmp(t->token,"#") == 0){
				regNum = 0x4;
				break;
			}
			if(strcmp(t->token,"(") == 0){
				// other displacements
				t = (Token*)start->next->data;
				//printf("Displace : %s\n",t->token);
				if(isANumber(t->token)){
					t = (Token*)start->next->next->data;
					if(t->token[0] == ','){
						t = (Token*)start->next->next->next->data;
						//printf("dis reg token: %s\n",t->token);
						if(t->token[0] == 'p'){
							t = (Token*)start->next->next->next->next->data;
							if(t->token[0] == ',')
								regNum = 0x3;
							else
								regNum = 0x2;
						}else
							regNum = t->token[1] - 0x30;
						break;
					}
					t = (Token*)start->next->next->next->next->data;
					if(t->token[0] == 'w'){
						regNum = 0x0;
						break;
					}else if(t->token[0] == 'l'){
						regNum = 0x1;
						break;
					}
					
				}

			}
			regNum = 0x1;
			break;
		default:
			break;
	}

	return regNum;
}



