//
//  main.cpp
//  Point-Line
//
//  Created by 郭倜维 on 2018/11/29.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
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

class Line : public Point
{
    Point A, B;
    double d;
public:
    Line(Point &A, Point &B):Point((A.GetX()+B.GetX())/2,(A.GetY()+B.GetY())/2),A(A),B(B){d = Length();};
    double Length();
    double Distance(Point &X);
    void Display();
};

void Line :: Display()
{
    Point::Display();
}

double Line :: Length()
{
    double d;
    d = A.Point::Distance(B);
    return d;
}

double Line :: Distance(Point &X)
{
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
        return C.Distance(X);
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    double x1, y1, x2, y2;
    //double x3, y3;
    cin >>x1>>y1>>x2>>y2;
    //cin>>x3>>y3;
    Point A(x1, y1), B(x2, y2);
    //point C(x3, y3);
    Line L(A, B);
    cout<<"AB:";
    A.Display();
    cout<<"--";
    B.Display();
    cout<<",   Length=";
    cout<<L.Length()<<",   MidPoint:";
    L.Display();
    //cout<<L.Distance(C);
    return 0;
}
