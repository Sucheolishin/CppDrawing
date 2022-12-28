
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "homework2.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	nowSelect = false;
	m_color = RGB(0, 0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnDrawRectangle)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_WM_KEYDOWN()
	//ON_COMMAND(ID_ACTION_GROUP, &CChildView::OnActionGroup)
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CChildView::OnUpdateDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, &CChildView::OnUpdateDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAR, &CChildView::OnUpdateDrawStar)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SELECT, &CChildView::OnUpdateActionSelect)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	/*--------------double buffering-------------*/
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CRect rect;
	GetClientRect(rect);
	int w = rect.Width();
	int h = rect.Height();
	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(&dc, w, h);
	memDC.SelectObject(memBmp);
	memDC.Rectangle(rect);
	/*--------------double buffering-------------*/
	CString str;
	str.Format(_T("Number of Shapes: %d"), m_shape.GetSize());
	CString str2;
	str2.Format(_T("Number of Selected: %d"), m_select.GetSize());
	memDC.TextOutW(5, 3, str);
	memDC.TextOutW(5, 20, str2);

	POSITION pos = m_shape.GetHeadPosition();
	POSITION selPos = m_select.GetHeadPosition();


	while (pos != NULL) {
		MyShape* s = m_shape.GetNext(pos);
		s->draw(&memDC);
		if (selPos != NULL) {
			MyShape* sel = m_select.GetNext(selPos);
			sel->drawSelect(&memDC);
		}
	}
	if (mode == SELECT) {
		CPen pen(PS_DOT, 1, RGB(0, 0, 0));
		memDC.SelectObject(pen);
		memDC.SelectStockObject(NULL_BRUSH);
		memDC.Rectangle(m_drag1.x, m_drag1.y, m_drag2.x, m_drag2.y);
	}

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_color = RGB(rand() % 256, rand() % 256, rand() % 256);
	switch (mode) {
	case RECT:m_shape.AddTail(new MyRect(point, m_color)); break;
	case CIRCLE:m_shape.AddTail(new MyCircle(point, m_color)); break;
	case CURVE:m_shape.AddTail(new MyCurve(point, m_color)); break;
	case STAR:m_shape.AddTail(new MyStar(point, m_color)); break;
	case SELECT:
		POSITION pos = m_shape.GetTailPosition();
		while (pos != NULL) {						//처음부터 끝까지
			MyShape* m_s = m_shape.GetPrev(pos);
			if (m_s->setSelect(point)) {	//포인터가 도형 안에 있으면서 선택이 안되어있으면
				nowSelect = true;
				m_move1 = point;
				if ((nFlags & MK_SHIFT) == MK_SHIFT) {
					if (m_s->select) {
						break;
					}
					m_select.AddTail(m_s);
					break;
				}
				POSITION s = m_select.GetHeadPosition();
				while (s != NULL) {
					MyShape* tmp = m_shape.GetNext(s);
					tmp->select = false;
				}
				m_select.RemoveAll();
				m_select.AddTail(m_s);
				break;
			}
		}
		if (!nowSelect) {
			POSITION s = m_select.GetHeadPosition();
			while (s != NULL) {
				MyShape* tmp = m_shape.GetNext(s);
				tmp->select = false;
			}
			m_select.RemoveAll();
			m_drag1 = point;
			m_drag2 = point;
		}
		nowSelect = false;
		break;
	}
	Invalidate();
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (mode != SELECT) {
		POSITION pos = m_shape.GetTailPosition();
		MyShape* cur = m_shape.GetAt(pos);
		cur->setSecondPoint(point);
	}
	else {
		if (m_select.GetSize() == 0)
			m_drag2 = point;
		POSITION pos = m_shape.GetHeadPosition();
		while (pos != NULL) {
			MyShape* i = m_shape.GetNext(pos);
			if (i->drag(m_drag2, m_drag1)) {
				m_select.AddTail(i);
				nowSelect = true;
			}
		}
		m_drag1 = 0;
		m_drag2 = 0;
	}
	Invalidate();
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && mode != SELECT) {
		POSITION pos = m_shape.GetTailPosition();
		MyShape* cur = m_shape.GetAt(pos);
		cur->setSecondPoint(point);
	}
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON && mode == SELECT) {
		m_move2 = point;
		POSITION pos = m_select.GetHeadPosition();
		while (pos != NULL) {
			MyShape* cur = m_shape.GetNext(pos);
			cur->m_pt += m_move2 - m_move1;
			cur->set(m_move2, m_move1);
		}
		m_move1 = m_move2;
		if(m_select.GetSize() == 0)
			m_drag2 = point;
	}
	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnDrawRectangle()
{
	mode = RECT;
}

void CChildView::OnDrawCircle(){mode = CIRCLE;}
void CChildView::OnDrawCurve() { mode = CURVE; }
void CChildView::OnDrawStar(){mode = STAR;}
void CChildView::OnActionSelect(){ mode = SELECT;}
BOOL CChildView::OnEraseBkgnd(CDC* pDC){return true;}

void CChildView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(3);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_DELETE) {
		POSITION pos = m_shape.GetHeadPosition();
		while (pos != NULL) {
			POSITION cur = pos;
			MyShape* i = m_shape.GetNext(pos);
			if (i->select) {
				m_shape.RemoveAt(cur);
			}
		}
		m_select.RemoveAll();
	}
	Invalidate();

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//void CChildView::OnActionGroup()
//{
//	POSITION pos = m_shape.GetTailPosition();
//	CList <MyShape*> tmp;
//	while (pos != NULL) {
//		POSITION cur = pos;
//		MyShape* i = m_shape.GetPrev(pos);
//		if (i->select) {
//			m_shape.RemoveAt(cur);
//			tmp.AddTail(i);
//		}
//	}
//	m_shape.(tmp);
//	
//}

void CChildView::OnAlignBringfront()
{
	POSITION pos = m_shape.GetTailPosition();
	while (pos != NULL) {
		POSITION cur = pos;
		MyShape* i = m_shape.GetPrev(pos);
		if (i->select) {
			m_shape.RemoveAt(cur);
			m_shape.AddTail(i);
		}
	}
}

void CChildView::OnAlignBringback()
{
	POSITION pos = m_shape.GetHeadPosition();
	while (pos != NULL) {
		POSITION cur = pos;
		MyShape* i = m_shape.GetNext(pos);
		if (i->select) {
			m_shape.RemoveAt(cur);
			m_shape.AddHead(i);
		}
	}
}


void CChildView::OnUpdateDrawRectangle(CCmdUI* pCmdUI)
{
	if (mode == RECT) {
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(false);
	}
}


void CChildView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	if (mode == CIRCLE) {
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(false);
	}
}


void CChildView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	if (mode == CURVE) {
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(false);
	}
}


void CChildView::OnUpdateDrawStar(CCmdUI* pCmdUI)
{
	if (mode == STAR) {
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(false);
	}
}


void CChildView::OnUpdateActionSelect(CCmdUI* pCmdUI)
{
	if (mode == SELECT) {
		pCmdUI->Enable(false);
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->Enable(true);
		pCmdUI->SetCheck(false);
	}
}
