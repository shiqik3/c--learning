#pragma once
#include<iostream>

using namespace std;

class U_ptr {
private:
	friend class SmartPtr;
	int *uptr;
	size_t use;

	U_ptr(int* p) :uptr(p), use(1) {};

	~U_ptr()
	{
		delete uptr;
		cout << "ptr has been delete" << endl;
	}
};

class SmartPtr {
private:
	U_ptr *ptr;
public:
	SmartPtr(int *p = NULL) :ptr(new U_ptr(p)) {
		cout << "构造成功" << endl;
	};

	SmartPtr(const SmartPtr& rhs) :ptr(rhs.ptr) {
		++ptr->use;
		cout << "复制构造成功" << endl;
	}

	SmartPtr& operator=(const SmartPtr& rhs) {
		++ptr->use;
		if (--ptr->use == 0) {
			delete ptr;
		}
		ptr = rhs.ptr;
		cout << "赋值成功" << endl;
		return *this;
	}
	~SmartPtr()
	{
		if (--ptr->use == 0) {
			delete ptr;
		}
	}
	int operator*() {
		return *(this->ptr->uptr);
	}

	int* get() {
		return this->ptr->uptr;
	}

	void swap(SmartPtr& b) {
		U_ptr *tmp = b.ptr;
		b.ptr = this->ptr;
		this->ptr = tmp;
	}

	bool unique() {
		return this->ptr->use == 1 ? true : false;
	}

	size_t use_count() {
		return this->ptr->use;
	}

};


void swap(SmartPtr& a, SmartPtr& b) {
	a.swap(b);
}

