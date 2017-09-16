////#include <stdio.h>
////#include <stdlib.h>
////#include <time.h>
////int fy[500][500];
////int d[][2] = { { 0,1 },{ 1,0 },{ 0,-1 },{ -1,0 } };
////int w = 30, h = 15, u = w * 2 + 1, v = h * 2 + 1;  //u是宽，v是高
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
////			printf("%s", fy[y][x] ? "　" : "█");
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
////每个int元素0未访问，1已访问，2拆除右边，3拆除下边
//
//class mazeRb {
//	//Recursive backtracker(递归回溯，深度优先算法)
//	//1.将起点作为当前迷宫单元并标记为已访问
//	//2.当还存在未标记的迷宫单元，进行循环
//	//	1>如果当前迷宫单元由未被访问的相邻迷宫单元
//	//		1.1随机选择一个未访问的相邻迷宫单元
//	//		1.2将当前迷宫单元入栈
//	//		1.3移除当前迷宫单元与相邻迷宫单元的墙
//	//		1.4标记相邻迷宫单元并用它作为当前迷宫单元
//	//	2>如果当前迷宫单元不存在未访问的相邻的迷宫单元，并且栈不空
//	//		2.1栈顶的迷宫单元出栈
//	//		2.2令其成为当前迷宫单元
//public:
//	int const static row = 50;    //行数
//	int const static col = 50;    //列数
//	int const static nv = 0;     //未访问
//	int maze_list[row][col];
//	int mx = 0, my = 0;    //表示当前单元格坐标
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
//			ret += 1;    //上
//		}
//		if (s1 + 1 < row && maze_list[s1 + 1][s2] == 0) {
//			ret += 2;    //下
//		}
//		if (s2 - 1 >= 0 && maze_list[s1][s2 - 1] == 0) {
//			ret += 4;    //左
//		}
//		if (s2 + 1 < col && maze_list[s1][s2 + 1] == 0) {
//			ret += 8;    //右
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
//	//打印函数
//	void pprint() {
//		//输出第一行
//		printf("  ");
//		for (int i = 1; i < col; i++) {
//			printf("__");
//		}
//		printf("\n");
//		//输出中间行
//		for (int i = 0; i < row - 1; i++) {
//			if (i > 0) {
//				printf("|");    //第一列
//			}
//			else {
//				printf(" ");
//			}
//			for (int j = 0; j < col; j++) {
//				printf("%s", belink(i, j).c_str());    //中间列
//			}
//			cout << endl;
//		}
//		//最后一行
//		printf("|");
//		for (int j = 0; j < col - 1; j++) {
//			printf("%s", belink(row - 1, j).c_str());    //中间列
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
//	int const static row = 20;    //行数
//	int const static col = 20;    //列数
//	int const static mright = 2;    //右边的墙
//	int const static mbottom = 4;    //下边的墙
//	int const static isvisit = 1;    //已访问
//	int const static nv = 0;     //未访问
//	vector<vector<int>> maze_list{ row,vector<int>(col,0) };    //迷宫数组
//	list<int> maze_sav;
//
//public:
//	mazeRp() {
//		clear();
//	}
//	void clear() {
//		//步骤1:让迷宫全是墙
//		for (vector<int> s : maze_list) {
//			for (int w : s) {
//				w = 0;
//			}
//		}
//	}
//	void complete() {
//		//步骤2:选一个格作为迷宫的通路
//		srand((int)time(0));
//		int mx = 0;    //x坐标
//		int my = 0;    //y坐标
//		int mf = 0;    //墙
//		int ran = 0;
//		list<int>::iterator iter = maze_sav.begin();
//		mx = rand() % row;
//		my = rand() % col;
//		maze_list[mx][my] = isvisit;
//		madd_list(mx, my);
//		//步骤3:当列表里还有墙时
//		while (maze_sav.size() > 0) {
//			//步骤3.1从列表里随机选择一个墙，如果它对面的格子不是迷宫的通路
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
//				//步骤3.1.1把墙打通，让对面的格子成为迷宫的通路
//				++maze_list[x][y];
//				maze_list[x][y] += mright;
//				//步骤3.1.2把那个格子的邻墙计入列表
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
//				//步骤3.1.1把墙打通，让对面的格子成为迷宫的通路
//				++maze_list[x][y];
//				maze_list[x][y] += mbottom;
//				//步骤3.1.2把那个格子的邻墙计入列表
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
//		//上边的墙，上格的下墙
//		if (x > 0 && maze_list[x - 1][y] == 0) {
//			maze_sav.push_back(x-1);
//			maze_sav.push_back(y);
//			maze_sav.push_back(mbottom);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		//左边的墙，左格的右墙
//		if (y > 0 && maze_list[x][y - 1] == 0) {
//			maze_sav.push_back(x);
//			maze_sav.push_back(y-1);
//			maze_sav.push_back(mright);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		//本格的下墙
//		if (maze_list[x][y] >> 2 == 0) {
//			maze_sav.push_back(x);
//			maze_sav.push_back(y);
//			maze_sav.push_back(mbottom);
//			maze_sav.push_back(NULL);
//			ret = true;
//		}
//		//本格的右墙
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
//		//第一行
//		printf("■");
//		for (int i = 0; i < col; i++) {
//			printf("■■");
//		}
//		cout << endl;
//		//中间行
//		for (int i = 0; i < row; i++) {
//			printf("■");
//			for (int j = 0; j < col; j++) {
//				cout << switchpic1(i, j).c_str();
//			}
//			cout << endl;
//			printf("■");
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
//			ret = "  ■";
//		}
//		return ret;
//	}
//	string switchpic2(int x, int y) {
//		string ret = "";
//		if (maze_list[x][y] >> 2 & 1== 1) {
//			ret = "  ■";
//		}
//		else {
//			ret = "■■";
//		}
//		return ret;
//	}
//
//};
//
////c++程序主入口
//int main() {
//	mazeRp* test = new mazeRp();
//	test->complete();
//	test->print();
// 	system("pause");
//	delete test;
//	return 0;
//}