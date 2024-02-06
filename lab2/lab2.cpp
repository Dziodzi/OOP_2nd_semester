#include <bits/stdc++.h>

using namespace std;

class Polynom {
public:
    unordered_map <int, double> poli_;
    Polynom()= default;
    explicit Polynom(unordered_map <int, double> vect): poli_(std::move(vect)){}
    ~Polynom()= default;
    Polynom (const Polynom& get)= default;

    double operator [] (int i){
        return poli_[i];
    }

    Polynom& operator = (const Polynom& get)
    {
        if (&get == this)
        {
            return *this;
        }
        poli_ = get.poli_;
        return *this;
    }

    bool operator == (const Polynom& pol2) const
    {
        return poli_ == pol2.poli_;
    }

    bool operator != (const Polynom& pol2) const
    {
        return !(poli_ == pol2.poli_);
    }

    const Polynom& operator+() const{
        return *this;
    }
    friend Polynom operator / (const Polynom& pol1, double x);
};

ostream& operator << (ostream& stream, Polynom& pol)
{
    for (auto i: pol.poli_){
        if (pol.poli_[i.first] != 0)
        {
            if (pol.poli_[i.first] < 0)
                stream << pol.poli_[i.first] << "X^" << i.first;
            else
                stream << "+" << pol.poli_[i.first] << "X^" << i.first;
        }
    }
    cout <<endl;
    return stream;
}

istream& operator >> (istream& stream, Polynom& pol)
{
    int n;
    stream >> n;
    double num;
    int pow;
    for (int i = 0; i < n; i++) {
        stream >> num >> pow;
        pol.poli_[pow] = num;
    }
    return stream;
}
Polynom operator - (Polynom get)
{
    for (auto i: get.poli_)
        get.poli_[i.first] = -get.poli_[i.first];
    return get;
}


void operator *= (Polynom &pol1, Polynom& pol2)
{
    unordered_map <int, double> poln;
    for (auto i: pol1.poli_)
        for (auto j: pol2.poli_)
            poln[i.first + j.first] += pol1.poli_[i.first] * pol2.poli_[j.first];
    pol1.poli_ = poln;
}

Polynom operator * (const Polynom& pol1, Polynom& pol2)
{
    Polynom p(pol1);
    p*=pol2;
    return p;
}


void operator += (Polynom& pol1,  Polynom& pol2)
{
    for (auto i: pol2.poli_)
        pol1.poli_[i.first] += pol2.poli_[i.first];
}

Polynom operator + (const Polynom& pol1,  Polynom& pol2)
{
    Polynom p(pol1);
    p+=pol2;
    return p;
}
void operator -= (Polynom& pol1,  Polynom& pol2)
{
    for (auto i: pol2.poli_)
        pol1.poli_[i.first] -= pol2.poli_[i.first];
}

Polynom operator - (const Polynom &pol1,  Polynom& pol2)
{
    Polynom p(pol1);
    p-=pol2;
    return p;
}

void operator *= (Polynom& pol1, double x)
{
    for (auto i: pol1.poli_)
        pol1.poli_[i.first] *= x;
}

Polynom operator * (const Polynom& pol1, const double x)
{
    Polynom p(pol1);
    p*=x;
    return p;
}

void operator /= (Polynom& pol1, double x)
{
    for (auto i: pol1.poli_)
        pol1.poli_[i.first] /= x;
}

Polynom operator / (const Polynom& pol1, const double x)
{
    Polynom p(pol1);
    p/=x;
    return p;
}

