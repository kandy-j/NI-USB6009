
// NI-USB6009-TestDlg.h : ͷ�ļ�
//

#pragma once
#include <CTime>


// CNIUSB6009TestDlg �Ի���
class CNIUSB6009TestDlg : public CDialogEx
{
// ����
public:
	CNIUSB6009TestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NIUSB6009TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	CTime m_PreTime;			// �ѿ�����ʱ��
};
