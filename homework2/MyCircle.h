#pragma once
#include "MyShape.h"
class MyCircle :
    public MyShape
{
public:
    double m_r;
    MyCircle();
    MyCircle(CPoint p, COLORREF c);
    void setFirstPoint(CPoint p);
    void setSecondPoint(CPoint p);
    void draw(CDC* pDC);
    bool setSelect(CPoint p);
    void drawSelect(CDC* pDC);
    void set(CPoint p1, CPoint p2);
    bool drag(CPoint p1, CPoint p2);
};

