#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:
    int _year;
    int _month;
    int _day;

public:
    // Default constructor: 1900-1-1
    Date() : _year(1900), _month(1), _day(1) {}

    // Parameterized constructor with validation
    Date(int yy, int mm, int dd) {
        if (isValidDate(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }

    // Check if a year is a leap year
    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    // Get the number of days in a given month
    int getDaysInMonth(int year, int month) const {
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return month_days[month];
    }

    // Validate if a date exists
    bool isValidDate(int year, int month, int day) const {
        if (year < 1900 || year > 2030) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getDaysInMonth(year, month)) return false;
        return true;
    }

    // Prefix ++: increment to next day and return reference
    Date& operator++() {
        _day++;
        if (_day > getDaysInMonth(_year, _month)) {
            _day = 1;
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        return *this;
    }

    // Postfix ++: increment to next day and return copy of old value
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }

    // Prefix --: decrement to previous day and return reference
    Date& operator--() {
        _day--;
        if (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day = getDaysInMonth(_year, _month);
        }
        return *this;
    }

    // Postfix --: decrement to previous day and return copy of old value
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    // Add days to a date
    Date operator+(int days) const {
        Date result = *this;
        for (int i = 0; i < days; i++) {
            ++result;
        }
        return result;
    }

    // Subtract days from a date
    Date operator-(int days) const {
        Date result = *this;
        for (int i = 0; i < days; i++) {
            --result;
        }
        return result;
    }

    // Less than comparison
    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }

    // Date difference (absolute value)
    int operator-(const Date& other) const {
        Date d1 = *this;
        Date d2 = other;
        int count = 0;

        // Make sure d1 is the earlier date
        if (d2 < d1) {
            Date temp = d1;
            d1 = d2;
            d2 = temp;
        }

        while (!(d1._year == d2._year && d1._month == d2._month && d1._day == d2._day)) {
            ++d1;
            count++;
        }

        return count;
    }

    // Output operator overload
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << "-" << d._month << "-" << d._day;
        return os;
    }

    // Alternative output function
    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main()
{
    Test();
    return 0;
}
