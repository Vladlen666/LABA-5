#pragma once
#include "list.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define PMAX 10

/*
Требования: полином задаётся в виде строки, в качестве внутреннего представления используется список из мономов
Операции: сложение, умножение, вычисление в точке (деление по желанию)
Сохранение/запись в файл (текстовый) (в полиноме нужно преобразование в строку и обратно)
*/

struct Monom
{
  double coef; // Коэффициент монома
  int degx, degy, degz; // degree of variables

  Monom(double _coef = 0.0, int _degx = 0, int _degy = 0, int _degz = 0) : coef(_coef), degx(_degx), degy(_degy), degz(_degz) {} // Конструктор

  Monom(const std::string& str) { ConvertFromString(str); } // Конструктор

  Monom(const Monom& other) // Конструктор копирования
  {
    coef = other.coef;
    degx = other.degx;
    degy = other.degy;
    degz = other.degz;
  }

  void ConvertFromString(const std::string& str)
  {
    *this = Monom();

    if (str.size() == 0)
      return;

    int first_not_num_ind = str.find_first_not_of("0123456789.- "); // Номер первого найденного символа (не цифры)
    if (first_not_num_ind == std::string::npos)
    {
      coef = stod(str);
      return;
    }
    else
    {
      if (first_not_num_ind == 0)
      {
        coef = 1.0;
      }
      else
      {
        std::string tmpcoef;
        for (int i = 0; i < first_not_num_ind; i++)
          tmpcoef += str[i];
        if (tmpcoef == "-")
          coef = -1.0;
        else
          coef = stod(tmpcoef);
      }
    }

    for (int i = str.size() - 1; i >= first_not_num_ind; i--)
    {
      std::string tmp;
      while (str[i] != 'x' && str[i] != 'y' && str[i] != 'z')
      {
        tmp += str[i];
        i--;
        if (i < 0)
          break;
      }
      if (i >= 0)
      {
        if (tmp.empty())
          tmp = "1";
        else
          std::reverse(tmp.begin(), tmp.end());

        if (str[i] == 'z')
          degz = std::stoi(tmp);
        if (str[i] == 'y')
          degy = std::stoi(tmp);
        if (str[i] == 'x')
          degx = std::stoi(tmp);
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& os, const Monom& mon)
  {
    if (mon.coef == 0)
      return os << 0;
    if (mon.coef > 0)
      os << '+';
    os << mon.coef;
    if (mon.degx != 0)
    {
      if (mon.degx == 1)
        os << 'x';
      else
        os << 'x' << mon.degx;
    }
    if (mon.degy != 0)
    {
      if (mon.degy == 1)
        os << 'y';
      else
        os << 'y' << mon.degy;
    }
    if (mon.degz != 0)
    {
      if (mon.degz == 1)
        os << 'z';
      else
        os << 'z' << mon.degz;
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Monom& mon)
  {
    std::string str;
    std::getline(is, str);
    mon.ConvertFromString(str);
    return is;
  }

  int deg() const noexcept { return degx * PMAX * PMAX + degy * PMAX + degz; }

  bool exist() const noexcept { return degx < PMAX&& degy < PMAX&& degz < PMAX; }

  // Операторы сравнения мономов без учёта коэффициентов (лексикографически)
  bool operator==(const Monom& other) const noexcept { return deg() == other.deg(); }
  bool operator!=(const Monom& other) const noexcept { return !(*this == other); }
  bool operator<(const Monom& other) const noexcept { return deg() < other.deg(); }
  bool operator>(const Monom& other) const noexcept { return deg() > other.deg(); }

  // Операторы
  friend Monom& operator+=(Monom& left, const Monom& right)
  {
    if (left == right)
    {
      left.coef += right.coef;
      left.optimization();
      return left;
    }
    else
      throw std::string("Monom& operator+=(Monom, Monom) throw an exception");
  }

  Monom operator+(const Monom& other) const noexcept
  {
    Monom tmp(*this);
    tmp += other;
    return tmp;
  }

  friend Monom& operator-=(Monom& left, const Monom& right)
  {
    if (left == right)
    {
      left.coef -= right.coef;
      left.optimization();
      return left;
    }
    else
      throw std::string("Monom& operator+=(Monom, Monom) throw an exception");
  }

  Monom operator-(const Monom& other) const noexcept
  {
    Monom tmp(*this);
    tmp -= other;
    if (tmp == 0)
      tmp.optimization();
    return tmp;
  }

  friend Monom& operator*=(Monom& left, const Monom& right)
  {
    left.coef *= right.coef;
    left.degx += right.degx;
    left.degy += right.degy;
    left.degz += right.degz;
    if (!left.exist())
      throw std::string("Monom operator*=(Monom, Monom) throw an exception");
    return left;
  }

  Monom operator*(const Monom& other) const
  {
    Monom tmp(*this);
    tmp *= other;
    return tmp;
  }

  Monom& operator=(const Monom& other)
  {
    if (this == &other)
      return *this;
    coef = other.coef;
    degx = other.degx;
    degy = other.degy;
    degz = other.degz;
    return *this;
  }

  friend Monom operator-(Monom& mon)
  {
    Monom tmp(mon);
    tmp.coef = -mon.coef;
    return tmp;
  }

  void optimization()
  {
    if (coef == 0)
      degx = degy = degz = 0;
  }

  double value_in_dot(int _x, int _y, int _z)
  {
    return coef * pow(_x, degx) * pow(_y, degy) * pow(_z, degz);
  }
};

class Polynomial
{
private:
  TList<Monom> data;
public:
  Polynomial() {} // Конструктор

  Polynomial(const std::string& str) { ConvertFromString(str); }

  Polynomial(const Polynomial& other) { data = other.data; }

  void ConvertFromString(const std::string& str)
  {
    for (int i = 0; i < str.size(); i++)
    {
      std::string tmp;
      if (str[i] == '-')
        tmp += str[i++];
      while (i < str.size())
      {
        if (str[i] == ' ')
        {
          i++;
          continue;
        }
        else
        {
          if (str[i] == '+' || str[i] == '-')
          {
            if (str[i] == '-')
              i--;
            break;
          }
          else
          {
            tmp += str[i++];
          }
        }
      }
      *this += Monom(tmp);
    }
    optimization();
  }

  void clear() { data.clear(); }

  void optimization()
  {
    for (int i = data.get_size() - 1; i >= 0; i--)
      if (data[i].coef == 0)
        data.delete_in_pos(i);
  }

  double value_in_dot(int _x, int _y, int _z)
  {
    double res = 0;
    for (int i = 0; i < data.get_size(); i++)
      res += data[i].value_in_dot(_x, _y, _z);
    return res;
  }

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& pol)
  {
    os << pol.data << '\n';
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Polynomial& pol)
  {
    pol.clear();
    std::string str;
    std::getline(is, str);
    pol.ConvertFromString(str);
    return is;
  }

  Polynomial& operator+=(const Monom& other)
  {
    for (int i = 0; i < data.get_size(); i++)
      if (data[i] == other)
      {
        data[i] += other;
        optimization();
        return *this;
      }
    data.insert_in_order(other);
    return *this;
  }

  friend Polynomial& operator+=(Polynomial& left, Polynomial& right)
  {
    for (int i = 0; i < right.data.get_size(); i++)
      left += right.data[i];
    return left;
  }

  Polynomial operator+(Polynomial& other) const noexcept
  {
    Polynomial tmp(*this);
    tmp += other;
    return tmp;
  }

  Polynomial& operator*=(const Monom& other)
  {
    for (int i = 0; i < data.get_size(); i++)
      data[i] *= other;
    optimization();
    return *this;
  }

  friend Polynomial& operator*=(Polynomial& left, Polynomial& right)
  {
    Polynomial copy(left);
    left.clear();
    for (int i = 0; i < right.data.get_size(); i++)
    {
      Polynomial tmp(copy);
      tmp *= right.data[i];
      left += tmp;
    }
    return left;
  }

  Polynomial operator*(Polynomial& other) const noexcept
  {
    Polynomial tmp(*this);
    tmp *= other;
    return tmp;
  }

  friend Polynomial operator-(Polynomial& pol) // Унарный минус
  {
    Polynomial tmp;
    for (int i = 0; i < pol.data.get_size(); i++)
      tmp.data.insert_last(-pol.data[i]);
    return tmp;
  }

  Polynomial& operator-=(Monom& other)
  {
    for (int i = 0; i < data.get_size(); i++)
      if (data[i] == other)
      {
        data[i] -= other;
        optimization();
        return *this;
      }
    data.insert_in_order(-other);
    return *this;
  }

  friend Polynomial& operator-=(Polynomial& left, Polynomial& right)
  {
    for (int i = 0; i < right.data.get_size(); i++)
      left -= right.data[i];
    return left;
  }

  Polynomial operator-(Polynomial& other) const noexcept
  {
    Polynomial tmp(*this);
    tmp += -other;
    return tmp;
  }

  bool operator==(const Polynomial& other) const noexcept
  {
    if (data.get_size() != other.data.get_size())
      return false;
    Polynomial maincopy(*this);
    Polynomial copy(other);
    for (int i = 0; i < data.get_size(); i++)
      if ((maincopy.data[i] != copy.data[i]) || maincopy.data[i].coef != copy.data[i].coef)
        return false;
    return true;
  }

};

struct VecOfPolymomial
{
  std::vector<Polynomial> pols;

  void SaveInFile()
  {
    std::fstream fs;
    fs.open("Data.txt", std::fstream::out);
    if (!fs.is_open())
      throw std::string("Could not open the file Data.txt");
    for (const auto& pol : pols)
      fs << pol;
    fs.close();
  }

  void ReadFromFile()
  {
    pols.clear();
    std::fstream fs;
    fs.open("Data.txt", std::fstream::in);
    if (!fs.is_open())
      throw std::string("Could not open the file Data.txt");
    while (true)
    {
      Polynomial tmppol;
      fs >> tmppol;
      if (fs.eof())
        break;
      pols.push_back(tmppol);
    }
    fs.close();
  }

  void push_back(Polynomial pol) { pols.push_back(pol); }

  void push_back(std::string str) { pols.push_back(Polynomial(str)); }

  friend std::ostream& operator<<(std::ostream& os, const VecOfPolymomial& obj)
  {
    for (int i = 0; i < obj.pols.size(); i++)
      os << i + 1 << ')' << obj.pols[i] << '\n';
    return os;
  }

};
