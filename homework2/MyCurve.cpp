#include "pch.h"
#include "MyCurve.h"
MyCurve::MyCurve() {
}

MyCurve::MyCurve(CPoint p, COLORREF c) {
	xmax = p.x;
	xmin = p.x;
	ymax = p.y;
	ymin = p.y;
	m_color = c;
	setFirstPoint(p);
}

void MyCurve::setFirstPoint(CPoint p) {
	m_pt = p;
	m_cp.push_back(m_pt - p);
}

void MyCurve::setSecondPoint(CPoint p) {
	if (xmax < p.x)
		xmax = p.x;
	if (xmin > p.x)
		xmin = p.x;
	if (ymax < p.y)
		ymax = p.y;
	if (ymin > p.y)
		ymin = p.y;
	m_cp.push_back(p- m_pt);
}

void MyCurve::draw(CDC* pDC) {
	CPen pen(BS_SOLID, 3, m_color);
	pDC->SelectObject(pen);

	if (m_cp.size() < 1) return;
	auto i = m_cp.begin();
	pDC->MoveTo(m_pt);
	while (i != m_cp.end()) {
		pDC->LineTo(m_pt + *i);
		i++;
	}
}

bool MyCurve::setSelect(CPoint p) {
	auto e = m_cp.begin();
	while (e != m_cp.end()) {
		CPoint in = (*e);
		if (m_pt.x + in.x + 10 >= p.x && m_pt.x + in.x - 10 <= p.x && m_pt.y + in.y + 10 >= p.y && m_pt.y + in.y - 10 < p.y) {
			return true;
		}
		e++;
	}
	return false;
}

void MyCurve::drawSelect(CDC* pDC) {
	select = true;
	CPen pen(PS_DOT, 1, RGB(255, 0, 0));
	pDC->SelectObject(pen);
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Rectangle(xmin - 5, ymin - 5, xmax + 5, ymax + 5);
}

void MyCurve::set(CPoint p1, CPoint p2) {
	xmin += p1.x - p2.x;
	xmax += p1.x - p2.x;
	ymin += p1.y - p2.y;
	ymax += p1.y - p2.y;
}

bool MyCurve::drag(CPoint p1, CPoint p2) {
	int pxmax = p1.x > p2.x ? p1.x : p2.x;
	int pxmin = p1.x < p2.x ? p1.x : p2.x;
	int pymax = p1.y > p2.y ? p1.y : p2.y;
	int pymin = p1.y < p2.y ? p1.y : p2.y;

	if (pxmax >= xmax && pymax >= ymax && pxmin <= xmin && pymin <= ymin) {
		return true;
	}
	return false;
}