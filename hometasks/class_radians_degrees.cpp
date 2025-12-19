
#include <iostream>
using namespace std;

constexpr double pi = 3.141592653589793238;

class Radians;

class Degrees
{
    double val;

    public:
        Degrees(double v): val(v) {}
        double get() const {return val;}
    
        Radians degrees_to_radians() const;


    Degrees& operator+= (const Degrees& rhs);
    Degrees& operator-= (const Degrees& rhs);
    Degrees& operator*= (double rhs);
    Degrees& operator/= (double rhs);

    bool operator==(const Degrees& val2) const {return bool(val == val2.val);}
    bool operator<(const Degrees& val2) const {return bool(val < val2.val);}
    bool operator<=(const Degrees& val2) const {return bool(val <= val2.val);}
    bool operator>(const Degrees& val2) const {return bool(val > val2.val);}
    bool operator>=(const Degrees& val2) const {return bool(val >= val2.val);}
};

Degrees& Degrees::operator+= (const Degrees& rhs)
{
  val += rhs.val;
  return *this;
}
Degrees& Degrees::operator-= (const Degrees& rhs)
{
  val -= rhs.val;
  return *this;
}
Degrees& Degrees::operator*= (double rhs)
{
  val *= rhs;
  return *this;
}
Degrees& Degrees::operator/= (double rhs)
{
  val += rhs;
  return *this;
}

Degrees operator* (const Degrees& lhs, double rhs);
Degrees operator* (double rhs, const Degrees& lhs);
Degrees operator- (const Degrees& lhs, const Degrees& rhs);
//Degrees operator- (const Degrees& rhs, const Degrees& lhs);
Degrees operator+ (const Degrees& lhs, const Degrees& rhs);
//Degrees operator+ (const Degrees& rhs, const Degrees& lhs);
Degrees operator/ (const Degrees& lhs, double rhs);

Degrees operator+(const Degrees& lhs, const Degrees& rhs){return Degrees{lhs} += rhs;}
//Degrees operator+(const Degrees& lhs, const Degrees& rhs){return Degrees{lhs} += rhs;}
Degrees operator-(const Degrees& lhs, const Degrees& rhs){return Degrees{lhs} -= rhs;}
//Degrees operator-(const Degrees& lhs, const Degrees& rhs){return Degrees{lhs} -= rhs;}
Degrees operator*(const Degrees& lhs, double rhs){return Degrees{lhs} *= rhs;}
Degrees operator*(double lhs, const Degrees& rhs){return rhs * lhs;}
Degrees operator/(const Degrees& lhs, double rhs){return Degrees{lhs} /= rhs;}



class Radians
{
    double val;
    
    public:
        Radians(double v): val(v) {}
        double get() const {return val;}
    
        Degrees radians_to_degrees() const;

    Radians& operator+= (const Radians& rhs);
    Radians& operator-= (const Radians& rhs);
    Radians& operator*= (double rhs);
    Radians& operator/= (double rhs);

    bool operator==(const Radians& val2) const {return bool(val == val2.val);}
    bool operator<(const Radians& val2) const {return bool(val < val2.val);}
    bool operator<=(const Radians& val2) const {return bool(val <= val2.val);}
    bool operator>(const Radians& val2) const {return bool(val > val2.val);}
    bool operator>=(const Radians& val2) const {return bool(val >= val2.val);}
};

Radians& Radians::operator+= (const Radians& rhs)
{
  val += rhs.val;
  return *this;
}
Radians& Radians::operator-= (const Radians& rhs)
{
  val -= rhs.val;
  return *this;
}
Radians& Radians::operator*= (double rhs)
{
  val *= rhs;
  return *this;
}
Radians& Radians::operator/= (double rhs)
{
  val += rhs;
  return *this;
}


Radians operator* (const Radians& lhs, double rhs);
Radians operator* (double rhs, const Radians& lhs);
Radians operator- (const Radians& lhs, const Radians& rhs);
//Radians operator- (const Radians& rhs, const Radians& lhs);
Radians operator+ (const Radians& lhs, const Radians& rhs);
//Radians operator+ (const Radians& rhs, const Radians& lhs);
Radians operator/ (const Radians& lhs, double rhs);

Radians operator+(const Radians& lhs, const Radians& rhs){return Radians{lhs} += rhs;}
//Radians operator+(const Radians& lhs, const Radians& rhs){return Radians{lhs} += rhs;}
Radians operator-(const Radians& lhs, const Radians& rhs){return Radians{lhs} -= rhs;}
//Radians operator-(const Radians& lhs, const Degrees& rhs){return Degrees{lhs} -= rhs;}
Radians operator*(const Radians& lhs, double rhs){return Radians{lhs} *= rhs;}
Radians operator*(double lhs, const Radians& rhs){return rhs * lhs;}
Radians operator/(const Radians& lhs, double rhs){return Radians{lhs} /= rhs;}



Radians Degrees::degrees_to_radians() const { return Radians(val * pi / 180.0); }
Degrees Radians::radians_to_degrees() const { return Degrees(val * 180.0 / pi); }

Radians degrees_to_radians(const Degrees& d) {return Radians(d.degrees_to_radians());}
Degrees radians_to_degrees(const Radians& r) {return Degrees(r.radians_to_degrees());}



int main() //проверка
{
    Degrees d1(90);
    Degrees d2(45);
    Radians r1 = d1.degrees_to_radians();
    Radians r2 = d2.degrees_to_radians();

    cout << "90 degrees = " << r1.get() << " radians\n";
    cout << r2.get() << " radians = " << radians_to_degrees(r2).get() << " degrees\n";

    Degrees sum = d1 + d2;
    Degrees sum2 = d2 + d1;
    Degrees diff = d1 - d2;
    cout << "90 + 45 = " << sum.get() << " degrees\n";
    cout << "45 + 90 = " << sum2.get() << " degrees\n";
    cout << "90 - 45 = " << diff.get() << " degrees\n";

    Radians r_sum = r1 + r2;
    Radians r_sum_2 = r2 + r1;
    Radians r_scaled = r1 * 2.0;
    Radians r_skaled2 = 2.0 * r1;
    cout << r1.get() << " + " << r2.get() << " = " << r_sum.get() << " radians\n";
    cout << r1.get() << " + " << r2.get() << " = " << r_sum_2.get() << " radians\n";

    cout << r1.get() << " * 2 = " << r_scaled.get() << " radians\n";
    cout << " 2 * " << r1.get() << " = "<< r_skaled2.get() << " radians\n";

    cout << "90 deg == 45 deg ? " << (d1 == d2) << "\n";
    cout << "90 deg > 45 deg ?  " << (d1 > d2)  << "\n";
    cout << "r1 < r2 ? " << (r1 < r2) << "\n";

    return 0;
}







