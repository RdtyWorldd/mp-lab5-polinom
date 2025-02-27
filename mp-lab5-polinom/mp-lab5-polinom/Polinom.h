#pragma once
#include <iostream>
#include <memory>
#include "List.h"

struct Monom
{
  double coeff;
  size_t x;
  size_t y;
  size_t z;

  bool operator== (const Monom& m) const;
  bool operator!= (const Monom& m) const;
  bool operator> (const Monom& m) const;
  bool operator< (const Monom& m) const;
  bool operator>= (const Monom& m) const;
  bool operator<= (const Monom& m) const;
};

/*
todo
-iterator
-tests

-override operators
*/

/*
  -методы добавления мономов
  слияние двух упорядоченных массивов
  похожее

  1) степени равны
  если степени равны складываем соответствующие коээфы, если не равно нулю, записываем, 
  если 0 то двигаем только добавляемый, так как pCurr результирующего итак сдвинется
  2) добавленного больше результирующего больше
  ставим перед, двигаем pCurr у добавляемого
  3) у результирующего больше
  ситуация аналогична 2

  когда кончится один из полиномов, то добавляем 
*/
class Polinom : public List<Monom>
{
private:
  Polinom& MonomOp(Monom m, double (*op)(double, double));
public:
  Polinom();
  Polinom(Monom* m, size_t size);
  Polinom(std::initializer_list<Monom> m);

  Polinom& addMonom(Monom m);
  Polinom& subMonom(Monom m);
  Polinom& multMonom(Monom m);

  Polinom& addPolinom(Polinom& p);
  Polinom& subPolinom(Polinom& p);
  Polinom& multPolinom(Polinom& p);

  Polinom& mult(const double c);
};