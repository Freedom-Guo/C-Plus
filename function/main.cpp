//
//  main.cpp
//  function
//
//  Created by 郭倜维 on 2018/11/29.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define Pi 3.14
using namespace std;

class Point
{
    double x, y;
public:
    Point(double x, double y);
    double GetX();
    double GetY();
    void Display();
    virtual double distance(Point &a){
        double d;
        d = sqrt((x-a.GetX())*(x-a.GetX())+(y-a.GetY())*(y-a.GetY()));
        return d;
    }
    virtual void print(){
        Display();
        cout<<"\n";};
};

Point :: Point(double x, double y) : x(x), y(y)
{
    
}

double Point :: GetX()
{
    return x;
}

double Point :: GetY()
{
    return y;
}

void Point :: Display()
{
    printf("(%.2lf,%.2lf)",x,y);
}

class Circle : public Point
{
    double r;
public:
    Circle(double x, double y, double r):Point(x,y),r(r){};
    Point GetXY();
    double GetR();
    double Girth();
    double Area();
    void Display();
    virtual void print(){
        Circle::Display();
    }
    virtual double distance(Point &a){
        double d;
        d = Point::distance(a);
        return d;
    }
};

Point Circle :: GetXY()
{
    Point C(GetX(),GetY());
    return C;
}

double Circle :: GetR()
{
    return r;
}

double Circle :: Girth()
{
    return 2*Pi*r;
}

double Circle :: Area()
{
    return Pi*r*r;
}

void Circle :: Display()
{
    cout<<"圆心";
    cout<<"("<<GetX()<<","<<GetY()<<","<<r<<"),   ";
    cout<<"Grith="<<Girth()<<",   ";
    cout<<"Area="<<Area()<<",   ";
}

class Line : public Point
{
    Point A, B;
    double d;
public:
    Line(Point &A, Point &B):Point((A.GetX()+B.GetX())/2,(A.GetY()+B.GetY())/2),A(A),B(B){d = Length();};
    double Length();
    void Display();
    virtual void print(){
        Line::Display();
        cout<<",   Length=";
        cout<<Length();
        cout<<",   MidPoint:";
        Point::Display();
        cout<<"\n";
    }
    virtual double distance(Point &X){
        if((A.GetX()-B.GetX())==0)
        {
            return abs(X.GetX()-A.GetX());
        }
        else if((A.GetY()-B.GetY())==0)
        {
            return abs(X.GetY()-A.GetY());
        }
        else
        {
            double k = (A.GetY()-B.GetY())/(A.GetX()-B.GetX());
            double k_1 =(-1.0)/k;
            double x;
            double y;
            x = (X.GetY()-A.GetY()+A.GetX()*k-X.GetX()*k_1)/(k-k_1);
            y = X.GetY()+(x-X.GetX())*k_1;
            Point C(x, y);
            return C.distance(X);
        }
    }
};

void Line :: Display()
{
    A.Display();
    cout<<"--";
    B.Display();
}

double Line :: Length()
{
    double d;
    d = A.distance(B);
    return d;
}

void print(Point &p);
double distance(Point& a, Point& b);

int main(int argc, const char * argv[])
{
    Point p1(4, 2), p2(3, 5),p3(4,1);
    Line l1(p1, p2);
    Circle c1(0, 0, 1), c2(2, 0, 1);
    cout << "Point  A: ";
    print(p1);
    cout << "Point  B: ";
    print(p2);
    cout << "Point  C: ";
    print(p3);
    cout << "\nLine   AB: ";
    print(l1);
    cout << "Line AB to point C:  " << distance(l1, p3) << endl;
    
    cout << "\nCircle A: ";
    print(c1);
    cout << "\nCircle B: ";
    print(c2);
    cout << "\nDistance=" << distance(c1, c2);
    cout << "\n";
    
    cout << "Line AB to circle B:  " << distance(l1, c2) << endl;
    
    return 0;
}

void print(Point &p)
{
    p.print();
}

double distance(Point& a, Point& b)
{
    return a.distance(b);
}
