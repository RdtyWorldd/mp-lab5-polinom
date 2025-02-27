#include "Polinom.h"

// Перегрузка оператора ==
bool Monom::operator==(const Monom &m) const {
    return coeff == m.coeff && x == m.x && y == m.y && z == m.z;
  }

  // Перегрузка оператора !=
  bool  Monom::operator!=(const Monom &m) const {
    return !(*this == m);  // Используем уже реализованный оператор ==
  }

  // Перегрузка оператора >
	bool Monom::operator>(const Monom &m) const {
    if(x > m.x)
	{
		if(y > m.y)
		{
			if(z > m.z)
				return true;
		}
	}
	return false;
  }

  // Перегрузка оператора <
  bool Monom::operator<(const Monom &m) const {
	if(x < m.x)
	{
		if(y < m.y)
		{
			if(z < m.z)
				return true;
		}
	}
	return false;
  }

  // Перегрузка оператора >=
  bool  Monom::operator>=(const Monom &m) const {
    return (*this > m || *this == m);
  }

  // Перегрузка оператора <=
  bool  Monom::operator<=(const Monom &m) const {
    return (*this < m || *this == m);
  }



/*************************************/

Polinom::Polinom():List()
{
}

//переписать
Polinom::Polinom(Monom* m, size_t size): List<Monom>()
{
  Node<Monom>* tmp = pFirst;
  Node<Monom>* add;
  for (size_t i = 0; i < size; i++)
  {
	add = new Node<Monom>;
	add->val = m[i];
	add->pNext = nullptr;

	tmp->pNext = add;
  }
  pLast = add;
}

Polinom::Polinom(std::initializer_list<Monom> m): List(m) 
{
}

Polinom& Polinom::MonomOp(Monom m, double (*op)(double, double))
{
	Polinom res(*this);
	if (pFirst == nullptr) 
	{
		m.coeff = op(0, m.coeff);
		res.pushBack(m);
	}
	else 
	{
		int i = 0;
		for(res.Reset(); !res.IsEnd(); res.GoNext())
		{
			if(m >= res.pCurr->val)
			{
				//моном больше
				if(m > res.pCurr->val)
				{
					m.coeff = op(0, m.coeff);
					res.add(i, m);
				}
				else //моном равен
				{
					double c = op(res.pCurr->val.coeff, m.coeff);
					if(c != 0.0)
						res.pCurr->val.coeff = c;
					else 
						res.remove(i);
				}
				break;
			}
			i++;
		}
		//если моном меньше всех в списке
		if(i == size)
		{
			m.coeff = op(0, m.coeff);
			res.pushBack(m);
		}
	}
	return res;
}

Polinom& Polinom::addMonom(Monom m)
{
	auto add {[] (double a, double b) { return a + b; } };
	return MonomOp(m, add);
}

Polinom& Polinom::subMonom(Monom m)
{
	auto sub {[] (double a, double b) { return a - b; } };
	return MonomOp(m, sub);
}

Polinom& Polinom::multMonom(Monom m)
{
	Polinom res(*this);
	for(res.Reset(); !res.IsEnd(); res.GoNext())
	{
		res.pCurr->val.coeff *= m.coeff;
		res.pCurr->val.x += m.x;
		res.pCurr->val.y += m.y;
		res.pCurr->val.z += m.z;
	}
	return res;
}

Polinom& Polinom::addPolinom(Polinom& p)
{
	Polinom res(*this);
	for(p.Reset(); !p.IsEnd(); p.GoNext())
	{
		res = res.addMonom(p.pCurr->val);
	}
	return res;
}

Polinom& Polinom::subPolinom(Polinom& p)
{
	Polinom res(*this);
	for(p.Reset(); !p.IsEnd(); p.GoNext())
	{
		res = res.subMonom(p.pCurr->val);
	}
	return res;
}

Polinom& Polinom::mult(const double c)
{
	Polinom res(*this);
	if(c == 0)
	{
		clear();
	}

	for(res.Reset(); !res.IsEnd(); res.GoNext())
	{
		pCurr->val.coeff *= c;
	}
	return res;
}

Polinom& Polinom::multPolinom(Polinom& p)
{
	Polinom res, tmp(*this);
	for(p.Reset(); !p.IsEnd(); p.GoNext())
	{
		Monom m = p.pCurr->val;
		res = res.addPolinom(tmp.multMonom(m));
	}
	return res;
}
