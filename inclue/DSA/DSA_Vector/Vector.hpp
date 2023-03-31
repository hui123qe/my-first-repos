#pragma once


typedef int IMG_WORD;
typedef float IMG_REAL;

typedef int Rank;//��
#define DEFAULT_CAPACITY 3 //Ĭ�ϵĳ�ʼ����

template<typename T>
class Vector
{
protected:
	Rank _size; int _capacity; T* _elem;//ģ�� ���� ������
	void copyFrom(T const* A, Rank lo, Rank hi);//������������A[lo,hi]
	void expand();//expand if the space is insufficient
	void shrink();//shrink the space;
	bool bubble(Rank lo, Rank hi);//ɨ�뽻��
	void bubbleSort(Rank lo, Rank hi);//���������㷨
	void selectionSort(Rank lo, Rank hi);//ѡ�������㷨 
	void merge(Rank lo, Rank mi, Rank hi);//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);//�鲢�����㷨
	Rank qartition(Rank lo, Rank hi);//��㹹���㷨
	void quickSort(Rank lo, Rank hi);//���������㷨
	void heapSort(Rank lo, Rank hi);//�������㷨
public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);//s<=c
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//�������帴��
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//����
	Vector(Vector<T> const& const V) {
		copyFrom(V._elem, 0, V._size);
	}//�������帴��
	Vector(Vector<T>const& V, Rank lo, Rank hi) {
		copyFrom(V._elem, lo, hi);
	}//����
	//��������
	~Vector() {
		delete[] _elem;
	}
	//ֻ�����ʽӿ�
	Rank size()const { return _size; }//��ģ
	bool empty() const { return !_size; }; //�п�
	int disordeered() const;//�ж������Ƿ��Ѿ�����
	Rank find(T const& e) { return find(e, 0, _size); }//���������������
	Rank find(T const& e, Rank lo, Rank hi);//���������������
	Rank search(T const& e)const //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi);//���������������
	//��д���ʽӿ�
	T operator[](Rank r);//�����±������������������������ʽ���ø�Ԫ��
	Vector<T>& operator =(Vector<T> const&);//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	T remove(Rank r);//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);//ɾ���������䡾lo,hi)֮�ڵ�Ԫ��
	Rank insert(Rank const r, T const& e);// ����Ԫ��
	Rank insert(T const& e) { return  insert(_size, e); }//Ĭ����ΪĩԪ�ز���
	bool isSort();
	void sort(Rank lo, Rank hi);//��[lo,ho)����
	void unsort(Rank lo, Rank hi);//��[lo,hi)����
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
//����
	void traverse(void(*)(T&));//������ʹ�ú���ָ�룬ֻ����ֲ����޸�)
	template<typename VST>void traverse(VST&);//������ʹ�ú������󣬿�ȫ�����޸�)
	void print();

};//Vector

template<typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = (hi - lo) * 2];
	_size = 0;
	while (lo<hi)
	{
		_elem[_size++] = A[lo++];
	}
}
template<typename T>
void  Vector<T>::expand()
{
	if (_size > _capacity / 2)
	{
		T *new_elem = new T[_capacity * 2];
		for (int i = 0; i < _size; i++)
		{
			new_elem[i] = _elem[i];
		}
		delete _elem;
		_elem = new_elem;
		_capacity *= 2;
	}
	else return;
}
template<typename T>
Rank Vector<T>::insert(Rank const r, T const& e)
{
	int ho = _size;
	while (ho > r)
	{
		_elem[ho--] = _elem[ho-1];
	}
	_elem[r] = e;
	_size++;
	return  _size;
}

template<typename T>
void Vector<T>::print()
{
	for (int i = 0; i < _size; i++)
	{
		cout << _elem[i]<<" ";
	}
	cout << endl;

}

template<typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)
{
	while (lo++ < hi)
	{
		if (_elem[lo] == e)return lo;
	}
	return 0;
}

template<typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)
{
	int num = 0;
	while (lo++ < hi)
	{
		if (_elem[lo] == e)num++;
	}
	return num;
}
template<typename T>
T Vector<T>::operator[](Rank r)
{
	if (r > _size)return 0;
	return _elem[r];
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& a)
{
	if (this->_capacity < a._capacity)
	{
		T *_elem_new = new T[a._capacity];
		delete _elem;
		_elem = _elem_new;
		_size = a._size;
	}
	for (int i = 0; i <a._size; i++)
	{
		_elem[i] = a._elem[i];
	}
	return *this;
}
template<typename T>
T Vector<T>::remove(Rank r)
{
	int a = _elem[r - 1];
	while (r < _size)
	{
		_elem[r-1] = _elem[r++];
	}
	_size--;
	return a;
}
template<typename T>
int  Vector<T>::remove(Rank lo, Rank hi)
{
	int _size_new = _size - (hi - lo);
	while (_size_new<_size)
	{
		_elem[lo++] = _elem[hi++];
		_size--;
	}
	return _size;
}

template<typename T>
bool  Vector<T>::isSort()
{
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i] < _elem[i - 1])return false;
	}
	return true;
}

template<typename T>
void Vector<T>::shrink()//shrink the space;
{
	if(_size>_capacity/2)
}