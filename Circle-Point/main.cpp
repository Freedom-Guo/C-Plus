//
//  main.cpp
//  Circle-Point
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
    double Distance(Point &a);
    void Display();
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

double Point :: Distance(Point &a)
{
    double d;
    d = sqrt((x-a.GetX())*(x-a.GetX())+(y-a.GetY())*(y-a.GetY()));
    return d;
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
    cout<<"("<<GetX()<<","<<GetY()<<","<<r<<"),   ";
    cout<<"Grith="<<Girth()<<",   ";
    cout<<"Area="<<Area()<<",   ";
}

int main(int argc, const char * argv[])
{
    double x1, y1, r1, x2, y2, r2;
    cin >>x1>>y1>>r1>>x2>>y2>>r2;
    Circle A(x1,y1,r1);
    Circle B(x2,y2,r2);
    cout<<"A:";
    A.Display();
    cout<<"\n"<<"B:";
    B.Display();
    cout<<"\nA";
    A.Point::Display();
    cout<<",  B";
    B.Point::Display();
    cout<<",  Distance="<<A.Distance(B);
    return 0;
}
