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
	Rank find(T const& e) const { return find(e, 0, _size); }//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi)const;//无序向量区间查找
	Rank search(T const& e)const //有序向量整体查找
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//有序向量区间查找
	//可写访问接口
	T& operator[](Rank r)const;//重载下标操作符，可以类似于数组形式引用各元素
	Vector<T>& operator =(Vector<T> const&);//重载赋值操作符，以便直接克隆向量
	T remove(Rank r);//删除秩为r的元素
	int remove(Rank lo, Rank hi);//删除秩在区间【lo,hi)之内的元素
	Rank insert(Rank r, T const& e);// 插入元素
	//Rank insert(T const& e) { return  insert(_size, e); }//默认作为末元素插入
	void sort(Rank lo, Rank hi);//对[lo,ho)排序
	void unsort(Rank lo, Rank hi);//对[lo,hi)置乱
	int deduplicate();//无序去重
	int uniquify();//有序去重
//遍历
	void traverse(void(*)(T&));//遍历（使用函数指针，只读或局部性修改)
	template<typename VST>void traverse(VST&);//遍历（使用函数对象，可全局性修改)
	void print();

};//Vector



template<typename T>//元素类型
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)//以数组区间A[lo,hi)为蓝本复制向量
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi) { _elem[_size++] = A[lo++]; }
}

template<typename T>
void Vector<T>::expand()//扩容
{
	if (_size < _capacity)return;//容量没有满的时候，不扩容
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;//容量没有达到最小值，直接给最小值
	T* OldData = _elem;
	_elem = new T[_capacity << 1];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = OldData[i];
	}
	delete[]OldData;

}
template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)return;
	if (_size << 2 > _capacity)return;
	T* oldElem = _elem;
	_elem = new T[_capacity >> 1];
	for (int i = 0; i < _size; i++)_elem[i] = oldElem[i];
	delete[] oldElem;
}

template<typename T>
T& Vector<T>::operator[](Rank r)const//重载下标运算符
{
	if (r > _size)throw "上溢";
	if (r < DEFAULT_CAPACITY)throw"下溢";
	return _elem[r];
}
template<typename T>
void permute(Vector<T>& V)
{
	for (int i = V.size; i > 0; i--)
	{
		swap(V[i - 1], V[rand() % i]);
	}
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)//(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (Rank i = hi - lo; i > 0; i--)
	{
		swap(V[i - 1], V[rand() % i]);
	}
}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }//less than
template <typename T>static bool lt(T& a, T& b) { return a < b; }//less than
template <typename T>static bool eq(T* a, T* b) { return eq(*a, *b); }//equal
template<typename T>static bool eq(T& a, T& b) { return a == b; }//eqaul

template <typename T >
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const
{
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
	if (_size = _capacity)
		expand();
	for (int i = _size; i > r; i--)
	{
		_elem[i] = _elem[i - 1];
	}
	_elem[r] = e;
	_size++;
	return r;
}
template<typename T>
void Vector<T>::print()
{
	for (IMG_WORD i = 0; i < this->_size; i++)
	{
		cout << this->_elem[i] << endl;
	}
	cout << "\n" << endl;

}

template<typename T>
int Vector<T>::remove(int lo, int hi)
{
	if (lo == hi)return -1;
	while (hi < _size)_elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi - lo;

}

template<typename T>
T Vector<T>::remove(Rank r)
{
	if (r >= _size)return -1;
	T e = _elem[r];
	Rank b = r + 1;
	while (r < _size - 1)_elem[r++] = _elem[b++];
	_size--;
	shrink();
	return e;

}

template<typename T>
Rank Vector<T>::deduplicate()
{
	Rank oldSize = _size;
	Rank i = 1;
	while (i < _size)
	{
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	}
	return _size - oldSize;
}
//int Vector<T>::deduplicate()
//{
//	Rank oldSize = _size;
//	for (Rank i = 0; i < _size; i++)
//	{
//		for (Rank j = i+1; j < _size; j++)
//		{
//			if (eq(_elem[i], _elem[j]))
//			{
//				remove(j);
//			}
//				
//		}
//	}
//	return oldSize-_size;
//}
template<typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)visit(_elem[i]);
}

template<typename T> template<typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)visit(_elem[i]);
}

template<typename T>
struct Increase
{
	virtual void operator()(T& e) { e++; }
};
template<typename T>
void increase(Vector<T>& V)
{
	V.traverse(Increase<T>());
}

template<typename T>
int Vector<T>::disordeered() const//判断向量是否已经排序
{
	int n = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i] < _elem[i - 1])
			n++;
	}
	return n;
}

//template<typename T>
//int Vector<T>::uniquify()//有序去重
//{
//	int n = 0;
//	int _oldsize = _size;
//	while (n < _size - 1)
//	{
//		if (_elem[n] != _elem[n + 1]) n++;
//		else  remove(n + 1);
//
//	}
//	return _oldsize - _size;
//}

template<typename T>
int Vector<T>::uniquify()//有序去重
{
	Rank i = 0, j = 0;
	while (++j < _size)
	{
		if (_elem[i] != _elem[j])_elem[++i] = _elem[j];
	}
	_size = ++i; shrink();
	return j - i;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const//有序向量区间查找
{
	return(rand() % 2) ? binsearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template <typename T>static Rank binserach(T* A, T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{
		Rank mi = (hi + lo) / 2;
	}
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2)return;
	Rank mi = (hi - lo) / 2;
	mergeSort(lo, mi); mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	Rank lb = mi - lo;
	Rank lc = hi - mi;

	T* B = new T[lb];
	T* C = mi + _elem;
	T* A = lo + _elem;
	for (Rank i = 0; i < lb; i++)B[i] = A[i++];
	for (Rank j, k, l = 0; (j < lb || k < lc);)
	{
		if (B[j] <= C[k])A[l++] = B[j++];
		else A[l++] = C[k++];
	}
	delete []B;
}



