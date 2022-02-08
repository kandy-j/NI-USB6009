
// NI-USB6009-TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NI-USB6009-Test.h"
#include "NI-USB6009-TestDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <NIDAQmx.h>
#include <math.h>

#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CNIUSB6009TestDlg 对话框



CNIUSB6009TestDlg::CNIUSB6009TestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NIUSB6009TEST_DIALOG, pParent)
	, m_nDoIndex(3)
	, m_nFinishedCount(0)
	, m_nProcessesCount(0)
	, m_bClosed(true)
	, m_nFinishedTime(60)
	, m_nProcessesTime(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNIUSB6009TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DO_INDEX, m_nDoIndex);
	DDV_MinMaxInt(pDX, m_nDoIndex, 0, 3);
	DDX_Text(pDX, IDC_FINISHED_COUNT, m_nFinishedCount);
	DDV_MinMaxInt(pDX, m_nFinishedCount, 0, 65535);
	DDX_Text(pDX, IDC_PROCESSES_COUNT, m_nProcessesCount);
	DDV_MinMaxInt(pDX, m_nProcessesCount, 0, 65535);
	DDX_Text(pDX, IDC_FINISHED_TIME, m_nFinishedTime);
	DDV_MinMaxInt(pDX, m_nFinishedTime, 0, 600);
	DDX_Text(pDX, IDC_PROCESSES_TIME, m_nProcessesTime);
	DDV_MinMaxInt(pDX, m_nProcessesTime, 0, 30);
}

BEGIN_MESSAGE_MAP(CNIUSB6009TestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CNIUSB6009TestDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CNIUSB6009TestDlg::OnBnClickedBtnClose)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_AUTO, &CNIUSB6009TestDlg::OnBnClickedBtnAuto)
END_MESSAGE_MAP()


// CNIUSB6009TestDlg 消息处理程序

BOOL CNIUSB6009TestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	LoadDataFromFile();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNIUSB6009TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNIUSB6009TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNIUSB6009TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNIUSB6009TestDlg::OnBnClickedBtnOpen()
{
	openOperate();
}


void CNIUSB6009TestDlg::OnBnClickedBtnClose()
{
	closeOperate();
}


void CNIUSB6009TestDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int iCount = 0;
	switch (nIDEvent)
	{
	case 1:
	{
		if (m_bClosed) {
			openOperate();			// 接通电路
			m_PreTime = CTime::GetCurrentTime();
			m_bClosed = false;
		}
		else {
			if (iCount == 0) {			// 启动过程中
				if (CTime::GetCurrentTime().GetTime() - m_PreTime.GetTime() > m_nProcessesTime) {		// 保证启动未完成
					iCount = (++iCount) % 2;
					closeOperate();	// 断开电路
					m_bClosed = true;
					m_nProcessesCount++;
					UpdateData(FALSE);
					saveDataToFile();
				}
			}
			else {								// 启动完成
				if (CTime::GetCurrentTime().GetTime() - m_PreTime.GetTime() > m_nFinishedTime) {		// 保证启动完成
					iCount = (++iCount) % 2;
					closeOperate();	// 断开电路
					m_bClosed = true;
					m_nFinishedCount++;
					UpdateData(FALSE);
					saveDataToFile();
				}
			}
		}
	}
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CNIUSB6009TestDlg::openOperate()
{
	UpdateData();
	int         error = 0;
	TaskHandle	taskHandle = 0;
	uInt32		data = 0x00;
	char        errBuff[2048] = { '\0' };
	int32		written;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
	DAQmxErrChk(DAQmxCreateDOChan(taskHandle, "Dev1/port1", "", DAQmx_Val_ChanForAllLines));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk(DAQmxStartTask(taskHandle));

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxErrChk(DAQmxWriteDigitalU32(taskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL));

Error:
	if (DAQmxFailed(error))
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
	if (taskHandle != 0) {
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle);
		DAQmxClearTask(taskHandle);
	}
	if (DAQmxFailed(error))
		printf("DAQmx Error: %s\n", errBuff);
	printf("End of program, press Enter key to quit\n");
}

void CNIUSB6009TestDlg::closeOperate()
{
	UpdateData();
	int         error = 0;
	TaskHandle	taskHandle = 0;
	uInt32		data = data = pow(2, m_nDoIndex);
	char        errBuff[2048] = { '\0' };
	int32		written;

	/*********************************************/
	// DAQmx Configure Code
	/*********************************************/
	DAQmxErrChk(DAQmxCreateTask("", &taskHandle));
	DAQmxErrChk(DAQmxCreateDOChan(taskHandle, "Dev1/port1", "", DAQmx_Val_ChanForAllLines));

	/*********************************************/
	// DAQmx Start Code
	/*********************************************/
	DAQmxErrChk(DAQmxStartTask(taskHandle));

	/*********************************************/
	// DAQmx Write Code
	/*********************************************/
	DAQmxErrChk(DAQmxWriteDigitalU32(taskHandle, 1, 1, 10.0, DAQmx_Val_GroupByChannel, &data, &written, NULL));

Error:
	if (DAQmxFailed(error))
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
	if (taskHandle != 0) {
		/*********************************************/
		// DAQmx Stop Code
		/*********************************************/
		DAQmxStopTask(taskHandle);
		DAQmxClearTask(taskHandle);
	}
	if (DAQmxFailed(error))
		printf("DAQmx Error: %s\n", errBuff);
	printf("End of program, press Enter key to quit\n");
}


void CNIUSB6009TestDlg::LoadDataFromFile()
{
	CString sFilePath = getExtPath() + "ParamData.ini";
	CFileException fileException;
	CStdioFile file;
	if (!file.Open(sFilePath, CFile::typeText | CFile::modeReadWrite, &fileException)) {
		return;
	}

	file.SeekToBegin();
	CString sTmp = "";
	CStringArray sTmpArr;
	int nIndex = 0;
	while (file.ReadString(sTmp))
	{
		switch (nIndex)
		{
		case 0:				// DO Index
		{
			sTmpArr.RemoveAll();
			SplitString(sTmp, sTmpArr, ':');
			if (sTmpArr.GetCount() == 2) {
				m_nDoIndex = atoi(sTmpArr.GetAt(1));
			}
		}
		break;
		case 1:				// Finished time
		{
			sTmpArr.RemoveAll();
			SplitString(sTmp, sTmpArr, ':');
			if (sTmpArr.GetCount() == 2) {
				m_nFinishedTime = atoi(sTmpArr.GetAt(1));
			}
		}
		break;
		case 2:				// Processes time
		{
			sTmpArr.RemoveAll();
			SplitString(sTmp, sTmpArr, ':');
			if (sTmpArr.GetCount() == 2) {
				m_nProcessesTime = atoi(sTmpArr.GetAt(1));
			}
		}
		break;
		case 3:				// Finished count
		{
			sTmpArr.RemoveAll();
			SplitString(sTmp, sTmpArr, ':');
			if (sTmpArr.GetCount() == 2) {
				m_nFinishedCount = atoi(sTmpArr.GetAt(1));
			}
		}
		break;
		case 4:				// Processes count
		{
			sTmpArr.RemoveAll();
			SplitString(sTmp, sTmpArr, ':');
			if (sTmpArr.GetCount() == 2) {
				m_nProcessesCount = atoi(sTmpArr.GetAt(1));
			}
		}
		break;
		default:
			break;
		}
		nIndex++;
	}
	file.Close();

	UpdateData(FALSE);
}

void CNIUSB6009TestDlg::saveDataToFile()
{
	UpdateData();
	CString sFilePath = getExtPath() + "ParamData.ini";
	CFileException fileException;
	CStdioFile file;
	if (!file.Open(sFilePath, CFile::typeText | CFile::modeCreate | CFile::modeReadWrite, &fileException)) {
		return;
	}
	// Do Index
	CString sTmp = "";
	sTmp.Format(_T("DoIndex:%d\n"), m_nDoIndex);
	file.WriteString(sTmp);

	// Finished time
	sTmp = "";
	sTmp.Format(_T("FinishedTime:%d\n"), m_nFinishedTime);
	file.WriteString(sTmp);

	// Processes time
	sTmp = "";
	sTmp.Format(_T("ProcessesTime:%d\n"), m_nProcessesTime);
	file.WriteString(sTmp);

	// Finished count
	sTmp = "";
	sTmp.Format(_T("FinishedCount:%d\n"), m_nFinishedCount);
	file.WriteString(sTmp);

	// Processes count
	sTmp = "";
	sTmp.Format(_T("ProcessesCount:%d\n"), m_nProcessesCount);
	file.WriteString(sTmp);
	file.Flush();
	file.Close();
}

CString CNIUSB6009TestDlg::getExtPath()
{
	char exePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, exePath, MAX_PATH);
	int nExePathLen = strlen(exePath);
	int i = 0;
	for (i = nExePathLen - 1; i >= 0; i--) {
		if (exePath[i] == '\\') {
			break;
		}
	}
	exePath[i + 1] = '\0';		// 保留最后的‘\’
	return exePath;
}

void CNIUSB6009TestDlg::SplitString(CString sSrc, CStringArray &arrDst, char cDelimiter)
{
	arrDst.RemoveAll();
	CString sTmpSrc = sSrc;
	int nPos = sSrc.Find(cDelimiter);
	while (-1 != nPos) {
		CString sTmp = sTmpSrc.Left(nPos);
		sTmpSrc = sTmpSrc.Mid(nPos + 1);
		arrDst.Add(sTmp);
		nPos = sTmpSrc.Find(cDelimiter);
	}

	if (!sTmpSrc.IsEmpty()) {
		arrDst.Add(sTmpSrc);
	}
}

void CNIUSB6009TestDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}


void CNIUSB6009TestDlg::OnBnClickedBtnAuto()
{
	UpdateData();
	CString sCaption = "";
	GetDlgItem(IDC_BTN_AUTO)->GetWindowText(sCaption);
	if (sCaption == _T("自动执行")) {
		SetTimer(1, 1000, NULL);
		GetDlgItem(IDC_BTN_AUTO)->SetWindowText(_T("停止"));
	}
	else {
		KillTimer(1);
		GetDlgItem(IDC_BTN_AUTO)->SetWindowText(_T("自动执行"));
	}
}
