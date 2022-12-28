
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include "MyRect.h"
#include "MyShape.h"
#include "MyCircle.h"
#include "MyCurve.h"
#include "MyStar.h"
#include "MyList.h"
// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();
	COLORREF m_color;
// 특성입니다.
public:
	CList <MyShape*> m_shape;
	CList <MyShape*> m_select;
	bool nowSelect;
	CPoint m_move1;
	CPoint m_move2;
	CPoint m_drag1;
	CPoint m_drag2;
// 작업입니다.
public:
	enum m_shapes { RECT, CIRCLE ,CURVE, STAR, SELECT};
	m_shapes mode = RECT;

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();
	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawRectangle();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawCurve();
	afx_msg void OnDrawStar();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnActionSelect();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnActionGroup();
	afx_msg void OnAlignBringfront();
	afx_msg void OnAlignBringback();
	afx_msg void OnUpdateDrawRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawStar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActionSelect(CCmdUI* pCmdUI);
};

