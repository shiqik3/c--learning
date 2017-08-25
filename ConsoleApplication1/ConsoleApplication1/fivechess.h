#include<stdio.h>
#include<stdlib.h>
#define COLS 10
#define ROWS 10

void menu() {
	printf("+----------------------+\n");
	printf("+  ��ӭʹ��������ϵͳ  +\n");
	printf("+                      +\n");
	printf("+ 1.��ʼ��Ϸ;  0.�˳�  +\n");
	printf("+----------------------+\n");
}
void restart() {
	printf("1.���¿�ʼ  0.�˳�\n");
}
void display(char map[ROWS][COLS]) {
	for (int i = 1; i < ROWS-1; i++) {
		for (int j = 1; j < COLS-1; j++) {
			if (map[i][j] != 0) {
				printf(" %c |", map[i][j]);
			}
			else {
				printf("   |");
			}
			
		}
		printf("\n");
		for (int k = 0; k < COLS; k++) {
			printf("----");
		}
		printf("\n");
	}
}
bool isOver(char map[ROWS][COLS],int x,int y) {
	int num_r = 1;
	int num_c = 1;
	int num_x = 1;
	int a;
	int b;
	a = x;
	b = y;
	/*
	�����ж�
	*/
	for (int i = -1; y+i > 0; ) {
		if (map[x][y] == map[x][y + i]) {
			i--;
			num_r++;
		}
		else {
			break;
		}
	}
	for (int i = 1; y+i < COLS; ) {
		if (map[x][y] == map[x][y + i]) {
			i++;
			num_r++;
		}
		else {
			break;
		}
	}
	/*
	�����ж�
	*/
	for (int i = -1; x + i > 0; ) {
		if (map[x][y] == map[x + i][y]) {
			i--;
			num_c++;
		}
		else {
			break;
		}
	}
	for (int i = 1; x + i < COLS; ) {
		if (map[x][y] == map[x + i][y]) {
			i++;
			num_c++;
		}
		else {
			break;
		}
	}
	/*
	б���ж�
	*/
	for (int i = -1; y + i > 0 && x + i > 0; ) {
		if (map[x][y] == map[x + i][y + i]) {
			i--;
			num_x++;
		}
		else {
			break;
		}
	}
	for (int i = 1; y + i < COLS && x + i < COLS; ) {
		if (map[x][y] == map[x + i][y + i]) {
			i++;
			num_x++;
		}
		else {
			break;
		}
	}
	if (num_r == 5 || num_x == 5 || num_c == 5) {
		return true;
	}
	return false;
}
void action_p(char map[ROWS][COLS],unsigned int &x,unsigned int &y) {
	printf("�׷��غ�,��������������\n");
	while (true) {
		scanf("%d %d", &x, &y);
		if (x<0 || y<0 || x>COLS - 1 || y>COLS - 1) {
			printf("�������ӷ�Χ������������\n");
		}
		else if (map[x][y] == 0) {
			map[x][y] = 'o';
			break;
		}
		else {
			printf("�˴��Ѿ����ӣ�����������\n");
		}
	}
}
void action_c(char map[ROWS][COLS],unsigned int &x,unsigned int &y) {
	printf("�ڷ��غ�,��������������\n");
	while (true) {
		scanf("%d %d", &x, &y);
		if (x<0 || y<0 || x>COLS - 1 || y>COLS - 1) {
			printf("�������ӷ�Χ������������\n");
		}
		else if (map[x][y] == 0) {
			map[x][y] = '#';
			break;
		}
		else {
			printf("�˴��Ѿ����ӣ�����������\n");
		}
	}
}

//int main() {
//	char map[ROWS][COLS] = {};
//	printf("%c", map[1][1]);
//	int choose;
//	unsigned int x;
//	unsigned int y;
//	menu();
//	scanf("%d", &choose);
//	while (choose==1) {
//		while (true) {
//			action_p(map,x,y);
//			display(map);
//			if (true == isOver(map,x,y)) {
//				break;
//			}
//			action_c(map, x, y);
//			display(map);
//			if (true == isOver(map,x,y)) {
//				break;
//			}
//		}
//		restart();
//		scanf("%d", &choose);
//	}
//	system("pause");
//	return 0;
//}