#include<stdio.h>
#include<stdlib.h>
class Aff {
public :
	int a;
	Aff(int b) {
		a = b;
	}
};
void newfa(Aff*f) {
	*f = Aff(4);
}
int main() {
	Aff ac = Aff(9);
	newfa(&ac);
	printf("%d", ac.a);
	system("pause");
}