#define _CRT_SECURE_NO_DEPRECATE
#ifndef _CONVERT_
#define _CONVERT_
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>

#define INPUT_FILE "input.c"
#define OUTPUT_FILE "output.c"

typedef enum STATE
{
	NUL_STATE,
	C_STATE,
	CPP_STATE,
	END_STATE
}State;



void DoNulState(FILE *pfread,FILE *pfwrite);
void DoCState(FILE *pfread, FILE *pfwrite);
void DoCppState(FILE *pfread, FILE *pfwrite);

#endif