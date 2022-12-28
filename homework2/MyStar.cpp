#include "pch.h"
#include "MyStar.h"

MyStar::MyStar() : m_r(0.0) {
}
MyStar::MyStar(CPoint p, COLORREF c) {
	setFirstPoint(p);
	m_color = c;
}

void MyStar::setFirstPoint(CPoint p) {
	m_pt = p;
}

void MyStar::setSecondPoint(CPoint p) {
	xmax = m_pt.x;
	xmin = m_pt.x;
	ymax = m_pt.y;
	ymin = m_pt.y;
	m_r = sqrt((m_pt.x - p.x) * (m_pt.x - p.x) + (m_pt.y - p.y) * (m_pt.y - p.y));
}

void MyStar::draw(CDC* pDC) {
	CBrush brush(m_color);
	CPen pen(BS_SOLID, 3, RGB(0, 0, 0));
	pDC->SelectObject(brush);
	pDC->SelectObject(pen);
	double PI = 3.141562;

	for (int i = 0; i < 11; i++) {
		if (i % 2 == 0) {
			p[i].x = (m_pt.x + sin((2 * PI / 10 * (i % 10))) * m_r);
			p[i].y = (m_pt.y - cos((2 * PI / 10 * (i % 10))) * m_r);
		}
		if (i % 2 == 1) {
			p[i].x = (m_pt.x + sin((2 * PI / 10 * (i % 10))) * (m_r/3));
			p[i].y = (m_pt.y - cos((2 * PI / 10 * (i % 10))) * (m_r/3));
		}
		if (xmax < p[i].x)
			xmax = p[i].x;
		if (xmin > p[i].x)
			xmin = p[i].x;
		if (ymax < p[i].y)
			ymax = p[i].y;
		if (ymin > p[i].y)
			ymin = p[i].y;
	}
	pDC->Polygon(p, 10);
}

bool MyStar::setSelect(CPoint pt) {
	int cross = 0;
	for (int i = 0; i < 10; i++) {
		int j = (i + 1) % 10;
		if ((p[i].y > pt.y) != (p[j].y > pt.y)) {
			double inx = 1.0 * (p[j].x - p[i].x) * (pt.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (pt.x < inx)cross++;
		}
	}
	if (cross % 2 != 0) {
		return true;
	}
	return false;
}

void MyStar::drawSelect(CDC* pDC) {
	select = true;
	CPen pen(PS_DOT, 1, RGB(255, 0, 0));
	pDC->SelectObject(pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(xmin - 5, ymin - 5, xmax + 5, ymax + 5);
}

void MyStar::set(CPoint p1, CPoint p2) {
	xmin += p1.x - p2.x;
	xmax += p1.x - p2.x;
	ymin += p1.y - p2.y;
	ymax += p1.y - p2.y;
}

bool MyStar::drag(CPoint p1, CPoint p2) {
	int pxmax = p1.x > p2.x ? p1.x : p2.x;
	int pxmin = p1.x < p2.x ? p1.x : p2.x;
	int pymax = p1.y > p2.y ? p1.y : p2.y;
	int pymin = p1.y < p2.y ? p1.y : p2.y;

	if (pxmax >= xmax && pymax >= ymax && pxmin <= xmin && pymin <= ymin) {
		return true;
	}
	return false;
}