
// ComPortDlg.h : файл заголовка
//

#pragma once
#include <sstream>
#include <vector>
#include "ComPortActions.h"
#include "afxwin.h"

// диалоговое окно CComPortDlg
class CComPortDlg : public CDialogEx
{
// Создание
public:
	CComPortDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString val_msg;
	afx_msg void OnBnClickedConnect();
	// com-port
	ComPortActions *com1, *com2;
	CListBox cnt_chat_area;
	afx_msg void OnCbnSelchangeSpeed();
	CComboBox cnt_speed;
	CString val_speed;
	afx_msg void OnBnClickedSend();
};
