#pragma once
#include<iostream>  
using namespace std;

// �������HasPtr��ʹ�õ�U_Ptr�࣬���ڷ�װʹ�ü��������ָ��  
// ���������г�Ա����private�����ǲ�ϣ����ͨ�û�ʹ��U_Ptr�࣬������û���κ�public��Ա  
// ��HasPtr������Ϊ��Ԫ��ʹ���Ա���Է���U_Ptr�ĳ�Ա  
class U_Ptr
{
	friend class HasPtr;
	int *ip;
	size_t use;
	U_Ptr(int *p) : ip(p), use(1)
	{
		cout << "U_ptr constructor called !" << endl;
	}
	~U_Ptr()
	{
		delete ip;
		cout << "U_ptr distructor called !" << endl;
	}
};

class HasPtr
{
public:
	// ���캯����p��ָ���Ѿ���̬������int����ָ��  
	HasPtr(int *p, int i) : ptr(new U_Ptr(p)), val(i)
	{
		cout << "HasPtr constructor called ! " << "use = " << ptr->use << endl;
	}

	// ���ƹ��캯�������Ƴ�Ա����ʹ�ü�����1  
	HasPtr(const HasPtr& orig) : ptr(orig.ptr), val(orig.val)
	{
		++ptr->use;
		cout << "HasPtr copy constructor called ! " << "use = " << ptr->use << endl;
	}

	// ��ֵ������  
	HasPtr& operator=(const HasPtr&);

	// �����������������Ϊ0����ɾ��U_Ptr����  
	~HasPtr()
	{
		cout << "HasPtr distructor called ! " << "use = " << ptr->use << endl;
		if (--ptr->use == 0)
			delete ptr;
	}

	// ��ȡ���ݳ�Ա  
	int *get_ptr() const
	{
		return ptr->ip;
	}
	int get_int() const
	{
		return val;
	}

	// �޸����ݳ�Ա  
	void set_ptr(int *p) const
	{
		ptr->ip = p;
	}
	void set_int(int i)
	{
		val = i;
	}

	// ���ػ��޸Ļ���int����  
	int get_ptr_val() const
	{
		return *ptr->ip;
	}
	void set_ptr_val(int i)
	{
		*ptr->ip = i;
	}
private:
	U_Ptr *ptr;   //ָ��ʹ�ü�����U_Ptr  
	int val;
};
HasPtr& HasPtr::operator = (const HasPtr &rhs)  //ע�⣬���︳ֵ�������ڼ�������������ʹ�ü���֮ǰʹrhs��ʹ�ü�����1���Ӷ���ֹ���Ҹ�ֵ  
{
	// �����Ҳ������е�ʹ�ü���  
	++rhs.ptr->use;
	// ��������������ʹ�ü�����1�����ö����ʹ�ü�������0����ɾ���ö���  
	if (--ptr->use == 0)
		delete ptr;
	ptr = rhs.ptr;   // ����U_Ptrָ��  
	val = rhs.val;   // ����int��Ա  
	return *this;
}

//int main(void)
//{
//	int *pi = new int(42);
//	HasPtr *hpa = new HasPtr(pi, 100);    // ���캯��  
//	HasPtr *hpb = new HasPtr(*hpa);     // �������캯��  
//	HasPtr *hpc = new HasPtr(*hpb);     // �������캯��  
//	HasPtr hpd = *hpa;     // �������캯��  
//
//	cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
//	hpc->set_ptr_val(10000);
//	cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
//	hpd.set_ptr_val(10);
//	cout << hpa->get_ptr_val() << " " << hpb->get_ptr_val() << endl;
//	delete hpa;
//	delete hpb;
//	delete hpc;
//	cout << hpd.get_ptr_val() << endl;
//	return 0;
//}
