// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0) throw - 1;
  else
  {
    bitLen = len;
    if (bitLen % 32 == 0) memLen = bitLen % 32;
    else memLen = bitLen % 32 + 1;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
      pMem[i] = 0;

  }

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[memLen];
  if (pMem != NULL)
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n > bitLen)) throw - 1;
  else
    return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  TELEM mask = 1;
  int m = n % 32;
  mask = 1 << m;
  return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n > bitLen)) throw - 1;
  else
    if (pMem[GetMemIndex(n)]) pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n > bitLen)) throw - 1;
  else
  {
    int tmp = pMem[GetMemIndex(n)];
    tmp &= GetMemMask(n);
    if (tmp != 0) return 1;
    else return 0;
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf)
 
    bitLen = bf.bitLen;
    memLen = bf.memLen;
    pMem = new TELEM[memLen];
    for (int i = 0; i < memLen; i++)
      pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  for (int i = 0; i < bitLen; i++)
  {
    if (GetBit(i) != bf.GetBit(i)) return 0;
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  int i = 0;
  if (memLen == bf.memLen)
    while (pMem[i] == bf.pMem[i])
      i++;
  else return 1;
  if (i == memLen) return 0;
  else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int max = 0;
  int min = 0;
  if (bitLen >= bf.bitLen)
  {
    max = bitLen;
    min = bf.bitLen;
  }
  else
  {
    max = bf.bitLen;
    min = bitLen;
  }
  TBitField tmp(max);
  if (max == bitLen) tmp = *this;
  else tmp = bf;
  for (int i = 0; i < min; i++)
    if (GetBit(i) || bf.GetBit(i))
      tmp.SetBit(i);
  return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int max = 0;
  int min = 0;
  if (bitLen >= bf.bitLen)
  {
    max = bitLen;
    min = bf.bitLen;
  }
  else
  {
    max = bf.bitLen;
    min = bitLen;
  }
  TBitField tmp(max);
  for (int i = 0; i < min; i++)
    if (GetBit(i) && bf.GetBit(i))
      tmp.SetBit(i);
  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField tmp(bitLen);
  for (int i = 0; i < memLen; i++)
    tmp.pMem[i] = ~pMem[i];
  return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int i = 0;
  while ((i <= 0) && (i < bf.bitLen))
  {
    bf.SetBit(i);
    istr >> i;
  }
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++)
    ostr << bf.GetBit(i);
  return ostr;
}
