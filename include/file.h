#ifndef __M68_FILE_H__
#define __M68_FILE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Returns file size in bytes of file
size_t fileSize(FILE* fp);
//reads file contents of file (fn) into a buffer and returns it
char* makeBuffer(const char* fn);


#endif
