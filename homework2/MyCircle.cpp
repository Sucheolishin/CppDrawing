#include "pch.h"
#include "MyCircle.h"

MyCircle::MyCircle():m_r(0.0) {
}
MyCircle::MyCircle(CPoint p, COLORREF c):m_r(0.0) {
	m_color = c;
	setFirstPoint(p);
}
void MyCircle::setFirstPoint(CPoint p) {
	m_pt = p;
}

void MyCircle::setSecondPoint(CPoint p) {
	m_r = sqrt((m_pt.x - p.x) * (m_pt.x - p.x) + (m_pt.y - p.y) * (m_pt.y - p.y));
	xmax = m_pt.x + m_r;
	xmin = m_pt.x - m_r;
	ymax = m_pt.y + m_r;
	ymin = m_pt.y - m_r;
}

void MyCircle::draw(CDC* pDC) {
	CBrush brush(m_color);
	CPen pen(BS_SOLID, 3, RGB(0, 0, 0));
	pDC->SelectObject(brush);
	pDC->SelectObject(pen);
	pDC->Ellipse(m_pt.x + m_r, m_pt.y + m_r, m_pt.x - m_r, m_pt.y - m_r);
}

bool MyCircle::setSelect(CPoint p) {
	double tmp = sqrt((m_pt.x - p.x) * (m_pt.x - p.x) + (m_pt.y - p.y) * (m_pt.y - p.y));
	if (m_r >= tmp) {
		return true;
	}
	return false;
}

void MyCircle::drawSelect(CDC* pDC) {
	select = true;
	CPen pen(PS_DOT, 1, RGB(255, 0, 0));
	pDC->SelectObject(pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(xmin - 5, ymin - 5, xmax + 5, ymax + 5);
}

void MyCircle::set(CPoint p1, CPoint p2) {
	xmin += p1.x - p2.x;
	xmax += p1.x - p2.x;
	ymin += p1.y - p2.y;
	ymax += p1.y - p2.y;
}

bool MyCircle::drag(CPoint p1, CPoint p2) {
	int pxmax = p1.x > p2.x ? p1.x : p2.x;
	int pxmin = p1.x < p2.x ? p1.x : p2.x;
	int pymax = p1.y > p2.y ? p1.y : p2.y;
	int pymin = p1.y < p2.y ? p1.y : p2.y;

	if (pxmax >= xmax && pymax >= ymax && pxmin <= xmin && pymin <= ymin) {
		return true;
	}
	return false;
}