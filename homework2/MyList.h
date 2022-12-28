#pragma once
#include "MyShape.h"
class MyList :
    public MyShape
{
    MyList();
    MyList(CList <MyShape*> list);
};

