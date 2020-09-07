#include <lexer.h>

uint8_t addrMode(listNode* start){
	Token* t = (Token*)start->data;
	uint8_t mode = -1;
	//printf("START TOKEN: %s\n",t->token);
	if(strcmp(t->token,"(") == 0){
		t = (Token*)start->next->data;
		if(t->token[0] == 'a'){
			t = (Token*)start->next->next->data;
			if(strcmp(t->token,"+") == 0){
				mode = 0x3;
			}else{
				mode = 0x2;
			}
		}else{
			//(d16,An) and (d8,An,Xn) and (xxx).w and (xxx).l
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
		case 0x7:
			if(strcmp(t->token,"#") == 0)
				regNum = 0x4;
			break;
		default:
			break;
	}

	return regNum;
}



