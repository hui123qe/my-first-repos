#pragma once
#include<iostream>
using namespace std;
typedef int Rank;

#define ListNodePosi(T)  ListNode<T>*

template<typename T>
struct ListNode
{
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ;
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) :data(e), pred(p), succ(s) {}
	ListNodePosi(T) insertAsPred(T const&  e);//为什么取地址啊，或者传递引用
	ListNodePosi(T) insertAsSucc(T const&  e);

};



template<typename T>
class List
{
private:
	int _size; ListNodePosi(T) head; ListNodePosi(T) trailer;

protected:
	void init();
	int clear();
	void CopyNodes(ListNodePosi(T), int);
	void merge(ListNodePosi(T) p, int m, List<T>& L, ListNodePosi(T) q, int n);
	void MergeSort(ListNodePosi(T)&, int);
	void SelectSort(ListNodePosi(T) p, int n);
	void InsertSort(ListNodePosi(T), int);
public:
	List() { init(); }
	List(List<T> const& L);//整体复制列表L
	List(List<T> const& L, Rank r, int n);//整体复制列表L中的第r项的n个
	List(ListNodePosi(T)p, int n);
	~List();
	//只读访问接口
	Rank Size()const { return _size; }
	bool empty()const { return _size <= 0; }
	T& operator[](Rank t)const;//重载，支持循环访问
	ListNodePosi(T) first()const { return head->succ; }
	ListNodePosi(T) last()const {
		return trailer->pred;
	}
	bool vaild(ListNodePosi(T) p)//判断位置是否对外合法
	{
		return p && (head != p) && (trailer != p);//将头尾节点等同于NULL
	}
	int disordered()const;//判断列表是否已经排序
	ListNodePosi(T) find(T const &a)const//无序列表查找
	{
		return find(a, _size, trailer);
	}
	ListNodePosi(T) find(T const &a, int n, ListNodePosi(T) const p)const;//无序区间查找
	ListNodePosi(T) Search(T const &e);//有序列表查找
	ListNodePosi(T) Search(T const &e, int n, ListNodePosi(T) p)const; //在有序列表p的n个前驱中找到不大于e的最后者
	ListNodePosi(T) SearchMax(ListNodePosi(T) const p, int n);//从p之后的n里面选出最大者
	ListNodePosi(T) SearchMax() {//选出整体最大者
		return SearchMax(head->succ, _size);
	}
	//可写访问接口
	ListNodePosi(T) InsertAsFirst(T const e);//将e当作首节点插入
	ListNodePosi(T) InsertAsLast(T const e);//将e当作尾节点插入
	ListNodePosi(T) insertA(ListNodePosi(T) const p, T const e);//将e当作p的后续插入
	ListNodePosi(T) insertB(ListNodePosi(T) const p, T const e);//将e当作p的前驱插入
	T remove(ListNodePosi(T) const p);//删除节点p，返回删除节点的数据
	void merge(List<T>& L) { return merge(first(), size, L, L.first(), L._size); }//全表归并
	void sort(ListNodePosi(T) p, int n);//列表区间排序
	void sort() { return sort(head->succ, _size); }//列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置（习题）					//遍历
	void traverse(void(*vist) (T&)); //遍历各节点,依次实施指定操作(函数指针，只读或局部修改)
	template <typename VST>
	void traverse(VST&); // 遍历，依次实斲visit操作（函数对象，可全尿性修改）	void print1();

	void print1()
	{
		ListNodePosi(T) temp = head->succ;
		while (temp != trailer)
		{
			cout << temp->data << "\t";
			temp = temp->succ;
		}
		cout << endl;
	}

};


template<typename T>
void List<T>::init()
{
	head = new ListNode<T>;
	trailer = new ListNode<T>;
	head->pred = NULL;
	head->succ = trailer;
	trailer->pred = head;
	trailer->succ = NULL;
	_size = 0;


}
template<typename T>

T& List<T>::operator[](Rank t)const//重载，支持循环访问
{
	ListNodePosi(T) temp = head->succ;
	for (int i = 0; i < t; i++)
	{
		temp = temp->succ;
	}
	return temp->data;
}
template<typename T>
int List<T>::clear()
{
	int tempSize = _size;
	while (tempSize > 0)remove(head->succ);
	return tempSize;
}
template<typename T>
T List<T>::remove(ListNodePosi(T) const p)//删除节点p，返回删除节点的数据
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;

}

template<typename T>
List<T>::~List()
{
	clear();
	delete head;
	delete trailer;
}

template<typename T>
ListNodePosi(T) List<T>::InsertAsFirst(T const e)//将e当作首节点插入
{
	ListNodePosi(T) temp = new ListNode<T>;
	temp->succ = head->succ;
	head->succ->pred = temp;
	head->succ = temp;
	temp->pred = head;
	temp->data = e;
	_size++;
	return temp;
}

template<typename T>
ListNodePosi(T) List<T>::InsertAsLast(T const e)//将e当作尾节点插入
{
	ListNodePosi(T) temp = new ListNode<T>;
	temp->data = e;
	temp->pred = trailer->pred;
	temp->succ = trailer;
	trailer->pred->succ = temp;
	trailer->pred = temp;
	_size++;
	return temp;
}


template<typename T>
ListNodePosi(T) List<T>::find(T const &a, int n, ListNodePosi(T) const p)const//无序区间查找
{
	ListNodePosi(T) temp = p->pred;
	while (temp != head)
	{
		if (temp->data == a)	break;
		temp = temp->pred;
	}
	return temp != head ? temp : NULL;
}

template<typename T>
int List<T>::deduplicate() //无序去重
{
	ListNodePosi(T) temp = head->succ;//第一个位置
	ListNodePosi(T) temp1 = temp;
	ListNodePosi(T) temp2;
	int a = 0;
	while (temp != trailer->pred)
	{

		temp1 = temp->succ;
		while (temp1 != trailer)
		{
			if (temp->data == temp1->data)
			{
				temp2 = temp1->succ;
				a = temp1->data;
				remove(temp1);
				temp1 = temp2;
			}
			else
			{
				temp1 = temp1->succ;
			}

		}

		temp = temp->succ;

	}
	return a;

}

template<typename T>
ListNodePosi(T) List<T>::Search(T const &e)//有序列表查找
{
	return Search(e, _size, trailer);

}
template<typename T>
ListNodePosi(T) List<T>::Search(T const &e, int n, ListNodePosi(T) p)const//在p的n个前驱中，找到等于e的最后者
{
	ListNodePosi(T) temp = NULL;

	while (n-- > 0)
	{
		if (e == p->data)temp = p;
		p = p->pred;

	}

	return temp;
}

template<typename T>
int List<T>::disordered() const
{
	int n = 0;
	ListNodePosi(T) temp = head->succ;
	for (int i = 0; i < _size; i++)
	{
		if (temp->data > temp->succ->data)
		{
			n++;
		}
		temp = temp->succ;
	}
	return  n;
}

template<typename T>
ListNodePosi(T) List<T>::SearchMax(ListNodePosi(T) const p, int n)
{
	ListNodePosi(T) temp;
	temp = p;
	ListNodePosi(T) Max;
	Max = p;
	while (n-- > 0)
	{
		temp = temp->succ;
		if (Max->data > temp->data)Max = temp;
	}
	return Max;
}
template<typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) const p, T const e)//将e当作p的后续插入
{
	return p->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const&  e)//将e紧随当前节点之后插入到当前的列表中（没有哨兵尾节点trailer）
{
	ListNodePosi(T) p = ListNode(e, this, succ);
	succ->pred = p; succ = p;
	return p;

}

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const&  e)//将e紧随当前节点之后插入到当前的列表中（没有哨兵尾节点trailer）
{
	ListNodePosi(T) p = ListNode(e, pred, this);
	pred->succ = p; pred = p;
	return p;

}
template<typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) const p, T const e)//将e当作p的后续插入
{
	return p->insertAsPred(e);
}
template<typename T>
void List<T>::sort(ListNodePosi(T) p, int n)//列表区间排序
{
	switch (rand() % 3)
	{
	case 1:
		insertSort(p, n);
		break;
	case 2:
		selectSort(p, n);
		break;
	case 3:
		MergeSort(p, n);
	default:
		MergeSort(p, n);
		break;
	}
}
template<typename T>
int List<T>::uniquify() //有序去重
{
	ListNodePosi(T) temp = head->succ;
	ListNodePosi(T) temp1 = NULL;
	while (temp != trailer)
	{
		temp = temp->succ;
		if (temp->data == temp->pred->data)
		{
			temp1 = temp->pred;
			remove(temp);
			temp = temp1;
		}
	}
	return _size;
}

template<typename T>
void List<T>::reverse()
{
	ListNodePosi(T) temp1 = head->succ;
	ListNodePosi(T) temp2 = NULL;
	for (int i = 0; i < _size; i++)
	{
		ListNodePosi(T) temp = new ListNode<T>(temp1->data, temp1->succ, temp1->pred);
		temp2 = temp1;
		temp1 = temp1->succ;
		delete temp2;
	}
	return;
}

//template<typename T>
//void List<T>::traverse(void(*) (T&)) //遍历各节点,依次实施指定操作(函数指针，只读或局部修改)
//{
//	return;
//}

template<typename T>
void List<T>::SelectSort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) temp1 = p;
	ListNodePosi(T) temp2 = NULL;
	ListNodePosi(T) temp3 = NULL;
	int data1;
	int i, j = 0;
	while (i++ <n)
	{
		j = i;
		while (j++<n)
		{
			temp3 = temp1->succ;
			temp2 = temp1;
			if (temp2->data < temp3->data)temp3 = temp2;
			temp2 = temp2->succ;

		}
		data1 = temp1->data;
		temp1->data = temp3->data;
		temp3->data = data1;
		temp1 = temp1->succ;
	}

}
template<typename T>
void List<T>::InsertSort(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) temp = p->succ;
	ListNodePosi(T) temp1 = NULL;
	ListNodePosi(T) temp2 = NULL;
	for (int i = 1; i < n; i++)
	{
		temp2 = temp->pred;
		while (temp->data > temp2)
		{
			temp2 = temp2->pred;
		}
		temp2->insertAsPred(temp->data);
		temp1 = temp;
		temp = temp->succ;
		delete temp1;
	}
}
//
//template<typename T>
//void List<T>::print1(ListNodePosi(T) const p)
//{
//	ListNodePosi(T) temp = p->succ;
//	while (temp != trailer)
//	{
//		cout << temp->data <<"\n"<< endl;
//		temp = temp->succ;
//	}
//}


template<typename T>
void List<T>::merge(ListNodePosi(T) p, int m, List<T>& L, ListNodePosi(T) q, int n)//merge two list
{


	ListNodePosi(T) pp = p->succ;
	while (m > 0 && n>0)
	{
		if (p->data >= q->data)
		{
			L.InsertAsLast(q);
			q = q->succ;
			n--;
		}
		if (p->data < q->data)
		{
			L.InsertAsLast(p);
			p = p->succ;
			m--;
		}
	}
	while (n > 0)
	{
		L.InsertAsLast(q);
		q = q->succ;
		n--;
	}
	while (m > 0)
	{
		L.InsertAsLast(p);
		p = p->succ;
		m--;
	}
}


template<typename T>
void List<T>::MergeSort(ListNodePosi(T)& p, int n)
{
	if (n < 2)return;
	int m = n >> 1;
	ListNodePosi(T) q = p;
	for (int i = 0; i < n; i++) { q = q->succ; }
	MergeSort(p, m); mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);

}

template<typename T>
void List<T>::CopyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n-- > 0) { InsertAsLast(p); p = p->succ; }
}

template<typename T>
List<T>::List(List<T> const& L)//整体复制列表L
{
	return CopyNodes(head->succ, _size);
}

template<typename T>
List<T>::List(List<T> const& L, Rank r, int n)//整体复制列表L中的第r项的n个
{
	ListNodePosi(T) temp = head;
	while (r-- > 0) { temp = temp->succ; }
	return CopyNodes(temp, n);
}

template<typename T>
List<T>::List(ListNodePosi(T)p, int n)
{
	return CopyNodes(p, n);
}

template<typename T>
void List<T>::traverse(void(*visit) (T&))
{

	for (ListNodePosi(T) p = head->succ; p != trailer; p = p->succ) { visit(p->data); }
}

template<typename T>
template <typename VST>
void  List<T>::traverse(VST&)
{
	for (ListNodePosi(T) p = head->succ; p != trailer; p = p->succ) { visit(p->data); }
}
