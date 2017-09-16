#include <stdio.h>
#include <stdlib.h>

#define N 8
char board[N+2][N+2];

void init(void)
{
	int i;
	for (i = 0; i < N + 2; i++) {
		board[0][i] = '#';
		board[N+1][i] = '#';
		board[i][0] = '#';
		board[i][N + 1] = '#';
	}
	for (i = 1; i <= N;i++)
	{
		int j;
		for (j = 1; j <= N;j++)
		{
			board[i][j] = ' ';
		}
	}
}

void display(void)
{
	int i, j;
	for (i = 0; i < N + 2; i++)
	{
		for (j = 0; j < N + 2;j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

struct Pos
{
	int ios;
	int jos;
};
typedef struct Pos pos_t;

pos_t pos[3] = { { -1, -1 }, { -1, 0 }, { -1, 1 } };

int check(int i, int j)
{
	int p;
	int ni, nj;
	int ret = 1;
	for (p = 0; p<3; p++) {
		ni = i;
		nj = j;
		while (ret && (board[ni][nj] != '#')) {
			ni = ni + pos[p].ios;
			nj = nj + pos[p].jos;
			ret = ret && (board[ni][nj] != '*');
		}
	}

	return ret;
}

void find(int i)
{
	if (i> N) {
		display();
		getchar();
	} else {
		int j;
		for (j = 1; j <= N;j++)
		{
			if (check(i, j)) {
				board[i][j] = '*';
				find(i + 1);
				board[i][j] = ' ';
			}
		}
	}
}

int main(void)
{
	init();
	//display();
	find(1);

	system("pause");
}
