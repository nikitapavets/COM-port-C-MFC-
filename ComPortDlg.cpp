
// ComPortDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "ComPort.h"
#include "ComPortDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CListBox *cnt_chat_area_outer;
ComPortActions *com2_outer;
HANDLE hEventFirstClient = CreateEvent(NULL, FALSE, FALSE, "updateFirstClient");
HANDLE hEventSecondClient = CreateEvent(NULL, FALSE, FALSE, "updateSecondClient");
bool firstClient = true;

UINT ThreadFirstClient(LPVOID param) {

	while (1) {

		WaitForSingleObject(hEventFirstClient, INFINITE);
		string answer = com2_outer->getMsg();
		cnt_chat_area_outer->AddString(answer.c_str());
	}

	return 0;
}

UINT ThreadSecondClient(LPVOID param) {

	while (1) {

		WaitForSingleObject(hEventSecondClient, INFINITE);
		string answer = com2_outer->getMsg();
		cnt_chat_area_outer->AddString(answer.c_str());
	}

	return 0;
}

void StartFirstClient() {
	SetEvent(hEventFirstClient);
}

void StartSecondClient() {
	SetEvent(hEventSecondClient);
}


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CComPortDlg



CComPortDlg::CComPortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COMPORT_DIALOG, pParent)
	, val_msg (_T(""))
	, val_speed(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MSG, val_msg);
	DDX_Control(pDX, IDC_CHAT_LIST, cnt_chat_area);
	DDX_Control(pDX, IDC_SPEED, cnt_speed);
	DDX_CBString(pDX, IDC_SPEED, val_speed);
}

BEGIN_MESSAGE_MAP(CComPortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, &CComPortDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CONNECT, &CComPortDlg::OnBnClickedConnect)
	ON_CBN_SELCHANGE(IDC_SPEED, &CComPortDlg::OnCbnSelchangeSpeed)
END_MESSAGE_MAP()


// обработчики сообщений CComPortDlg

BOOL CComPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	vector<string> speeds = {"110", "600", "1200", "2400", "4800", "9600", "14400", "38400", "56000"};

	for (int i = 0; i < speeds.size(); i++) {
		this->cnt_speed.InsertString(0, speeds[i].c_str());
	}

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CComPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CComPortDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CComPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CComPortDlg::OnBnClickedSend()
{
	UpdateData(TRUE);
	int writeBytes = com1->writePort((string)this->val_msg);
	this->cnt_chat_area.AddString(this->val_msg);
	this->val_msg = "";
	UpdateData(FALSE);

	if (firstClient) {
		StartSecondClient();
	}
	else {
		StartFirstClient();
	}
	
}

void CComPortDlg::OnBnClickedConnect()
{
	CWinThread *cwt;

	CreateEvent(0, TRUE, TRUE, "firstClient");
	if (GetLastError() != ERROR_ALREADY_EXISTS) {
		com1 = new ComPortActions("COM1");
		com2 = new ComPortActions("COM2");
		cwt = new CWinThread(ThreadFirstClient, NULL);
	}
	else {
		com1 = new ComPortActions("COM2");
		com2 = new ComPortActions("COM1");
		cwt = new CWinThread(ThreadSecondClient, NULL);
		firstClient = false;
	}
	cwt->CreateThread();

	cnt_chat_area_outer = &(this->cnt_chat_area);
	com2_outer = this->com2;	

	UpdateData(TRUE);
	this->val_speed = "14400";
	UpdateData(FALSE);
}

void CComPortDlg::OnCbnSelchangeSpeed()
{
	int speed = atoi(this->val_speed);
	com1->setSpeed(speed);
}