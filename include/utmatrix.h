﻿// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();

  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента

  ValType& operator[](int pos);             // доступ
  const ValType& operator[](int pos) const; // доступ для константных объектов
  ValType& at(int pos);                     // доступ с проверкой корректности индекса
  const ValType& at(int pos) const;         // доступ с проверкой корректности индекса для константных объектов

  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector& operator+=(const TVector &v);
  TVector  operator-(const TVector &v);     // вычитание
  TVector& operator-=(const TVector &v);
  ValType  operator*(const TVector &v);     // скалярное произведение

  friend class TVector<TVector<ValType>>;
  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v);
  friend ostream& operator<<(ostream &out, const TVector &v);
};

template <class ValType>
TVector<ValType>::TVector(int s, int si): Size(s), StartIndex(si) 
{
    if (s < 0 || s > MAX_VECTOR_SIZE)
        throw runtime_error("TVector::TVector(): size is incorrect");
    if (si < 0 || si >= MAX_VECTOR_SIZE)
        throw runtime_error("TVector::TVector(): start index is incorrect");

    pVector = new ValType[s]{};
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v): Size(v.Size), StartIndex(v.StartIndex)
{
    pVector = new ValType[Size];
    for (size_t i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ для константных объектов
const ValType& TVector<ValType>::operator[](int pos) const
{
    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ с проверкой корректности индекса
ValType& TVector<ValType>::at(int pos)
{
    if (pos < StartIndex || pos >= Size)
        throw runtime_error("TVector::at(): index is incorrect");

    return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ с проверкой корректности индекса для константных объектов
const ValType& TVector<ValType>::at(int pos) const
{
    if (pos < StartIndex || pos >= Size)
        throw runtime_error("TVector::at(): index is incorrect");

    return pVector[pos];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (this == &v) return true;
    if (Size != v.Size || StartIndex != v.StartIndex) return false;

    for (size_t i = 0; i < Size; ++i)
        if (pVector[i] != v.pVector[i]) return false;
    
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this == &v) return *this;
    
    StartIndex = v.StartIndex;

    if (Size != v.Size) {
        delete[] pVector;
        pVector = new ValType[v.Size];
        Size = v.Size;
    }
    for (size_t i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];

    return *this;

} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector<ValType> res = *this;
    for (size_t i = 0; i < Size; ++i)
        res.pVector[i] += val;
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector<ValType> res = *this;
    for (size_t i = 0; i < Size; ++i)
        res.pVector[i] -= val;
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector<ValType> res = *this;
    for (size_t i = 0; i < Size; ++i)
        res.pVector[i] *= val;
    return res;
} /*-------------------------------------------------------------------------*/


template <class ValType> // присваивающее сложение
TVector<ValType>& TVector<ValType>::operator+=(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw runtime_error("TVector::operator+(TVector): sizes of vectors are different");

    for (size_t i = 0; i < Size; ++i)
        pVector[i] += v.pVector[i];
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw runtime_error("TVector::operator+(TVector): sizes of vectors are different");

    TVector<ValType> res = *this;
    res += v;
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивающее вычитание
TVector<ValType>& TVector<ValType>::operator-=(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw runtime_error("TVector::operator+(TVector): sizes of vectors are different");

    for (size_t i = 0; i < Size; ++i)
        pVector[i] -= v.pVector[i];
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw runtime_error("TVector::operator+(TVector): sizes of vectors are different");

    TVector<ValType> res = *this;
    res -= v;
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw runtime_error("TVector::operator*(TVector): sizes of vectors are different");

    ValType res = 0;
    for (size_t i = 0; i < Size; ++i)
        res += pVector[i] * v.pVector[i];
    return res;
} /*-------------------------------------------------------------------------*/

template <typename ValType>
istream& operator>>(istream &in, TVector<ValType> &v)
{
    for (int i = 0; i < v.Size; i++)
        in >> v.pVector[i];
    return in;
}

template <typename ValType>
ostream& operator<<(ostream &out, const TVector<ValType> &v)
{
    for (int i = 0; i < v.Size; i++)
        out << v.pVector[i] << ' ';
    out << '\n';

    return out;
}



// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа

  ValType& at(int i, int j);                     // доступ к ячейке матрицы с проверкой индекса
  const ValType& at(int i, int j) const;         // доступ к ячейке константной матрицы с проверкой индекса

  /*bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  */
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};


template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    if (s > MAX_MATRIX_SIZE)
        throw runtime_error("TMatrix::TMatrix(): size is too large");

    for (size_t i = 0; i < s; ++i) {
        pVector[i] = TVector<ValType>(s-i,i);
    }
} /*-------------------------------------------------------------------------*/


template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
    TVector<TVector<ValType>>(mt) {
    
    for (size_t i = 0; i < Size; ++i)
        pVector[i] = mt.pVector[i];
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>> &mt):
    TVector<TVector<ValType>>(mt) {

    for (size_t i = 0; i < Size; ++i)
        pVector[i].StartIndex = i;
}

template <class ValType> // доступ к ячейке матрицы с проверкой индекса
ValType& TMatrix<ValType>::at(int i, int j) {
    if (i < 0 || i >= Size || j < 0 || j >= Size || i > j)
        throw runtime_error("TMatrix::at(): one of indices is incorrect");

    return pVector[i][j-pVector[i].StartIndex];
}

template <class ValType> // доступ к константной матрице с проверкой индекса
const ValType& TMatrix<ValType>::at(int i, int j) const {
    if (i < 0 || i >= Size || j < 0 || j >= Size || i > j)
        throw runtime_error("TMatrix::at(): one of indices is incorrect");

    return pVector[i][j-pVector[i].StartIndex];
}

/*
template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (this == &mt) return true;
    if (Size != mt.Size) return false;

    for (size_t i = 0; i < Size; ++i)
        if (pVector[i] != mt.pVector[i]) return false;

    return true;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
}

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this == &mt) return *this;

    if (Size != mt.Size) {
        for (size_t i = 0; i < Size; ++i)
            pVector[i]::~TVector();
        delete[] pVector;
        pVector = new ValType[v.Size];
        Size = v.Size;
    }
    for (size_t i = 0; i < Size; ++i)
        pVector[i] = v.pVector[i];

    return *this;

}

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw runtime_error("TMatrix::operator+: sizes are different");

    TMatrix<ValType> res = *this;
    for (size_t i = 0; i < Size; ++i)
        res.pVector[i] += mt.pVector[i];

    return res;
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    if (Size != mt.Size)
        throw runtime_error("TMatrix::operator+: sizes are different");

    TMatrix<ValType> res = *this;
    for (size_t i = 0; i < Size; ++i)
        res.pVector[i] -= mt.pVector[i];

    return res;
}
*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
