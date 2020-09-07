#ifndef __M68_LEXER_H__
#define __M68_LEXER_H__
#include <list.h>
#include <token.h>
#include <stdint.h>

uint8_t addrMode(listNode* start);
uint8_t registerNum(listNode* start);
uint32_t immediateVal(listNode* start);
uint8_t sizeVal(listNode* start);



#endif

