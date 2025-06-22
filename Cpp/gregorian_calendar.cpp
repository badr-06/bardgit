#include <iostream>
#include <stdexcept>
#include <cmath>

class Date {
private:
  int Days;

  int Yearinvis(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
  }

  int DaysinMoth(int m, int y) {
    if ((m == 2) && Yearinvis(y))
      return 29;
    else {
      const int day_in_mobth[] = {31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
      return day_in_mobth[m - 1];
    }
  }

  int validdate(int D, int M, int Y) {
    if (D < 1 || M < 1 || D > DaysinMoth(M, Y) || M > 12 || Y < 1970 ||
        Y > 2099)
      return 0;
    else
      return 1;
  }

  int totalDay() {
    int total_day = 0;
    for (int i = 1970; i < Year; i++) {
      total_day += (Yearinvis(i) ? 366 : 365);
    }
    for (int i = 1; i < Month; i++) {
      total_day += DaysinMoth(i, Year);
    }
    return total_day += Day;
  }

  void Fromdays(int t) {
    Year = 1970;
    while (t >= (Yearinvis(Year) ? 366 : 365)) {
      t -= (Yearinvis(Year) ? 366 : 365);
      ++Year;
    }
    Month = 1;
    int m = 0;
    while (t > (m = DaysinMoth(Month, Year))) {
      t -= m;
      ++Month;
    }

    Day = t;
  }

public:
  Date(int D, int M, int Y);

  int GetDay() const;
  int GetMonth() const;
  int GetYear() const;

  Date operator+(int s) {
    Date new_date(Day, Month, Year);
    int d = new_date.totalDay() + s;
    new_date.Fromdays(d);

    return new_date;
  }

  Date operator-(int s) {
    Date new_date(Day, Month, Year);
    if (Day <= s) {
      int d = new_date.totalDay() - s;
      new_date.Fromdays(d);
    } else {
      new_date.Day -= s;
    }
    return new_date;
  }

  void print() { std::cout << Day << ":" << Month << ":" << Year << std::endl; }

  int operator-(Date &other) {
    if (!validdate(this->Day, this->Month, this->Year) ||
        !validdate(other.Day, other.Month, other.Year)) {
      throw std::out_of_range("дата выходит за пределы");
    }
    int x = this->totalDay();
    int y = other.totalDay();
    int c = x - y;
    return c;
  }
};

Date::Date(int D, int M, int Y) {
  if (!validdate(D, M, Y)) {
    Days = 719050;
  } else {
   
  }
}
int Date::GetDay() const { return Day; }

int Date::GetMonth() const { return Month; }

int Date::GetYear() const { return Year; }

int main() {

  Date dt(20, -9, 2002);

  dt.print();

}