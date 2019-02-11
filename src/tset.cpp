// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp), maxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.maxPower)
{
  maxPower = s.maxPower;
  bitField = s.bitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf.GetLength())
{
  bitField = bf;
  maxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  if (Elem < 0) throw - 1;
  else return bitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  bitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  bitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  bitField = s.bitField;
  maxPower = s.maxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return (bitField == s.bitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return (bitField != s.bitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TBitField tmp(maxPower);
  tmp = bitField | s.bitField;
  TSet a(tmp);
  return a;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet tmp(*this);
  tmp.bitField.SetBit(Elem);
  return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet tmp(*this);
  tmp.bitField.ClrBit(Elem);
  return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TBitField tmp(maxPower);
  tmp = bitField&s.bitField;
  TSet a(tmp);
  return a;
}

TSet TSet::operator~(void) // дополнение
{
  TBitField tmp(maxPower);
  tmp = ~bitField;
  TSet a(tmp);
  return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  int i = 0;
  while ((i >= 0) && (i < s.maxPower))
  {
    s.InsElem(i);
    istr >> i;
  }
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  for (int i = 0; i < s.maxPower; i++)
    if (s.bitField.GetBit(i))
      ostr << i;
  return ostr;
}
