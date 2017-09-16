#pragma once
#include<stdio.h>


int check(int s) {
	int ret = 1;    //0非素数，1是素数
	if (s == 1) {
		ret = 0;
	}
	else if (s % 2 == 0) {
		ret = 0;
	}
	else {
		for (int i = 3; i <= (s / 2); i += 2) {
			if (s%i == 0) {
				ret = 0;
			}
		}
	}
	return ret;
}

int main() {
	int cc = 3;
	int i = 0;
	scanf("%d", &i);
	if (i == 1) {
		cc = 2;
	}
	for (--i; i>0; cc += 2) {
		if (check(cc) == 1) {
			--i;
		}
	}
	cc -= 2;
	printf("%d\n", cc);
	return 0;

}

