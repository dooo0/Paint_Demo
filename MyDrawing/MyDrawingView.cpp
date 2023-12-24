
// MyDrawingView.cpp: CMyDrawingView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MyDrawing.h"
#endif

#include "MyDrawingDoc.h"
#include "MyDrawingView.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyDrawingView
struct DrawingInfo
{
	BOOL bFIll;
	CPoint ptStart;
	CPoint ptEnd;
	int nShape;
};
DrawingInfo DrawInfo;
std::vector<DrawingInfo> MyDraw;
IMPLEMENT_DYNCREATE(CMyDrawingView, CView)

BEGIN_MESSAGE_MAP(CMyDrawingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CMyDrawingView 생성/소멸


CMyDrawingView::CMyDrawingView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	
	DrawInfo.bFIll = false;
	DrawInfo.ptEnd.x = 0;
	DrawInfo.ptEnd.x = 0;
	DrawInfo.ptStart.x = 0;
	DrawInfo.ptStart.y = 0;
	DrawInfo.nShape = 0;
}

CMyDrawingView::~CMyDrawingView()
{
}

BOOL CMyDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMyDrawingView 그리기

void CMyDrawingView::OnDraw(CDC* /*pDC*/)
{
	CMyDrawingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMyDrawingView 인쇄

BOOL CMyDrawingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMyDrawingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMyDrawingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMyDrawingView 진단

#ifdef _DEBUG
void CMyDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDrawingDoc* CMyDrawingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDrawingDoc)));
	return (CMyDrawingDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyDrawingView 메시지 처리기


void CMyDrawingView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	
	CBrush myBr(RGB(255, 0, 0));//정상
	CBrush* pOldBr = NULL;

	for (int i = 0; i < MyDraw.size(); i = i++)
	{
		if (MyDraw[i].bFIll)
		{
			pOldBr = dc.SelectObject(&myBr);
		}
		///////////////////////////////////////////////
		switch (MyDraw[i].nShape)
		{
		case 0:
			dc.MoveTo(MyDraw[i].ptStart);
			dc.LineTo(MyDraw[i].ptEnd);
			break;
		case 1:
			dc.Rectangle(MyDraw[i].ptStart.x, MyDraw[i].ptStart.y, MyDraw[i].ptEnd.x, MyDraw[i].ptEnd.y);
			break;
		case 2:
			dc.Ellipse(MyDraw[i].ptStart.x, MyDraw[i].ptStart.y, MyDraw[i].ptEnd.x, MyDraw[i].ptEnd.y);
			break;
		}
		///////////////////////////////////////////////
		if (MyDraw[i].bFIll)
		{
			dc.SelectObject(pOldBr);
		}
	}
}  

void CMyDrawingView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//m_ptStart = point;
	DrawInfo.ptStart = point;
	m_bDrag = TRUE;
	CView::OnLButtonDown(nFlags, point);
}

void CMyDrawingView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		//m_ptEnd = point;
		RedrawWindow();
	}
	CView::OnMouseMove(nFlags, point);
}

void CMyDrawingView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bDrag)
	{
		//m_ptEnd = point;
		m_bDrag = FALSE;
		
		DrawInfo.ptEnd= point;
		CMyDrawingApp* pApp = (CMyDrawingApp*)AfxGetApp();
		DrawInfo.bFIll = pApp->m_bFill;
		DrawInfo.nShape = pApp->m_nShape;
		MyDraw.push_back(DrawInfo);
		RedrawWindow();
	}	
	CView::OnLButtonUp(nFlags, point);
}