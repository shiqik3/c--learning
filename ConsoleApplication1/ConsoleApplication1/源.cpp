#include<iostream>
#include<string>
#include<vector>

using namespace std;



bool isde7(string s) {
	//int ssss;
	char* w = (char*)s.c_str();
	int tmp = 0;
	for (; *w!='\0'; w++) {
		//ssss = tmp * 10 + (*w - '0');
		tmp = (tmp * 10 + (*w - '0')) % 7;
	}
	return tmp == 0;
}

int main() {
	vector<string> a;
	string cmp,ss;
	int n,num;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	num = 0;
	for (int i = 0; i < a.size(); i++) {
		cmp = a[i];
		for (int j = 0; j < a.size(); j++) {
			if (i == j) {
				continue;
			}
			else {
				ss = cmp + a[j];
				if (isde7(ss)) {
					++num;
				}
			}
		}
	}
	cout << num;
	return 0;
	
}


//#include<iostream>
//#include<vector>
//
//using namespace std;
//
//int swap(int sw) {
//	if (sw == 0 ) {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//int main() {
//	vector<int> list;
//	int n;
//	int ret = 0;
//	int sw = 1;
//	cin >> n;
//	list.resize(n);
//
//	for (int i = 0; i < n; i++) {
//		cin >> list[i];
//	}
//
//	for (int i = 0; i < n; i++) {
//		if (list[i] == sw) {
//			++ret;
//			sw = swap(sw);
//		}
//	}
//	if (ret % 2 == 0) {
//		cout << "Bob";
//	}
//	else {
//		cout << "Alice";
//	}
//	return 0;
//}