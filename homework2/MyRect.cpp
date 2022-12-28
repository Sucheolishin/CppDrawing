#include "pch.h"
#include "MyRect.h"

MyRect::MyRect() : m_w(0), m_h(0) {
	xmax = m_pt.x > m_pt.x - m_w ? m_pt.x : m_pt.x - m_w;
	xmin = m_pt.x < m_pt.x - m_w ? m_pt.x : m_pt.x - m_w;
	ymax = m_pt.y > m_pt.y - m_h ? m_pt.y : m_pt.y - m_h;
	ymin = m_pt.y < m_pt.y - m_h ? m_pt.y : m_pt.y - m_h;
}

MyRect::MyRect(CPoint p, COLORREF c) : m_w(0), m_h(0) {
	m_color = c;
	setFirstPoint(p);
}

void MyRect::setFirstPoint(CPoint p) {
	m_pt = p;
}

void MyRect::setSecondPoint(CPoint p) {
	m_w = m_pt.x - p.x;
	m_h = m_pt.y - p.y;
	xmax = m_pt.x > m_pt.x - m_w ? m_pt.x : m_pt.x - m_w;
	xmin = m_pt.x < m_pt.x - m_w ? m_pt.x : m_pt.x - m_w;
	ymax = m_pt.y > m_pt.y - m_h ? m_pt.y : m_pt.y - m_h;
	ymin = m_pt.y < m_pt.y - m_h ? m_pt.y : m_pt.y - m_h;
}

void MyRect::draw(CDC* pDC) {
	CBrush brush(m_color);
	CPen pen(BS_SOLID, 3, RGB(0, 0, 0));
	pDC->SelectObject(brush);
	pDC->SelectObject(pen);
	pDC->Rectangle(m_pt.x, m_pt.y, m_pt.x - m_w,m_pt.y - m_h);
}

bool MyRect::setSelect(CPoint p) {
	if (xmax >= p.x && ymax >= p.y && xmin <= p.x && ymin <= p.y) {
		return true;
	}
	return false;
}

void MyRect::drawSelect(CDC* pDC) {
	select = true;
	CPen pen(PS_DOT, 1, RGB(255, 0, 0));
	pDC->SelectObject(pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(xmin - 5, ymin - 5, xmax +5, ymax + 5);
}

void MyRect::set(CPoint p1, CPoint p2) {
	xmin += p1.x - p2.x;
	xmax += p1.x - p2.x;
	ymin += p1.y - p2.y;
	ymax += p1.y - p2.y;
}

bool MyRect::drag(CPoint p1, CPoint p2) {
	int pxmax = p1.x > p2.x ? p1.x : p2.x;
	int pxmin = p1.x < p2.x ? p1.x : p2.x;
	int pymax = p1.y > p2.y ? p1.y : p2.y;
	int pymin = p1.y < p2.y ? p1.y : p2.y;

	if (pxmax >= xmax && pymax >= ymax && pxmin <= xmin && pymin <= ymin) {
		return true;
	}
	return false;
}