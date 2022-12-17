#pragma once
#include <iostream>
#include <string>

/*
Реализация TList:
+ |  1) Конструктор
+ |  2) Конструктор копирования
+ |  3) Конструктор перемещения
+ |  4) Оператор присваивания
+ |  5) Оператор присваивания перемещением
+ |  6) Вставка в начало
+ |  7) Удаление из начала
+ |  8) Вставка в конец
+ |  9) Удаление из конца
+ | 10) Вставка в любое место списка
+ | 11) Удаление из любого места списка
+ | 12) Оператор индексации
+ | 13) Получение значения размера списка
+ | 14) Проверка на пустоту списка
+ | 15) Деструктор
+ | 16) Чистка списка
+ | 17) swap
+ | 18) Вставка по возрастанию
+ | 19) Оператор ввода
+ | 20) Оператор вывода
+ | 21) Метод считывания с потока
*/

template <class TType>
class TList
{
private:
  struct Node
  {
    TType data;
    Node* pNext;
    Node(const TType _data = {}, Node* _pNext = nullptr) : data(_data), pNext(_pNext) {}
  };

  Node* pFirst; // Указатель на первый элемент списка
  Node* pLast; // Указатель на послений элемент списка
  int size; // Размер списка

public:
  friend void swap(TList<TType>& lhs, TList<TType>& rhs)
  {
    std::swap(lhs.pFirst, rhs.pFirst);
    std::swap(lhs.pLast, rhs.pLast);
    std::swap(lhs.size, rhs.size);
  }

  friend std::ostream& operator<<(std::ostream& os, const TList<TType>& list)
  {
    if (!list.is_empty())
    {
      Node* tmp = list.pFirst;
      while (tmp != nullptr)
      {
        os << tmp->data << ' ';
        tmp = tmp->pNext;
      }
    }
    else
    {
      os << '0';
    }
    return os;
  }

  std::istream& ReadFromStream(std::istream& is)
  {
    TType tmpdata;
    is >> tmpdata;
    if (is.eof())
      return is;
    push_back(tmpdata);
    return is;
  }

  friend std::istream& operator>>(std::istream& is, TList<TType>& list)
  {
    list.clear();
    return list.ReadFromStream(is);
  }

  TList() : pFirst(nullptr), pLast(nullptr), size(0) {} // Конструктор

  ~TList() { clear(); } // Деструктор

  TList(const TList& list) // Конструктор копирования
  {
    pFirst = pLast = nullptr;
    size = 0;
    Node* tmp = list.pFirst;
    while (tmp != nullptr)
    {
      insert_last(tmp->data);
      tmp = tmp->pNext;
    }
  }

  TList(TList&& list) noexcept // Конструктор перемещения
  {
    pFirst = list.pFirst;
    pLast = list.pLast;
    list.pFirst = nullptr;
    list.pLast = nullptr;
    size = list.size;
  }

  TList& operator=(const TList& list) // Оператор присваивания
  {
    if (this == &list)
      return *this;
    TList tmp(list);
    swap(tmp, *this);
    return *this;
  }

  TList& operator=(TList&& list) noexcept // Оператор присваивания перемещением
  {
    if (this == &list)
      return *this;
    clear();
    pFirst = list.pFirst;
    pLast = list.pLast;
    list.pFirst = nullptr;
    list.pLast = nullptr;
    size = list.size;
  }

  int get_size() const noexcept { return size; } // Получение значения размера списка

  bool is_empty() const noexcept { return size == 0; } // Проверка на пустоту

  void insert_first(const TType elem) // Вставка элемента в начало списка
  {
    Node* tmp = new Node(elem); // pNext == nullptr
    if (is_empty())
    {
      pFirst = pLast = tmp;
    }
    else
    {
      tmp->pNext = pFirst;
      pFirst = tmp;
    }
    size++;
  }

  void delete_first() noexcept // Удаление первого элемента, контроль использования за программистом
  {
    Node* tmp = pFirst;
    pFirst = pFirst->pNext;
    delete tmp;
    size--;
    if (pFirst == nullptr)
      pLast = nullptr;
  }

  void clear() noexcept // Чистка списка 
  {
    while (pFirst != nullptr)
      delete_first();
  }

  void insert_last(const TType elem) // Вставка элемента в конец списка
  {
    Node* tmp = new Node(elem); // pNext == nullptr
    if (is_empty())
    {
      pFirst = pLast = tmp;
    }
    else
    {
      pLast->pNext = tmp;
      pLast = tmp;
    }
    size++;
  }

  void delete_last() noexcept // Удаление последнего элемента, контроль использования за программистом
  {
    if (pFirst == pLast)
    {
      delete_first();
    }
    else
    {
      Node* tmp = pFirst;
      while (tmp->pNext != pLast)
        tmp = tmp->pNext;
      tmp->pNext = nullptr;
      delete pLast;
      pLast = tmp;
      size--;
    }
  }

  void insert_in_pos(const TType& elem, const int pos) // Вставка элемента на позицию
  {
    if (pos < 0 || pos > size)
      throw std::string("TList::insert_in_pos(TType, int) throw an exception");
    if (is_empty())
    {
      insert_first(elem);
      return;
    }
    if (pos == size)
    {
      insert_last(elem);
      return;
    }
    Node* prev = pFirst;
    for (int i = 0; i < pos - 1; i++)
      prev = prev->pNext;
    Node* NewNode = new Node(elem, prev->pNext);
    prev->pNext = NewNode;
    size++;
  }

  void delete_in_pos(const int pos) // Удаление элемента по индексу
  {
    if (pos < 0 || pos >= size || is_empty())
      throw std::string("TList::delete_in_pos(int) throw an exception");
    if (pos == 0)
    {
      delete_first();
      return;
    }
    if (pos == size - 1)
    {
      delete_last();
      return;
    }
    Node* prev = pFirst;
    for (int i = 0; i < pos - 1; i++)
      prev = prev->pNext;
    Node* tmpdel = prev->pNext;
    prev->pNext = tmpdel->pNext;
    delete tmpdel;
    size--;
  }

  void insert_in_order(const TType& elem) // Вставка элемента в отсортированный список
  {
    if (is_empty() || pFirst->data > elem)
    {
      insert_first(elem);
      return;
    }
    Node* prev = pFirst;
    for (Node* tmp = pFirst; tmp != nullptr; tmp = tmp->pNext)
    {
      if (tmp->data > elem)
        break;
      prev = tmp;
    }
    if (prev != pLast)
    {
      Node* NewNode = new Node(elem, prev->pNext);
      prev->pNext = NewNode;
      size++;
    }
    else
    {
      insert_last(elem);
    }
  }

  TType& operator[](const int ind) // Оператор индексации
  {
    if (ind < 0 || ind >= size || is_empty())
      throw std::string("TList::operator[](int) throw an exception");
    Node* tmp = pFirst;
    for (int i = 0; tmp != nullptr; i++)
    {
      if (i == ind)
        return tmp->data;
      tmp = tmp->pNext;
    }
  }

};
