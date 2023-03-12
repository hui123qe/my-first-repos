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
	Rank find(T const& e) const { return find(e, 0, _size); }//���������������
	Rank find(T const& e, Rank lo, Rank hi)const;//���������������
	Rank search(T const& e)const //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//���������������
	//��д���ʽӿ�
	T& operator[](Rank r)const;//�����±������������������������ʽ���ø�Ԫ��
	Vector<T>& operator =(Vector<T> const&);//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	T remove(Rank r);//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);//ɾ���������䡾lo,hi)֮�ڵ�Ԫ��
	Rank insert(Rank r, T const& e);// ����Ԫ��
	//Rank insert(T const& e) { return  insert(_size, e); }//Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi);//��[lo,ho)����
	void unsort(Rank lo, Rank hi);//��[lo,hi)����
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
//����
	void traverse(void(*)(T&));//������ʹ�ú���ָ�룬ֻ����ֲ����޸�)
	template<typename VST>void traverse(VST&);//������ʹ�ú������󣬿�ȫ�����޸�)
	void print();

};//Vector



template<typename T>//Ԫ������
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)//����������A[lo,hi)Ϊ������������
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi) { _elem[_size++] = A[lo++]; }
}

template<typename T>
void Vector<T>::expand()//����
{
	if (_size < _capacity)return;//����û������ʱ�򣬲�����
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;//����û�дﵽ��Сֵ��ֱ�Ӹ���Сֵ
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
T& Vector<T>::operator[](Rank r)const//�����±������
{
	if (r > _size)throw "����";
	if (r < DEFAULT_CAPACITY)throw"����";
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
int Vector<T>::disordeered() const//�ж������Ƿ��Ѿ�����
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
//int Vector<T>::uniquify()//����ȥ��
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
int Vector<T>::uniquify()//����ȥ��
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
Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const//���������������
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



