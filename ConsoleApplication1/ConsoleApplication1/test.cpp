////#include <stdio.h>
////#include <stdlib.h>
////#include <time.h>
////int fy[500][500];
////int d[][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
////int w = 30, h = 15, u = w * 2 + 1, v = h * 2 + 1;  //u�ǿ�v�Ǹ�
////int yzfy(int y, int x) {
////	if (x<1 || y<1 || x >= u - 1 || y >= v - 1 || fy[y][x])return 0; else fy[y][x] = 1;
////	for (int f = rand() % 4, i = 0, p = rand() & 1 ? 3 : 1; i<4; ++i, f = (f + p) % 4)
////		if (yzfy(y + *d[f] * 2, x + d[f][1] * 2)) fy[y + *d[f]][x + d[f][1]] = 1;
////	return 1;
////}
////int main() {
////	srand(time(NULL)); yzfy(1, 1); fy[1][0] = fy[v - 2][u - 1] = 1;
////	for (int y = 0; y < v; ++y, puts(""))
////		for (int x = 0; x < u; ++x)
////			printf("%s", fy[y][x] ? "��" : "��");
////	system("pause");
////	return 0;
////}
//
//
//
//#include<iostream>
//#include<stdlib.h>
//#include<time.h>
//#include<stack>
//
//using namespace std;
//
//
////ÿ��intԪ��0δ���ʣ�1�ѷ��ʣ�2����ұߣ�3����±�
//
//class mazeRb {
//	//Recursive backtracker(�ݹ���ݣ���������㷨)
//	//1.�������Ϊ��ǰ�Թ���Ԫ�����Ϊ�ѷ���
//	//2.��������δ��ǵ��Թ���Ԫ������ѭ��
//	//	1>�����ǰ�Թ���Ԫ��δ�����ʵ������Թ���Ԫ
//	//		1.1���ѡ��һ��δ���ʵ������Թ���Ԫ
//	//		1.2����ǰ�Թ���Ԫ��ջ
//	//		1.3�Ƴ���ǰ�Թ���Ԫ�������Թ���Ԫ��ǽ
//	//		1.4��������Թ���Ԫ��������Ϊ��ǰ�Թ���Ԫ
//	//	2>�����ǰ�Թ���Ԫ������δ���ʵ����ڵ��Թ���Ԫ������ջ����
//	//		2.1ջ�����Թ���Ԫ��ջ
//	//		2.2�����Ϊ��ǰ�Թ���Ԫ
//public:
//	int const static row = 50;    //����
//	int const static col = 50;    //����
//	int const static nv = 0;     //δ����
//	int maze_list[row][col];
//	int mx = 0, my = 0;    //��ʾ��ǰ��Ԫ������
//	stack<int> ss;
//	mazeRb() {
//		for (int i = 0; i < row; i++) {
//			for (int j = 0; j < col; j++) {
//				maze_list[i][j] = nv;
//			}
//		}
//	}
//	void complete() {
//		int result = 0;
//		int ret;
//		maze_list[0][0] = 1;
//		srand((int)time(0));
//		for (int i = 0; i < row; i++) {
//			for (int j = 0; j < col; j++) {
//				while (maze_list[i][j] == 0) {
//					result = haNeiNv(mx, my);
//					if (result > 0) {
//						int a = rand() % 4;
//						ret = 0;
//						while (!ret) {
//							a++;
//							a %= 4;
//							ret = (result >> a) & 1;
//						}
//						ss.push(-1);
//						ss.push(my);
//						ss.push(mx);
//						unions(mx, my, a);
//					}
//					else {
//						mx = ss.top();
//						ss.pop();
//						my = ss.top();
//						ss.pop();
//						ss.pop();
//					}
//				}
//			}
//		}
//	}
//	void print() {
//		pprint();
//	}
//private:
//
//	int haNeiNv(int s1, int s2) {
//		int ret = 0;
//		if (s1 - 1 >= 0 && maze_list[s1 - 1][s2] == 0) {
//			ret += 1;    //��
//		}
//		if (s1 + 1 < row && maze_list[s1 + 1][s2] == 0) {
//			ret += 2;    //��
//		}
//		if (s2 - 1 >= 0 && maze_list[s1][s2 - 1] == 0) {
//			ret += 4;    //��
//		}
//		if (s2 + 1 < col && maze_list[s1][s2 + 1] == 0) {
//			ret += 8;    //��
//		}
//		return ret;
//	}
//
//	void unions(int x, int y, int o) {
//		switch (o) {
//		case 0:
//			maze_list[x - 1][y] += 3;
//			mx = x - 1;
//			break;
//		case 1:
//			maze_list[x][y] += 3;
//			mx = x + 1;
//			break;
//		case 2:
//			maze_list[x][y - 1] += 2;
//			my = y - 1;
//			break;
//		case 3:
//			maze_list[x][y] += 2;
//			my = y + 1;
//			break;
//		default:
//			printf("error");
//		}
//		maze_list[mx][my] += 1;
//	}
//
//	//��ӡ����
//	void pprint() {
//		//�����һ��
//		printf("  ");
//		for (int i = 1; i < col; i++) {
//			printf("__");
//		}
//		printf("\n");
//		//����м���
//		for (int i = 0; i < row - 1; i++) {
//			if (i > 0) {
//				printf("|");    //��һ��
//			}
//			else {
//				printf(" ");
//			}
//			for (int j = 0; j < col; j++) {
//				printf("%s", belink(i, j).c_str());    //�м���
//			}
//			cout << endl;
//		}
//		//���һ��
//		printf("|");
//		for (int j = 0; j < col - 1; j++) {
//			printf("%s", belink(row - 1, j).c_str());    //�м���
//		}
//		cout << " ";
//		cout << endl;
//		//printf("%d", find(num_col*num_row-1));
//
//	}
//
//	string belink(int x, int y) {
//		string ret = "";
//		switch (maze_list[x][y]) {
//		case 1:
//			ret = "_|";
//			break;
//		case 3:
//			ret = "__";
//			break;
//		case 4:
//			ret = " |";
//			break;
//		case 6:
//			ret = "  ";
//			break;
//		default:
//			printf("error");
//		}
//		return ret;
//	}
//
//};
//
//#include<iostream>
//#include<vector>
//#include<list>
//class mazeRp {
//private:
//	int const static row = 20;    //����
//	int const static col = 20;    //����
//	int const static mright = 2;    //�ұߵ�ǽ
//	int const static mbottom = 4;    //�±ߵ�ǽ
//	int const static isvisit = 1;    //�ѷ���
//	int const static nv = 0;     //δ����
//	vector<vector<int>> maze_list{ row,vector<int>(col,0) };    //�Թ�����
//	list<int> maze_sav;
//
//public:
//	mazeRp() {
//		clear();
//	}
//	void clear() {
//		//����1:���Թ�ȫ��ǽ
//		for (vector<int> s : maze_list) {
//			for (int w : s) {
//				w = 0;
//			}
//		}
//	}
//	void complete() {
//		//����2:ѡһ������Ϊ�Թ���ͨ·
//		srand((int)time(0));
//		int mx = 0;    //x����
//		int my = 0;    //y����
//		int mf = 0;    //ǽ
//		int ran = 0;
//		list<int>::iterator iter = maze_sav.begin();
//		mx = rand() % row;
//		my = rand() % col;
//		maze_list[mx][my] = isvisit;
//		madd_list(mx, my);
//		//����3:���б��ﻹ��ǽʱ
//		while (maze_sav.size() > 0) {
//			//����3.1���б������ѡ��һ��ǽ�����������ĸ��Ӳ����Թ���ͨ·
//			ran = rand() % (maze_sav.size() - 1) / 4 * 4;
//			iter = maze_sav.begin();
//			for (int i = 0; i < ran; ) {
//				++iter;
//				++i;
//			}
//			mx = *iter;
//			iter = maze_sav.erase(iter);
//			my = *iter;
//			iter = maze_sav.erase(iter);
//			mf = *iter;
//			iter = maze_sav.erase(iter);
//			iter = maze_sav.erase(iter);
//			do_link(mx, my, mf);
//
//
//		}
//	}
//
//	void do_link(int x, int y, int f) {
//		if (f == 2) {
//			if (maze_list[x][y] == 0) {
//				//����3.1.1��ǽ��ͨ���ö���ĸ��ӳ�Ϊ�Թ���ͨ·
//				++maze_list[x][y];
//				maze_list[x][y] += mright;
//				//����3.1.2���Ǹ����ӵ���ǽ�����б�
//				madd_list(x, y);
//			}
//			else if (y + 1 < col && maze_list[x][y + 1] == 0) {
//				++maze_list[x][y + 1];
//				maze_list[x][y] += mright;
//				madd_list(x, y + 1);
//			}
//			else {
//
//			}
//		}
//		else if (f = 4) {
//			if (maze_list[x][y] == 0) {
//				//����3.1.1��ǽ��ͨ���ö���ĸ��ӳ�Ϊ�Թ���ͨ·
//				++maze_list[x][y];
//				maze_list[x][y] += mbottom;
//				//����3.1.2���Ǹ����ӵ���ǽ�����б�
//				madd_list(x, y);
//			}
//			else if (x + 1 < row && maze_list[x + 1][y] == 0) {
//				++maze_list[x + 1][y];
//				maze_list[x][y] += mbottom;
//				madd_list(x + 1, y);
//			}
//			else {
//
//			}
//		}
//	}
//
//	bool madd_list(int x, int y) {
//		bool ret = false;
//		//�ϱߵ�ǽ���ϸ����ǽ
//		if (x > 0 && maze_list[x - 1][y] == 0) {
//			maze_sav.push_back(x-1);
//			maze_sav.push_back(y);
//			maze_sav.push_back(mbottom);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		//��ߵ�ǽ��������ǽ
//		if (y > 0 && maze_list[x][y - 1] == 0) {
//			maze_sav.push_back(x);
//			maze_sav.push_back(y-1);
//			maze_sav.push_back(mright);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		//�������ǽ
//		if (maze_list[x][y] >> 2 == 0) {
//			maze_sav.push_back(x);
//			maze_sav.push_back(y);
//			maze_sav.push_back(mbottom);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		//�������ǽ
//		if (maze_list[x][y] >> 1 == 0) {
//			maze_sav.push_back(x);
//			maze_sav.push_back(y);
//			maze_sav.push_back(mright);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		return ret;
//	}
//
//	void print() {
//		//��һ��
//		printf("��");
//		for (int i = 0; i < col; i++) {
//			printf("����");
//		}
//		cout << endl;
//		//�м���
//		for (int i = 0; i < row; i++) {
//			printf("��");
//			for (int j = 0; j < col; j++) {
//				cout << switchpic1(i, j).c_str();
//			}
//			cout << endl;
//			printf("��");
//			for (int j = 0; j < col; j++) {
//				cout << switchpic2(i, j).c_str();
//			}
//			cout << endl;
//		}
//	}
//
//	string switchpic1(int x, int y) {
//		string ret = "";
//		if (maze_list[x][y] >> 1 & 1 == 1) {
//			ret = "    ";
//		}
//		else {
//			ret = "  ��";
//		}
//		return ret;
//	}
//	string switchpic2(int x, int y) {
//		string ret = "";
//		if (maze_list[x][y] >> 2 & 1== 1) {
//			ret = "  ��";
//		}
//		else {
//			ret = "����";
//		}
//		return ret;
//	}
//
//};
//
////c++���������
//int main() {
//	mazeRp* test = new mazeRp();
//	test->complete();
//	test->print();
// 	system("pause");
//	delete test;
//	return 0;
//}