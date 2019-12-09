//
//  main.cpp
//  1
//
//  Created by 郭倜维 on 2018/10/9.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct STACK{
    int *elems;//申请内存用于存放栈的元素
    int max;
    int pos;
};

void initSTACK(STACK *const p, int m);//初始化p指向的栈：最多m个元素
void initStack(STACK *const p, const STACK&s);//用栈s初始化p指向的栈
int size(const STACK *const p);//返回p指向的栈的最大元素个数max
int howMany(const STACK *const p);//返回p指向的栈的实际元素个数pos
int getelem(const STACK*const p, int x);//取下标x处的栈元素
STACK *const push(STACK *const p, int e);//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e);//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s);//赋s给p指的栈,并返回p
void print(const STACK*const p);//打印p指向的栈
void destroySTACK(STACK*const p);//销毁p指向的栈

int flag = 0;

int main(int argc, const char * argv[])
{
    STACK s;
    STACK *ps=&s;
    int argi=3;
    
    if(!strcmp(argv[1],"-s"))
    {
        int max=atoi(argv[2]);
        initSTACK(ps,max);
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
                if(ps->pos==ps->max)
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int ele=atoi(argv[argi]);
                    ps=push(ps,ele);
                    argi++;
                }
            }
            print(ps);
        }
        
        else if(!strcmp(argv[argi],"-N")) //元素个数pos
        {
            printf("N %d ",howMany((ps)));
            argi++;
        }
        
        else if(!strcmp(argv[argi],"-O")) //出栈
        {
            printf("O ");
            argi++;
            int outnum=atoi(argv[argi]);
            while(outnum)
            {
                if(ps->pos==0)
                {
                    printf("E ");
                    return 0;
                }
                else
                {
                    int elem;
                    ps=pop(ps,elem);
                    outnum--;
                }
            }
            print(ps);
            argi++;
        }
        
        else if(!strcmp(argv[argi],"-G"))
        {
            printf("G ");
            argi++;
            int x=atoi(argv[argi]);
            if(x<-1||x>=ps->pos)
            {
                printf("E ");
                return 0;
            }
            else
            {
                printf("%d ",getelem(ps,x));
                argi++;
            }
        }
        
        else if(!strcmp(argv[argi],"-C"))
        {
            printf("C ");
            STACK *temp;
            temp=ps;
            STACK news;
            ps=&news;
            initStack(ps,*temp);
            print(ps);
            argi++;
        }
        
        else if(!strcmp(argv[argi],"-A"))
        {
            printf("A ");
            argi++;
            STACK *temp;
            temp=ps;
            STACK news;
            ps=&news;
            
            int newmax=atoi(argv[argi]);
            initSTACK(ps,newmax);
            ps=assign(ps,*temp);
            print(ps);
            argi++;
        }
    }
    
    return 0;
}

void initSTACK(STACK *const p, int m)//初始化p指向的栈：最多m个元素
{
    p->max = m;
    p->elems = (int*)malloc(m*sizeof(int));
    p->pos = 0;
}

void initStack(STACK *const p, const STACK&s)//用栈s初始化p指向的栈
{
    initSTACK(p, s.max);
    int i;
    if(s.elems == NULL)
    {
        printf("S=NULL!\n");
    }
    else
        for(i=0; i<(s.pos); i++)
        {
            p->elems[i] = s.elems[i];
            p->pos++;
        }
}

int size(const STACK *const p)//返回p指向的栈的最大元素个数max
{
    return p->max;
}

int howMany(const STACK *const p)//返回p指向的栈的实际元素个数pos
{
    return p->pos;
}

int getelem(const STACK*const p, int x)//取下标x处的栈元素
{
    return p->elems[x];
}

STACK *const push(STACK *const p, int e)//将e入栈，并返回p
{
    if(p->pos == p->max)
    {
        printf("E ");
    }
    else
    {
        p->elems[p->pos] = e;
        p->pos++;
        return p;
    }
    return 0;
}

STACK *const pop(STACK *const p, int &e)//出栈到e，并返回p
{
    if(p->pos == 0)
    {
        printf("E ");
    }
    else
    {
        e=p->elems[p->pos-1];
        p->pos--;
        flag = 1;
    }
    return p;
}

STACK *const assign(STACK*const p, const STACK&s)//赋s给p指的栈,并返回p
{
    free(p->elems);
    p->max = s.max;
    p->pos = s.pos;
    p->elems = new int[p->max];
    for(int i = 0; i < p->pos; i++)
        p->elems[i] = s.elems[i];
    return p;

}

void print(const STACK*const p)//打印p指向的栈
{
    int i;
    if(p->pos == 0)
    {
        printf("");
    }
    else
    {
        for(i=0; i<=p->pos-1; i++)
        {
            printf("%d  ", p->elems[i]);
        }
    }
}

