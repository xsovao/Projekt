// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Application.h"
#include "LogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef MIN_SIZE
#define MIN_SIZE 300
#endif

// CLogDlg dialog

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOG_DIALOG, pParent)
	, m_csLog( L"")
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LISTING, m_csLog);
	DDX_Control(pDX, IDC_LISTING, m_ctrlLog);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
	ON_MESSAGE(WM_TEXT, OnText)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()


void CLogDlg::OnSizing(UINT nSide, LPRECT lpRect)
{
	if ((lpRect->right - lpRect->left) < MIN_SIZE)
	{
		switch (nSide)
		{
		case WMSZ_LEFT:
		case WMSZ_BOTTOMLEFT:
		case WMSZ_TOPLEFT:
			lpRect->left = lpRect->right - MIN_SIZE;
		default:
			lpRect->right = lpRect->left + MIN_SIZE;
			break;
		}
	}

	if ((lpRect->bottom - lpRect->top) < MIN_SIZE)
	{
		switch (nSide)
		{
		case WMSZ_TOP:
		case WMSZ_TOPRIGHT:
		case WMSZ_TOPLEFT:
			lpRect->top = lpRect->bottom - MIN_SIZE;
		default:
			lpRect->bottom = lpRect->top + MIN_SIZE;
			break;
		}
	}

	__super::OnSizing(nSide, lpRect);
}

void CLogDlg::OnSize(UINT nType, int cx, int cy)
{
	Default();

	if (!::IsWindow(m_ctrlLog.m_hWnd))
		return;

	m_ctrlLog.SetWindowPos(nullptr, -1, -1, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE);
}

void CLogDlg::OnClose()
{
	ShowWindow(SW_HIDE);
}

LRESULT CLogDlg::OnText(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);

	LPCTSTR pBuffer = (LPCTSTR)wParam;

	if (pBuffer == nullptr)
		m_csLog.Empty();
	else
		m_csLog += pBuffer;

	UpdateData(FALSE);

	// scroll to the last line
	SCROLLINFO si;
	memset(&si, 0, sizeof(si));
	si.cbSize = sizeof(si);
	m_ctrlLog.GetScrollInfo(SB_VERT, &si);

	if (((UINT)si.nMax) > si.nPage && (si.nPos + si.nPage) < (UINT)si.nMax)
	{
		m_ctrlLog.LineScroll(si.nMax - si.nPage - si.nPos);
	}

	return S_OK;
}
