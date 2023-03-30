#pragma once


typedef int IMG_WORD;
typedef float IMG_REAL;

typedef int Rank;//秩
#define DEFAULT_CAPACITY 3 //默认的初始容量

template<typename T>
class Vector
{
protected:
	Rank _size; int _capacity; T* _elem;//模板 容量 数据区
	void copyFrom(T const* A, Rank lo, Rank hi);//复制数组区间A[lo,hi]
	void expand();//expand if the space is insufficient
	void shrink();//shrink the space;
	bool bubble(Rank lo, Rank hi);//扫码交换
	void bubbleSort(Rank lo, Rank hi);//气泡排序算法
	void selectionSort(Rank lo, Rank hi);//选择排序算法 
	void merge(Rank lo, Rank mi, Rank hi);//归并算法
	void mergeSort(Rank lo, Rank hi);//归并排序算法
	Rank qartition(Rank lo, Rank hi);//轴点构造算法
	void quickSort(Rank lo, Rank hi);//快速排序算法
	void heapSort(Rank lo, Rank hi);//堆排序算法
public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量为c，规模为s，所有元素初始为v
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);//s<=c
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//数组整体复制
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//区间
	Vector(Vector<T> const& const V) {
		copyFrom(V._elem, 0, V._size);
	}//向量整体复制
	Vector(Vector<T>const& V, Rank lo, Rank hi) {
		copyFrom(V._elem, lo, hi);
	}//区间
	//析构函数
	~Vector() {
		delete[] _elem;
	}
	//只读访问接口
	Rank size()const { return _size; }//规模
	bool empty() const { return !_size; }; //判空
	int disordeered() const;//判断向量是否已经排序
	Rank find(T const& e) { return find(e, 0, _size); }//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi);//无序向量区间查找
	Rank search(T const& e)const //有序向量整体查找
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi);//有序向量区间查找
	//可写访问接口
	T operator[](Rank r);//重载下标操作符，可以类似于数组形式引用各元素
	Vector<T>& operator =(Vector<T> const&);//重载赋值操作符，以便直接克隆向量
	T remove(Rank r);//删除秩为r的元素
	int remove(Rank lo, Rank hi);//删除秩在区间【lo,hi)之内的元素
	Rank insert(Rank const r, T const& e);// 插入元素
	Rank insert(T const& e) { return  insert(_size, e); }//默认作为末元素插入
	bool isSort();
	void sort(Rank lo, Rank hi);//对[lo,ho)排序
	void unsort(Rank lo, Rank hi);//对[lo,hi)置乱
	int deduplicate();//无序去重
	int uniquify();//有序去重
//遍历
	void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部性修改)
	template<typename VST>void traverse(VST&);//遍历（使用函数对象，可全局性修改)
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