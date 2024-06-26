﻿


#include "pch.h"
#include "TimbreEditor.h"
#include "afxdialogex.h"
#include "TimbreTab.h"
#include "ModuleTab.h"



IMPLEMENT_DYNAMIC(CTimbreTab, CDialogEx)



CTimbreTab::~CTimbreTab()
{
}



CTimbreTab::CTimbreTab(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_TIMBRE_TAB, pParent)
,mx(-1)
,my(-1)
,m_bEditing(false)
,m_iOperator(-1)
,m_bHighLight(false)
{
}



void CTimbreTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIMBRE_ALG0_STATIC, m_aCStaticALG[0]);
	DDX_Control(pDX, IDC_TIMBRE_ALG1_STATIC, m_aCStaticALG[1]);
	DDX_Control(pDX, IDC_TIMBRE_ALG2_STATIC, m_aCStaticALG[2]);
	DDX_Control(pDX, IDC_TIMBRE_ALG3_STATIC, m_aCStaticALG[3]);
	DDX_Control(pDX, IDC_TIMBRE_ALG4_STATIC, m_aCStaticALG[4]);
	DDX_Control(pDX, IDC_TIMBRE_ALG5_STATIC, m_aCStaticALG[5]);
	DDX_Control(pDX, IDC_TIMBRE_ALG6_STATIC, m_aCStaticALG[6]);
	DDX_Control(pDX, IDC_TIMBRE_ALG7_STATIC, m_aCStaticALG[7]);
}



BEGIN_MESSAGE_MAP(CTimbreTab, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



void CTimbreTab::OnCancel(){}



HBRUSH CTimbreTab::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	auto hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	switch (pWnd->GetDlgCtrlID()){
		case IDC_TIMBRE_EN_STATIC:{		SetColor(pDC, 0, 0); break; }
		case IDC_TIMBRE_ALG_STATIC:{	SetColor(pDC, 1, 0); break; }
		case IDC_TIMBRE_FB_STATIC:{		SetColor(pDC, 2, 0); break; }
		case IDC_TIMBRE_NUM_STATIC:{	SetColor(pDC, 3, 0); break; }
		case IDC_TIMBRE_KML_STATIC:{	SetColor(pDC, 4, 0); break; }
		case IDC_TIMBRE_KMH_STATIC:{	SetColor(pDC, 5, 0); break; }
		case IDC_TIMBRE_EPR_STATIC:{	SetColor(pDC, 6, 0); break; }
		case IDC_TIMBRE_KT_STATIC:{		SetColor(pDC, 7, 0); break; }
		case IDC_TIMBRE_DT_STATIC:{		SetColor(pDC, 8, 0); break; }
		
		case IDC_TIMBRE_EN1_STATIC:{	SetColor(pDC, 0, 1); break; }
		case IDC_TIMBRE_AL1_STATIC:{	SetColor(pDC, 1, 1); break; }
		case IDC_TIMBRE_DL1_STATIC:{	SetColor(pDC, 2, 1); break; }
		case IDC_TIMBRE_SL1_STATIC:{	SetColor(pDC, 3, 1); break; }
		case IDC_TIMBRE_RL1_STATIC:{	SetColor(pDC, 4, 1); break; }
		case IDC_TIMBRE_TL1_STATIC:{	SetColor(pDC, 5, 1); break; }
		case IDC_TIMBRE_MT1_STATIC:{	SetColor(pDC, 6, 1); break; }
		case IDC_TIMBRE_VOID1_0_STATIC:{SetColor(pDC, 7, 1); break; }
		case IDC_TIMBRE_VOID1_1_STATIC:{SetColor(pDC, 8, 1); break; }
		
		case IDC_TIMBRE_EN2_STATIC:{	SetColor(pDC, 0, 2); break; }
		case IDC_TIMBRE_AL2_STATIC:{	SetColor(pDC, 1, 2); break; }
		case IDC_TIMBRE_DL2_STATIC:{	SetColor(pDC, 2, 2); break; }
		case IDC_TIMBRE_SL2_STATIC:{	SetColor(pDC, 3, 2); break; }
		case IDC_TIMBRE_RL2_STATIC:{	SetColor(pDC, 4, 2); break; }
		case IDC_TIMBRE_TL2_STATIC:{	SetColor(pDC, 5, 2); break; }
		case IDC_TIMBRE_MT2_STATIC:{	SetColor(pDC, 6, 2); break; }
		case IDC_TIMBRE_VOID2_0_STATIC:{SetColor(pDC, 7, 2); break; }
		case IDC_TIMBRE_VOID2_1_STATIC:{SetColor(pDC, 8, 2); break; }
		
		case IDC_TIMBRE_EN3_STATIC:{	SetColor(pDC, 0, 3); break; }
		case IDC_TIMBRE_AL3_STATIC:{	SetColor(pDC, 1, 3); break; }
		case IDC_TIMBRE_DL3_STATIC:{	SetColor(pDC, 2, 3); break; }
		case IDC_TIMBRE_SL3_STATIC:{	SetColor(pDC, 3, 3); break; }
		case IDC_TIMBRE_RL3_STATIC:{	SetColor(pDC, 4, 3); break; }
		case IDC_TIMBRE_TL3_STATIC:{	SetColor(pDC, 5, 3); break; }
		case IDC_TIMBRE_MT3_STATIC:{	SetColor(pDC, 6, 3); break; }
		case IDC_TIMBRE_VOID3_0_STATIC:{SetColor(pDC, 7, 3); break; }
		case IDC_TIMBRE_VOID3_1_STATIC:{SetColor(pDC, 8, 3); break; }
		
		case IDC_TIMBRE_EN4_STATIC:{	SetColor(pDC, 0, 4); break; }
		case IDC_TIMBRE_AL4_STATIC:{	SetColor(pDC, 1, 4); break; }
		case IDC_TIMBRE_DL4_STATIC:{	SetColor(pDC, 2, 4); break; }
		case IDC_TIMBRE_SL4_STATIC:{	SetColor(pDC, 3, 4); break; }
		case IDC_TIMBRE_RL4_STATIC:{	SetColor(pDC, 4, 4); break; }
		case IDC_TIMBRE_TL4_STATIC:{	SetColor(pDC, 5, 4); break; }
		case IDC_TIMBRE_MT4_STATIC:{	SetColor(pDC, 6, 4); break; }
		case IDC_TIMBRE_VOID4_0_STATIC:{SetColor(pDC, 7, 4); break; }
		case IDC_TIMBRE_VOID4_1_STATIC:{SetColor(pDC, 8, 4); break; }
		
		case IDC_TIMBRE_VOID0_STATIC2:{	SetColor(pDC, 0, 5); break; }
		case IDC_TIMBRE_AR_STATIC:{		SetColor(pDC, 1, 5); break; }
		case IDC_TIMBRE_DR_STATIC:{		SetColor(pDC, 2, 5); break; }
		case IDC_TIMBRE_SR_STATIC:{		SetColor(pDC, 3, 5); break; }
		case IDC_TIMBRE_RR_STATIC:{		SetColor(pDC, 4, 5); break; }
		case IDC_TIMBRE_BIT_STATIC:{	SetColor(pDC, 5, 5); break; }
		case IDC_TIMBRE_LEN_STATIC:{	SetColor(pDC, 6, 5); break; }
		case IDC_TIMBRE_VOID3_STATIC2:{	SetColor(pDC, 7, 5); break; }
		case IDC_TIMBRE_VOID4_STATIC2:{	SetColor(pDC, 8, 5); break; }
		
		case IDC_TIMBRE_OP1_STATIC:{	SetColor(pDC, 0); break; }
		case IDC_TIMBRE_OP2_STATIC:{	SetColor(pDC, 1); break; }
		case IDC_TIMBRE_OP3_STATIC:{	SetColor(pDC, 2); break; }
		case IDC_TIMBRE_OP4_STATIC:{	SetColor(pDC, 3); break; }
	}
	
	return hbr;//(HBRUSH)GetStockObject(DKGRAY_BRUSH);
}



BOOL CTimbreTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	SetPicture(0);
	
	return FALSE;
}



void CTimbreTab::SetColor(CDC* pDC, int x, int y)
{
	auto b = (mx == x && my == y);
	pDC->SetTextColor((b)? ((m_bEditing)? RGB(255,160,128): GetSysColor(COLOR_3DFACE)): GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkColor((b)? GetSysColor(COLOR_WINDOWTEXT): GetSysColor(COLOR_3DFACE));
}



void CTimbreTab::SetColor(CDC* pDC, int iOperator)
{
	auto b = (m_iOperator == iOperator && m_bHighLight);
	pDC->SetTextColor((b)? RGB(255,160,128): GetSysColor(COLOR_WINDOWTEXT));
	pDC->SetBkColor((b)? GetSysColor(COLOR_WINDOWTEXT): GetSysColor(COLOR_3DFACE));
}



void CTimbreTab::SetCur(int x, int y, bool bEditing)
{
	mx = x;
	my = y;
	m_bEditing = bEditing;
}



void CTimbreTab::SetPicture(int ALG)
{
	for (int i = 0; i <= 7; ++i){
		m_aCStaticALG[i].ShowWindow((ALG == i)? SW_SHOW: SW_HIDE);
	}
}



void CTimbreTab::SetOperator(int iOperator, bool bHighLight)
{
	m_iOperator = iOperator;
	m_bHighLight = bHighLight;
	
	switch (m_iOperator){
		case 0:{	GetDlgItem(IDC_TIMBRE_OP1_STATIC)->RedrawWindow();	break;	}
		case 1:{	GetDlgItem(IDC_TIMBRE_OP2_STATIC)->RedrawWindow();	break;	}
		case 2:{	GetDlgItem(IDC_TIMBRE_OP3_STATIC)->RedrawWindow();	break;	}
		case 3:{	GetDlgItem(IDC_TIMBRE_OP4_STATIC)->RedrawWindow();	break;	}
	}
}
