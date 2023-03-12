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


