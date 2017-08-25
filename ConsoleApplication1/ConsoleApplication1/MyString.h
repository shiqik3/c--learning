#pragma once
#include<utility>
#include<stdio.h>

class MyString {
public:
	MyString()
		:data_(new char[1])
	{
		*data_ = '\0';
	}
	MyString(const char* str)
		:data_(new char[strlen(str) + 1]) {
		strcpy(data_, str);
	}
	MyString(const MyString& rhs)
		:data_(new char[rhs.size() + 1]) {
		strcpy(data_, rhs.Myc_str);
	}
	~MyString() {
		delete[] data_;
	}
	MyString& operator=(MyString rhs) {
		MyString(rhs);
		return *this;
	}
	char* Myc_str() const {
		return data_;
	}
	size_t size() const {
		return strlen(data_);
	}
private:
	char* data_;
};