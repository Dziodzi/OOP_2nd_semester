#include <utility>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;


class Point {
public:
    double x;
    double y;
    explicit Point(double x_ = 0, double y_ = 0): x(x_), y(y_){}
    double GetX() const {
        return x;
    }
    double GetY() const {
        return y;
    }
};

class PolygonalChain
{
protected:
    vector <Point> chain;

public:

    explicit PolygonalChain(vector<Point> vect): chain(std::move(vect)){}

    virtual double perimeter() {
        double l = 0;
        for (int i = 0; i < chain.size() - 1; i++)
            l += sqrt((chain[i + 1].GetX() - chain[i].GetX()) * (chain[i + 1].GetX() - chain[i].GetX()) + (chain[i + 1].GetY() - chain[i].GetY()) * (chain[i + 1].GetY() - chain[i].GetY()));
        return l;
    }

    PolygonalChain(const PolygonalChain& get) = default;

    PolygonalChain& operator=(const PolygonalChain& get) {
        if (&get == this) {
            return *this;
        }
        for (auto i : get.chain) {
            chain.push_back(i);
        }
        return *this;
    }


};

class CompletePolygonalChain : public PolygonalChain {

public:
    explicit CompletePolygonalChain(vector<Point> vect) :PolygonalChain(std::move(vect)) {};

    double perimeter() override {
        double l = 0;
        for (int i = 0; i < chain.size() - 1; i++)
            l += sqrt((chain[i + 1].GetX() - chain[i].GetX()) * (chain[i + 1].GetX() - chain[i].GetX()) + (chain[i + 1].GetY() - chain[i].GetY()) * (chain[i + 1].GetY() - chain[i].GetY()));
        l += sqrt((chain[chain.size() - 1].GetX() - chain[0].GetX()) * (chain[chain.size() - 1].GetX() - chain[0].GetX()) + (chain[chain.size() - 1].GetY() - chain[0].GetY()) * (chain[chain.size() - 1].GetY() - chain[0].GetY()));
        return l;
    }

};

class Polygon :public CompletePolygonalChain {
protected:
    static double angle(Point a, Point b) {
        return (a.GetX() * b.GetX() + a.GetY() * b.GetY()) / (sqrt(a.GetX() * a.GetX() + a.GetY() * a.GetY()) * sqrt(b.GetX() * b.GetX() + b.GetY() * b.GetY()));
    }

public:
    explicit Polygon(vector<Point> vect): CompletePolygonalChain(std::move(vect)) {
        if (not convex())
            cout << "?? ????????" << endl;
    };

    double area() {
        double a = 0;
        for (int i = 0; i < chain.size() - 1; i++) {
            a += chain[i].GetX() * chain[i + 1].GetY();
        }
        a += chain[chain.size() - 1].GetX() * chain[0].GetY();

        for (int i = 0; i < chain.size() - 1; i++) {
            a -= chain[i + 1].GetX() * chain[i].GetY();
        }
        a -= chain[0].GetX() * chain[chain.size() - 1].GetY();
        a = 0.5 * abs(a);
        return a;
    }
    int Edge() {
        int E = chain.size();
        return E;
    }




    bool convex(){
        Point prev, next;
        prev.x=chain[chain.size()-1].x-chain[chain.size()-2].x;
        prev.y=chain[chain.size()-1].y-chain[chain.size()-2].y;
        next.x=chain[0].x-chain[chain.size()-1].x;
        next.y=chain[0].y-chain[chain.size()-1].y;

        bool sign;
        sign= (prev.x * next.y - prev.y * next.x) >= 0;

        bool result=true;
        for (int i=1; i<chain.size() && result; ++i)
        {
            prev=next;
            next.x=chain[i].x-chain[i-1].x;
            next.y=chain[i].y-chain[i-1].y;
            result=sign*((prev.x * next.y - prev.y * next.x) >= 0);
        }
        return result;
    }

};

class Triangle : public Polygon {

public:
    explicit Triangle(vector<Point> vect) : Polygon(std::move(vect)) {
        if (chain.size() != 3) cout << "A o?aoaieuieea aie?ii auou 3 oi?ee, a ooo eo ia o?e!!1!" << endl;;
    };
    class Heights_of_Triangle {
    public:
        double a, b, c;
    };
    Heights_of_Triangle Heights() {
        double S = area();
        vector<double> side;
        vector<double> heights_;
        side.push_back(sqrt((chain[1].GetX() - chain[0].GetX()) * (chain[1].GetX() - chain[0].GetX()) + (chain[1].GetY() - chain[0].GetY()) * (chain[1].GetY() - chain[0].GetY())));
        side.push_back(sqrt((chain[2].GetX() - chain[1].GetX()) * (chain[2].GetX() - chain[1].GetX()) + (chain[2].GetY() - chain[1].GetY()) * (chain[2].GetY() - chain[1].GetY())));
        side.push_back(sqrt((chain[0].GetX() - chain[2].GetX()) * (chain[0].GetX() - chain[2].GetX()) + (chain[0].GetY() - chain[2].GetY()) * (chain[0].GetY() - chain[2].GetY())));
        Heights_of_Triangle tmp{};
        tmp.a = side[0];
        tmp.b = side[1];
        tmp.c = side[2];
        return tmp;
    }
};

class Trapezoid : public Polygon {

public:
    explicit Trapezoid(vector<Point> vect) : Polygon(std::move(vect)) {
        if (chain.size() != 4) cout << "A o?aiaoee aie?ii auou 4 oi?ee, a ooo eo ia ?aou?a!!1!" << endl;
        else {
            Point a(chain[3].GetX() - chain[0].GetX(), chain[3].GetY() - chain[0].GetY());
            Point b(chain[2].GetX() - chain[1].GetX(), chain[2].GetY() - chain[1].GetY());
            Point c(chain[3].GetX() - chain[2].GetX(), chain[3].GetY() - chain[2].GetY());
            Point d(chain[0].GetX() - chain[1].GetX(), chain[0].GetY() - chain[1].GetY());
            if (!(angle(a, b) == 1 && angle(c, d) != 1)) cout << "Io yoi o?a i?inoi eaeay-oi oeyia, a ia o?aiaoey" << endl;
        }
    };



};

class PolygonRight : public Polygon {

public:
    explicit PolygonRight(vector<Point> vect) : Polygon(std::move(vect)) {
        Point a(chain[chain.size() - 1].GetX() - chain[0].GetX(), chain[chain.size() - 1].GetY() - chain[0].GetY());
        Point b(chain[1].GetX() - chain[0].GetX(), chain[1].GetY() - chain[0].GetY());
        double checkAngle = angle(a, b);
        double checkLength = perimeter() / chain.size();
        if (sqrt((chain[chain.size() - 1].GetX() - chain[0].GetX()) * (chain[chain.size() - 1].GetX() - chain[0].GetX()) + (chain[chain.size() - 1].GetY() - chain[0].GetY()) * (chain[chain.size() - 1].GetY() - chain[0].GetY())) != checkLength || sqrt((chain[1].GetX() - chain[0].GetX()) * (chain[1].GetX() - chain[0].GetX()) + (chain[1].GetY() - chain[0].GetY()) * (chain[1].GetY() - chain[0].GetY())) != checkLength)
            cout << "Noi?iiu ia i?aiu iieo?eeenu - yoi ia nianai i?aaeeuiue iiiaioaieuiee :(" << endl;
        else {
            for (int i = 1; i < chain.size() - 1; i++) {
                Point c(chain[i - 1].GetX() - chain[i].GetX(), chain[i - 1].GetY() - chain[i].GetY());
                Point d(chain[i + 1].GetX() - chain[i].GetX(), chain[i + 1].GetY() - chain[i].GetY());
                if (angle(c, d) != checkAngle) {
                    cout << "Oaeu ia i?aiu iieo?eeenu - yoi ia nianai i?aaeeuiue iiiaioaieuiee :(" << endl;
                    break;
                }
                if (sqrt((chain[i + 1].GetX() - chain[i].GetX()) * (chain[i + 1].GetX() - chain[i].GetX()) + (chain[i + 1].GetY() - chain[i].GetY()) * (chain[i + 1].GetY() - chain[i].GetY())) != checkLength) {
                    cout << "Noi?iiu ia i?aiu iieo?eeenu - yoi ia nianai i?aaeeuiue iiiaioaieuiee :(" << endl;
                    break;
                }
            }
        }
    };
    
    double Angles() {
        double Ang = (M_PI / chain.size()) * 360 / M_PI;
        return Ang;
    }

    double RadiusCC() {
        double R = (perimeter() / chain.size()) / (2 * sin(M_PI / Edge()));
        return R;
    }
};
