//
//  main.cpp
//  4_final
//
//  Created by 郭倜维 on 2018/11/20.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

using namespace std;

class STACK {
    int  *const  elems;    //申请内存用于存放栈的元素
    const  int   max;    //栈能存放的最大元素个数
    int   pos;            //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m);        //初始化栈：最多m个元素
    STACK(const STACK&s); //用栈s拷贝初始化栈
    virtual int  size() const;    //返回栈的最大元素个数max
    virtual operator int () const;     //返回栈的实际元素个数pos
    virtual int operator[] (int x) const;    //取下标x处的栈元素
    virtual STACK& operator<<(int e);     //将e入栈,并返回栈
    virtual STACK& operator>>(int &e);     //出栈到e,并返回栈
    virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
    virtual void print() const;        //打印栈
    virtual ~STACK();                //销毁栈
};

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
        e = elems[pos-1];
    }
    pos--;
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

class QUEUE : public STACK{
    STACK s2;
public:
    QUEUE(int m);        //初始化循环队列：elems有m个元素
    QUEUE(const QUEUE&s);   //用队列s拷贝初始化队列
    virtual operator int() const;  //返回队列的实际元素个数
    virtual int full() const;               //返回队列是否已满，满返回1，否则返回0
    virtual int operator[ ](int x)const;   //取下标为x的元素,第1个元素下标为0
    virtual QUEUE& operator<<(int e);     //将e入队列,并返回队列
    virtual QUEUE& operator>>(int &e);    //出队列到e,并返回队列
    virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
    virtual void print() const;            //打印队列
    virtual ~QUEUE();                    //销毁队列
};

int main(int argc, const char * argv[])
{
    class QUEUE *pq = (class QUEUE *)malloc(sizeof(class QUEUE));
    class QUEUE *sq = (class QUEUE *)malloc(sizeof(class QUEUE));
    
    int argi = 3;
    
    if(!strcmp(argv[1],"-S"))
    {
        int max=atoi(argv[2]);
        pq = new QUEUE(max);
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
                if(pq->full())
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int temp = atoi(argv[argi]);
                    pq->operator<<(temp);
                    argi++;
                }
            }
            pq->print();
        }
        else if(!strcmp(argv[argi],"-N"))
        {
            printf("N %d ", pq->operator int());
            argi++;
        }
        else if(!strcmp(argv[argi],"-O"))
        {
            printf("O ");
            argi++;
            int temp = atoi(argv[argi]);
            while (temp)
            {
                if(pq->operator int() == 0)
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int e;
                    pq->operator>>(e);
                }
                temp--;
            }
            pq->print();
            argi++;
        }
        else if(!strcmp(argv[argi],"-G"))
        {
            printf("G ");
            argi++;
            int temp = atoi(argv[argi]);
            if(temp<-1 || temp >= pq->operator int())
            {
                printf("E ");
                return 0;
            }
            else
            {
                printf("%d ", pq->operator[](temp));
            }
            argi++;
        }
        else if(!strcmp(argv[argi],"-C"))
        {
            printf("C ");
            QUEUE *newQueue;
            newQueue = new QUEUE(*pq);
            if (newQueue) newQueue->print();
            delete newQueue;
            argi++;
        }
        else if(!strcmp(argv[argi],"-A"))
        {
            printf("A ");
            argi++;
            sq = new QUEUE(pq->operator int());
            sq->operator=(*pq);
            sq->print();
            argi++;
        }
    }
    return 0;
}

//初始化循环队列：elems有m个元素
QUEUE::QUEUE(int m) :STACK(m), s2(m)
{
    return;
}

//用队列s拷贝初始化队列
QUEUE::QUEUE(const QUEUE &s) : STACK(s.STACK::size()), s2(s.s2.size())
{
    *this = s;
}

//返回队列的实际元素个数
QUEUE::operator int() const
{
    return s2 + STACK::operator int();
}

//返回队列是否已满，满返回1，否则返回0
int  QUEUE::full() const {
    if (s2 == s2.size() && STACK::operator int() == STACK::size())
    {
        return 1;
    }
    return 0;
}

//取下标为x的元素,第1个元素下标为0
int  QUEUE::operator[](int x) const
{
    if ((this->STACK::operator int() + s2 == 0) || (x > (s2.size() * 2 - 1)) ){
        printf("E ");
        return 0;
    }
    
    if (s2 == 0)
    {
        return this->STACK::operator[](x);
    }
    else
    {
        if (x >= s2)
        {
            return this->STACK::operator[](x - s2);
        }
        else
        {
            return s2[s2 - 1 - x];
        }
    }
}

//将e入队列,并返回队列
QUEUE& QUEUE::operator<<(int e)
{
    int k;
    //如果队列满了，那么返回错误
    if (full())
    {
        printf("E ");
        return *this;
    }
    
    //如果队列2不为0，且队列1满，那么错误。
    if (s2 != 0 && STACK::operator int() == this->STACK::size())
    {
        printf("E ");
        exit(1);
    }
    
    //如果队列1没有满，那么进入队列1
    if (STACK::operator int() <  this->STACK::size())
    {
        STACK::operator<<(e);
        return *this;
    }
    else
    {
        //如果队列1满了，将队列1的内容倒入队列2
        while (STACK::operator int() != 0)
        {
            STACK::operator>>(k);
            s2 << k;
        }
        STACK::operator<<(e);
    }
    return *this;
}

//出队列到e,并返回队列
QUEUE& QUEUE::operator>> (int &e)
{
    if (STACK::operator int() == 0 && s2 == 0)
    {
        printf("");
        return *this;
    }
    else if(s2 != 0)
    {
        s2>>e;
    }
    else
    {
        int s1_size = STACK :: operator int();
        int e = 0;
        for(int i = 0; i < s1_size; i++)
        {
            STACK::operator >> (e);
            s2 << e;
        }
        s2 >> e;
    }
    return *this;
}

//赋s给队列,并返回被赋值的队列
QUEUE& QUEUE::operator=(const QUEUE&s)
{
    if(this != &s)
    {
        s2=s.s2;
        STACK::operator=(s);
    }
    return *this;
}


//打印队列
void QUEUE::print() const
{
    int i;
    if (!(STACK::operator int() != 0 || s2 != 0))
    {
        printf("");
    }
    if(this->operator int() == 0)
    {
        printf("");
    }
    
    if (s2 != 0)
    {
        for (i = s2 - 1; i >= 0; i--)
        {
            printf("%d ", s2[i]);
        }
    }
    
    if (STACK::operator int() != 0)
    {
        for (i = 0; i < STACK::operator int(); i++)
        {
            printf("%d ", STACK::operator[](i));
        }
    }
    
}

//销毁队列
QUEUE::~QUEUE()
{
    
}

