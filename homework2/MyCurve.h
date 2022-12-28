#pragma once
#include "MyShape.h"
#include <vector>
class MyCurve :
    public MyShape
{
public:
    std::vector<CPoint>m_cp;
    MyCurve();
    MyCurve(CPoint p, COLORREF c);
    void setFirstPoint(CPoint p);
    void setSecondPoint(CPoint p);
    void draw(CDC* pDC);
    bool setSelect(CPoint p);
    void drawSelect(CDC *pDC);
    void set(CPoint p1, CPoint p2);
    bool drag(CPoint p1, CPoint p2);
};

