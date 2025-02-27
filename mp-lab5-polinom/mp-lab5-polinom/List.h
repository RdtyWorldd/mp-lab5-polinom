#pragma once
#include <iostream>

template <typename T>
struct Node
{
  T val;
  Node<T>* pNext;
};

template <typename T>
class List
{
protected:
  Node<T>* pFirst;
  Node<T>* pLast;

  Node<T>* pCurr, *pPrev;
  size_t size;
public:
  List();
  List(const List<T>& list);
  List(std::initializer_list<T> l);
  List<T>& operator= (const List<T>& list);
  ~List();
  
  void pushBack(T val);
  void pushFront(T val);
  void removeFirst();
  void removeLast();

  void add(int id, T val);
  T& get(int id);
  void remove(int id);
  T& operator[](int id);
  void clear();

  bool isEmpty() const;
  size_t getSize() const;

  void Reset();
  void GoNext();
  bool IsEnd();

  //перед pCurr, двигает pPrev

  void insertCurr(T val);
  void removeCurr();

  bool operator== (const List<T>& list) const;
  bool operator!= (const List<T>& list) const;

  friend std::ostream& operator<< (std::ostream& out, const List<T>& list)
  {
	  Node<T>* tmp = list.pFirst;
    while(tmp != nullptr)
    {
      out << tmp->val << " ";
    }
    out << std::endl;
    return out;
  }

  friend std::istream& operator>> (std::istream& in, const List<T>& list)
  {
	  return in;
  }
};

template<typename T>
inline List<T>::List()
{
  pFirst = nullptr;
  pLast == nullptr;
  pCurr = nullptr;
  pPrev = nullptr;
  size = 0;
}

template<typename T>
inline List<T>::List(std::initializer_list<T> list)
{
  Node<T>* tmp = new Node<T> { list[list.size -1], nullptr };
  pLast = tmp;
  for(int i = list.size-2; i >= 0; i--)
  {
    Node<T>* add = new Node<T> { list[i], tmp }; 
    tmp = add;
  }
  pFirst = tmp;
}

template<typename T>
inline List<T>::List(const List<T>& list)
{
  clear();

  size = list.size;
  if (list.pFirst == nullptr) {
	pFirst = nullptr;
	pLast = nullptr;
	return;
  }

  Node<T>* tmp = list.pFirst;
  pFirst = new Node<T>{ tmp->val, nullptr };
  Node<T>* previous = pFirst;

  tmp = tmp->pNext;
  while (tmp != nullptr) {
	Node<T>* node = new Node<T>{ tmp->val, nullptr };
	previous->pNext = node;

	previous = node; //previous = previous -> pNext;
	tmp = tmp->pNext;
  }
  pLast = previous;
}

template<typename T>
inline List<T>& List<T>::operator=(const List<T>& list)
{
  if (this != &list)
  {
	clear();

	size = list.size;
	if (list.pFirst == nullptr) {
	  pFirst = nullptr;
	  pLast = nullptr;
	  return *this;
	}

	Node<T>* tmp = list.pFirst;
	pFirst = new Node<T>{ tmp->val, nullptr };
	Node<T>* previous = pFirst;

	tmp = tmp->pNext;
	while (tmp != nullptr) {
	  Node<T>* node = new Node<T>{ tmp->val, nullptr };
	  previous->pNext = node;

	  previous = node; //previous = previous -> pNext;
	  tmp = tmp->pNext;
	}
	pLast = previous;
  }
  return *this;
}

template<typename T>
inline List<T>::~List()
{
  clear();
  delete pFirst;
  delete pLast;
  delete pCurr;
  delete pPrev;
}

template<typename T>
inline void List<T>::pushBack(T val)
{
  Node<T>* tmp = new Node<T>{ val, nullptr };
  if (pFirst == nullptr)
  {
	pFirst = pLast = tmp;
  }
  else
  {
	pLast->pNext = tmp;
	pLast = pLast->pNext;
  }
  size++;
}

template<typename T>
inline void List<T>::pushFront(T val)
{
  Node<T>* tmp = new Node<T>{ val, pFirst };
  pFirst = tmp;
  if (pLast == nullptr)
	pLast = pFirst;

  size++;
}

template <typename T>
inline void List<T>::removeFirst()
{
  if(pFirst == nullptr)
  {
    throw std::exception("list is empty");
  }

  if(pFirst == pLast)
  {
    delete pFirst;
    pFirst = nullptr;
    pLast = nullptr;
  }
  else 
  {
    Node<T>* tmp = pFirst;
    pFirst = pFirst->pNext;
    delete tmp;
  }
  size--;
}

template <typename T>
inline void List<T>::removeLast()
{
  if(pLast == nullptr)
  {
    throw std::exception("list is empy");
  }
    
  if(pFirst == pLast)
  {
    delete pFirst;
    pFirst = nullptr;
    pLast = nullptr;
  }
  else
  {
    Node<T>* tmp = pFirst;
    while(tmp->pNext != pLast)
    {
      tmp = tmp->pNext;
    }
    tmp->pNext = nullptr;
    delete pLast;
    pLast = tmp;
  }
  size--;
}

template<typename T>
inline void List<T>::add(int id, T val)
{
  if (id < 0 || id > size)
	throw std::exception("index is out of range");
  if (id == 0) {
	pushFront(val);
	return;
  }
  if (id == size) {
	pushBack(val);
	return;
  }

  Node<T>* p = pFirst;
  for (int i = 0; i < id - 1; i++)
	p = p->pNext;

  Node<T>* tmp = new Node<T>{ val, p->pNext };
  p->pNext = tmp;

  size++;
}

template<typename T>
inline T& List<T>::get(int id)
{
  if (id < 0 || id >= size)
	throw std::exception("index is out of range");

  Node<T>* p = pFirst;
  for (int i = 0; i < id; i++)
	  p = p->pNext;

  return p->val;
}

template<typename T>
inline void List<T>::remove(int id)
{
  if (id < 0 || id >= size)
	throw std::exception("index is out of range");

  Node<T>* tmp = pFirst;
  if (id == 0)
  {
	  pFirst = pFirst->pNext;
  }
  else
  {
    Node<T>* prev = tmp;
    for (int i = 0; i < id; i++)
    {
      prev = tmp;
      tmp = tmp->pNext;
    }
    prev->pNext = tmp->pNext;
    if (id == size - 1)	pLast = prev;
  }
  size--;
  delete tmp;
}

template<typename T>
inline T& List<T>::operator[](int id)
{
  return get(id);
}

template<typename T>
inline void List<T>::clear()
{
  while (pFirst != nullptr)
  {
	Node<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;
  }
  pLast = nullptr;
  size = 0;
}

template<typename T>
inline bool List<T>::isEmpty() const
{
  return size == 0;
}

template<typename T>
inline size_t List<T>::getSize() const
{
  return size;
}

template <typename T>
inline void List<T>::insertCurr(T val)
{
  if(pCurr == pFirst)
  {
    pushFront(val);
    pPrev = pFirst;
  }
  else if(pPrev == pLast)
  {
    pushBack(val);
    pPrev = pLast;
  }
  else 
  {
    Node<T>* tmp = new Node<T>{val, pCurr};
    pPrev->pNext = tmp;
    pPrev = tmp;
    size++;
  }
}

template <typename T>
inline void List<T>::removeCurr()
{
  if(pCurr == pFirst)
  {
    removeFirst();
    pCurr = pFirst;
    return;
  }

  if (pCurr != nullptr)
  {
    Node<T>* tmp = pCurr;
    pCurr = pCurr->pNext;
    delete tmp;
    pPrev->pNext = pCurr;
    if(pCurr == nullptr)
    {
      pLast = pPrev;
    }
    size --;
  }
}

template <typename T>
inline bool List<T>::operator==(const List<T> &list) const
{
  if (pFirst == list.pFirst)
	return true;

  if (size != list.size)
	return false;

  Node<T>* firstS = pFirst;
  Node<T>* secondS = list.pFirst;

  while (firstS != nullptr && secondS != nullptr)
  {
	if (firstS->val != secondS->val)
	  return false;
	firstS = firstS->pNext;
	secondS = secondS->pNext;
  }

  return true;
}

template<typename T>
inline bool List<T>::operator!=(const List<T>& list) const
{
  return !((*this) == list);
}

template<typename T>
inline void List<T>::Reset()
{
  pCurr = pFirst;
  pPrev = nullptr;
}

template<typename T>
inline void List<T>::GoNext()
{
  pPrev = pCurr;
  pCurr = pCurr->pNext;
}

template<typename T>
inline bool List<T>::IsEnd()
{
  return pLast == pPrev;
}