#pragma once
class MyShape
{
public:
	CPoint m_pt;
	int xmax, xmin, ymax, ymin;
	COLORREF m_color;
	bool select;
	MyShape();
	MyShape(CPoint p, COLORREF c);
	virtual void setFirstPoint(CPoint p) = 0;
	virtual void setSecondPoint(CPoint p) = 0;
	virtual void draw(CDC *pDC) = 0;
	virtual bool setSelect(CPoint p) = 0;
	virtual void drawSelect(CDC *pDC) = 0;
	virtual void set(CPoint p1, CPoint p2) = 0;
	virtual bool drag(CPoint p1, CPoint p2) = 0;
};

