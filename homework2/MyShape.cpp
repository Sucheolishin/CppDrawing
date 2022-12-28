#include "pch.h"
#include "MyShape.h"

MyShape::MyShape():m_pt(0,0) {
	xmax = 0, xmin = 0, ymax = 0, ymin = 0;
	m_color = RGB(0,0,0);
	select = false;
}

MyShape::MyShape(CPoint p, COLORREF c) {
	xmax = 0, xmin = 0, ymax = 0, ymin = 0;
	m_color = c;
	select = false;
}
