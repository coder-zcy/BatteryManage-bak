
// TestDeviceDlg.h : ͷ�ļ�
//

#pragma once


// CTestDeviceDlg �Ի���
class CTestDeviceDlg : public CDialogEx
{
// ����
public:
	CTestDeviceDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTDEVICE_DIALOG };

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
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD_PTR dwData);
	DECLARE_MESSAGE_MAP()

public:

	afx_msg void EnumerateSerialPorts(CUIntArray& ports, CUIntArray& portse, CUIntArray& portsu);
	CUIntArray  ports;
	CUIntArray  portse;
	CUIntArray  portsu;
};
