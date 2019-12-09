//
//  main.cpp
//  2_final
//
//  Created by 郭倜维 on 2018/10/23.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

class STACK{
    int *const elems; //申请内存用于存放栈的元素
    const int max;  //栈能存放的最大元素个数
    int pos; //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m); //初始化栈：最多m个元素
    STACK(const STACK&s); //用栈s拷贝初始化栈
    int size() const; //返回栈的最大元素个数max
    int howMany() const; //返回栈的实际元素个数pos
    int getelem(int x) const; //取下标x处的栈元素
    STACK& push(int e); //将e入栈,并返回栈
    STACK& pop(int &e); //出栈到e,并返回栈
    STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
    void print() const; //打印栈
    ~STACK(); //销毁栈
};

//int flag = 0;

int main(int argc, const char * argv[])
{
    int argi=3;
    class STACK *ps = (class STACK *)malloc(sizeof(class STACK));
    class STACK *ss = (class STACK *)malloc(sizeof(class STACK));
    
    if(!strcmp(argv[1],"-S"))
    {
        int max=atoi(argv[2]);
        STACK s(max);
        ps=&s;
        printf("S %d ",max);
    }
    
    while(argi<argc)
    {
        if(!strcmp(argv[argi],"-I")) //入栈
        {
            printf("I ");
            argi++;
            while(argi<argc&&strcmp(argv[argi],"-O")&&strcmp(argv[argi],"-C")&&strcmp(argv[argi],"-A")&&strcmp(argv[argi],"-N")&&strcmp(argv[argi],"-G")&&strcmp(argv[argi],"-I"))
            {
                if(ps->howMany() == ps->size())
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int ele=atoi(argv[argi]);
                    ps->push(ele);
                    argi++;
                }
            }
            ps->print();
        }
        
        else if(!strcmp(argv[argi],"-N")) //元素个数pos
        {
            printf("N %d ",ps->howMany());
            argi++;
        }
        
        else if(!strcmp(argv[argi],"-O")) //出栈
        {
            printf("O ");
            argi++;
            int outnum=atoi(argv[argi]);
            while(outnum)
            {
                if(ps->howMany()==0)
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int elem;
                    ps->pop(elem);
                    outnum--;
                }
            }
            ps->print();
            argi++;
        }
        
        else if(!strcmp(argv[argi],"-G"))
        {
            printf("G ");
            argi++;
            int x=atoi(argv[argi]);
            if(x<-1||x>=ps->howMany())
            {
                printf("E ");
                return 0;
            }
            else
            {
                printf("%d ",ps->getelem(x));
                argi++;
            }
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

STACK::STACK(int m):max(m),elems(new int[m])
{
    pos = 0;
}

STACK::STACK(const STACK&s):max(s.max),elems(s.elems)
{
    pos = s.pos;
}

int STACK::size()const
{
    return max;
}

int STACK::getelem(int x)const
{
    if(pos == 0)
    {
        return -1;
    }
    else
    {
        if(x>pos)
        {
            return -1;
        }
        else
            return elems[x];
    }
    return -1;
}

int STACK::howMany()const
{
    return pos;
}

STACK&STACK::push(int e)
{
    if(pos>=max)
    {
        //cout<<"The space is not enough!!\n";
    }
    else
    {
        *(elems+pos) = e;
        pos++;
        //cout<<*(elems+pos-1);
    }
    return (*this);
}

STACK&STACK::pop(int &e)
{
    if(pos == 0)
    {
        //cout<<"The stack is empty!!!\n";
    }
    else
    {
        e = *(elems+pos-1);
        pos--;
    }
    return (*this);
}

STACK&STACK::assign(const STACK &s)
{
    int i;
    for (i = 0; i<s.pos && i<this->max; i++)
    {
        elems[i] = s.elems[i];
    }
    pos = i;
    return *this;
}

void STACK::print()const
{
    //cout<<"The max is:"<<max<<endl;
    //cout<<"This element at present is:"<<pos<<endl;
    //cout<<"The inner element is:";
    int i;
    if(pos == 0)
    {
        printf("");
    }
    else
    {
        for(i=0; i<=pos-1; i++)
        {
            printf("%d ", elems[i]);
        }
    }
}

STACK::~STACK()
{
    delete []elems;
    pos = 0;
    //max = 0;
}

