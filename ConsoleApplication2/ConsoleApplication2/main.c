#define _CRT_SECURE_NO_DEPRECATE
#include "convert.h"
extern State state;
void DoConvertWork(FILE *pfread,FILE *pfwrite)
{
	while (state != END_STATE)
	{
		switch (state)
		{
		case NUL_STATE:
			DoNulState(pfread, pfwrite);
			break;
		case C_STATE:
			DoCState(pfread, pfwrite);
			break;
		case CPP_STATE:
			DoCppState(pfread, pfwrite);
			break;
		case END_STATE:
			break;
		}
	}
}


int main()
{
	FILE * pfwrite = NULL;
	FILE * pfread = NULL;

	pfread = fopen(INPUT_FILE,"r");
	if (NULL == pfread)
	{
		perror("open read error");
		exit(1);
	}
	pfwrite = fopen(OUTPUT_FILE,"w");
	if (NULL == pfwrite)
	{
		perror("open write error");
		fclose(pfread);
		exit(2);
	}

	DoConvertWork(pfread, pfwrite);

	fclose(pfread);
	fclose(pfwrite);
	system("pause");
	return 0;
}