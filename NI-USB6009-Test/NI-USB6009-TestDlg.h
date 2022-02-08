
// NI-USB6009-TestDlg.h : 头文件
//

#pragma once
#include <CTime>


// CNIUSB6009TestDlg 对话框
class CNIUSB6009TestDlg : public CDialogEx
{
// 构造
public:
	CNIUSB6009TestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NIUSB6009TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnAuto();

private:
	void openOperate();

	void closeOperate();

	void LoadDataFromFile();

	void saveDataToFile();

	CString getExtPath();

	void SplitString(CString sSrc, CStringArray &arrDst, char cDelimiter);

private:
	int m_nDoIndex;
	int m_nFinishedCount;
	int m_nProcessesCount;
	bool m_bClosed;
	int m_nFinishedTime;
	int m_nProcessesTime;
	CTime m_PreTime;			// 已开机的时间
};
