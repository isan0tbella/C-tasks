

using namespace std;

constexpr double pi = 3.141592653589793238;

class Degrees;

class Radians
{
    double val;
    
    public:
        Radians(double v): val(v) {}
        double get() const {return val;}
    
        Degrees radians_to_degrees() const {return Degrees(val*180.0/pi);}

    Radians operator+(const Radians& val2) const {return Radians(val + val2.val);}
    Radians operator-(const Radians& val2) const {return Radians(val - val2.val);}
    Radians operator*(double k) const {return Radians(val * k);}
    Radians operator/(double k) const {return Radians(val / k);}

    bool operator==(const Radians& val2) const {return bool(val == val2.val);}
    bool operator<(const Radians& val2) const {return bool(val < val2.val);}
    bool operator<=(const Radians& val2) const {return bool(val <= val2.val);}
    bool operator>(const Radians& val2) const {return bool(val > val2.val);}
    bool operator>=(const Radians& val2) const {return bool(val >= val2.val);}
};



class Degrees
{
    double val;

    public:
        Degrees(double v): val(v) {}
        double get() const {return val;}
    
        Radians degrees_to_radians() const {return Radians(val*pi/180.0);}

    Degrees operator+(const Degrees& val2) const {return Degrees(val + val2.val);}
    Degrees operator-(const Degrees& val2) const {return Degrees(val - val2.val);}
    Degrees operator*(double k) const {return Degrees(val * k);}
    Degrees operator/(double k) const {return Degrees(val / k);}

    bool operator==(const Degrees& val2) const {return bool(val == val2.val);}
    bool operator<(const Degrees& val2) const {return bool(val < val2.val);}
    bool operator<=(const Degrees& val2) const {return bool(val <= val2.val);}
    bool operator>(const Degrees& val2) const {return bool(val > val2.val);}
    bool operator>=(const Degrees& val2) const {return bool(val >= val2.val);}
};

Radians degrees_to_radians(const Degrees& d) {return Radians(d.degrees_to_radians());}
Degrees radians_to_degrees(const Radians& r) {return Degrees(r.radians_to_degrees());}









