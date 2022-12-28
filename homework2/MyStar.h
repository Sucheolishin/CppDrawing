#pragma once
#include "MyShape.h"
class MyStar :
    public MyShape
{
public:
    double m_r;
    MyStar();
    MyStar(CPoint p, COLORREF c);
    CPoint p[11];
    void setFirstPoint(CPoint p);
    void setSecondPoint(CPoint p);
    void draw(CDC* pDC);
    bool setSelect(CPoint p);
    void drawSelect(CDC* pDC);
    void set(CPoint p1, CPoint p2);
    bool drag(CPoint p1, CPoint p2);
};

