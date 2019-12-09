//
//  main.cpp
//  3_final
//
//  Created by 郭倜维 on 2018/11/19.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <malloc.h>

class STACK {
    int  *const  elems;    //申请内存用于存放栈的元素
    const  int   max;    //栈能存放的最大元素个数
    int   pos;            //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);        //初始化栈：最多m个元素
    STACK(const STACK&s); //用栈s拷贝初始化栈
    virtual int  size() const;    //返回栈的最大元素个数max
    virtual  operator int () const;     //返回栈的实际元素个数pos
    virtual int operator[] (int x) const;    //取下标x处的栈元素
    virtual STACK& operator<<(int e);     //将e入栈,并返回栈
    virtual STACK& operator>>(int &e);     //出栈到e,并返回栈
    virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
    virtual void print() const;        //打印栈
    virtual ~STACK();                //销毁栈
};
using namespace std;

int main(int argc, const char * argv[])
{
    class STACK *ps = (class STACK *)malloc(sizeof(class STACK));
    class STACK *ss = (class STACK *)malloc(sizeof(class STACK));
    int argi = 3;
    
    if(!strcmp(argv[1],"-S"))
    {
        int max=atoi(argv[2]);
        ps = new STACK(max);
        printf("S %d ",max);
    }
    
    while (argi<argc)
    {
        if(!strcmp(argv[argi],"-I"))
        {
            printf("I ");
            argi++;
            while(argi<argc&&strcmp(argv[argi],"-O")&&strcmp(argv[argi],"-C")&&strcmp(argv[argi],"-A")&&strcmp(argv[argi],"-N")&&strcmp(argv[argi],"-G")&&strcmp(argv[argi],"-I"))
            {
                if(ps->size() == ps->operator int())
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int temp = atoi(argv[argi]);
                    *ps<<temp;
                    //ps->operator<<(temp);
                    argi++;
                }
            }
            ps->print();
        }
        else if(!strcmp(argv[argi],"-N"))
        {
            printf("N %d ", ps->operator int());
            argi++;
        }
        else if(!strcmp(argv[argi],"-O"))
        {
            printf("O ");
            argi++;
            int temp = atoi(argv[argi]);
            while (temp)
            {
                if(ps->operator int() == 0)
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int e;
                    *ps>>e;
                    //ps->operator>>(e);
                    temp--;
                }
            }
            ps->print();
            argi++;
        }
        else if(!strcmp(argv[argi],"-G"))
        {
            printf("G ");
            argi++;
            int temp = atoi(argv[argi]);
            if(temp<-1 || temp >= ps->operator int())
            {
                printf("E ");
                return 0;
            }
            else
            {
                printf("%d ", ps->operator[](temp));
            }
            argi++;
        }
        else if(!strcmp(argv[argi],"-C"))
        {
            printf("C ");
            ss = new STACK(*ps);
            if (ss) ss->print();
            argi++;
        }
        else if(!strcmp(argv[argi],"-A"))
        {
            printf("A ");
            argi++;
            //int temp = atoi(argv[argi]);
            ss = new STACK(*ps);
            ss->print();
            argi++;
        }
    }
    return 0;
}

//初始化栈
STACK::STACK(int m) : max(m), elems(new int[m])
{
    pos = 0;
}

//用栈s拷贝初始化栈
STACK::STACK(const STACK &s) : max(s.max), elems(new int[s.max])
{
    pos = s.pos;
    *this = s;
}

//返回栈的最大元素个数max
int  STACK::size() const
{
    return max;
}

//返回栈的实际元素个数pos
STACK::operator int() const
{
    return pos;
}

//取下标x处的栈元素
int  STACK::operator[](int x) const
{
    if (x > pos)
    {
        printf("E ");   //超过了最大下标
        return 0;
    }
    return elems[x];
}

//将e入栈,并返回栈
STACK& STACK::operator<<(int e)
{
    if (pos == max)
    {
        printf("E ");  //堆栈已满，无法插入新元素
        return *this;
    }
    elems[pos] = e;
    pos++;
    return *this;
}

//出栈到e,并返回栈
STACK& STACK::operator>> (int &e)
{
    if (pos == 0)
    {
        printf("E  ");  //栈中不存在元素
    }
    else
    {
        e = elems[pos];
        pos--;
    }
    return *this;
}

//赋s给栈,并返回被赋值的栈
STACK& STACK::operator=(const STACK&s)
{
    if(this != &s)
    {
        if (max > s.pos)
        {
            for (int i = 0; i < s.pos; i++)
            {
                *(elems + i) = *(s.elems + i);
            }
            pos = s.pos;
            return *this;
        }
        else
        {
            int **elem,*max1;
            elem = const_cast<int**> (&elems);
            *elem = (int*)malloc((s.max) * sizeof(int));
            for (int i = 0; i < s.pos; i++)
            {
                *(*elem + i) = *(s.elems + i);
            }
            max1 = const_cast<int*> (&max);
            *max1 = s.max;
            pos = s.pos;
            return *this;
        }
    }
    return *this;
}

//打印栈
void STACK::print() const
{
    int i;
    if (pos == 0)
    {
        printf("");   //栈为空
        return;
    }
    else
    {
        for (i = 0; i < pos; i++)
        {
            printf("%d ", elems[i]);
        }
    }
}

//销毁栈
STACK::~STACK()
{
    delete[] elems;
}
