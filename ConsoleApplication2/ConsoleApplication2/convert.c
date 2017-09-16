#define _CRT_SECURE_NO_DEPRECATE
#include "convert.h"
State state = NUL_STATE;
void DoNulState(FILE *pfread, FILE *pfwrite)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfread);
	if ('/' == first)
	{
		second = fgetc(pfread);
		if ('*' == second)
		{
			fputc('/',pfwrite);
			fputc('/', pfwrite);
			state = C_STATE;
		}
		else if ('/' == second)
		{
			fputc('/', pfwrite);
			fputc('/', pfwrite);
			state = CPP_STATE;
		}
		else
		{
			/*fputc(first, pfwrite);
			fputc(second, pfwrite);*/
		}
	}
	else if (EOF == first)
	{
		state = END_STATE;
	}
	else
	{
		fputc(first, pfwrite);
		
	}
}

void DoCState(FILE *pfread, FILE *pfwrite)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfread);
	if ('*' == first)
	{
		second = fgetc(pfread);
		if ('/' == second)
		{

			char next = fgetc(pfread);
			if (next != '\n' && next != EOF)
			{
				fputc(next, pfwrite);
			}

			fputc('\n', pfwrite);

			state = NUL_STATE;
			
		}
		else
		{
			fputc(first, pfwrite);
			ungetc(second,pfread);////返回第二个*
		}
	}
	else if ('\n' == first)
	{
		fputc(first, pfwrite);
		fputc('/', pfwrite);
		fputc('/', pfwrite);
	}
	else
	{
		fputc(first, pfwrite);
	}

	
}


void DoCppState(FILE *pfread, FILE *pfwrite)
{
	int first = 0;
	int second = 0;
	first = fgetc(pfread);
	if (EOF == first)
	{
		
		state = END_STATE;
	}
	else if ('\n' == first)
	{
		fputc(first, pfwrite);
		state = NUL_STATE;
	}
	else
	{
		fputc(first,pfwrite);
	}
}