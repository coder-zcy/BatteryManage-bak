#pragma once

#include "InitCopyDlg.h"
#include "afxwin.h"
#include "CabinetInfo.h"

#include <iostream>
#include <vector>


using namespace std;

#define SCREEN_MAX_NUM 20

// CScreenDlg �Ի���

class CScreenDlg : public CDialog
{
	DECLARE_DYNAMIC(CScreenDlg)

public:
	CScreenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScreenDlg();

	// �Ի�������
	enum { IDD = IDD_SCREEN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CInitCopyDlg *copyDlg;
	CComboBox screenNumCom;

	virtual BOOL OnInitDialog();
	//  ��ʼ������ѡ��
	void InitScreenSet();
	void ConnectToDatabase();
	CabinetInfo GetResultSetCabInfo();
	void InitCabinetInfo(CabinetInfo cabinetInfo);
	//void InitCabinetInfoByCabId(int cabId);
	void CScreenDlg::SaveGlbCabInfos(int cabId, CabinetInfo cabinetInfo);
	BOOL SaveCabInfoToDb(int cabId, CabinetInfo cabinetInfo);

	//	�ӶԻ�����CabinetInfo
	CabinetInfo GetDlgCabInfo();

	//	��ʼ��Ĭ�ϻ������
	void InitDefCabinet();
	void InitCabinetInfoById(int cabId);
	afx_msg void OnBnClickedScrnump();
	afx_msg void OnBnClickedScrnumm();
	afx_msg void OnBnClickedParacopy();


	CEdit deviceIdEdit;
	CEdit groupNumPerColEdit;
	CEdit colShowNumEdit;
	CEdit numPerGroupEdit;
	CEdit constVmaxEdit;
	CEdit constVminEdit;
	CEdit constAmaxEdit;
	CEdit constAminEdit;
	CButton constVchargeChk;
	CButton omTestChk;
	CButton saveToFileChk;
	CButton vdisChk;
	CEdit vdisValEdit;
	CButton adisChk;
	CEdit adisValEdit;
	CButton timeDisChk;
	CEdit timeDisValEdit;
	CEdit vshowMaxEdit;
	CEdit vshowMinEdit;
	CEdit svshowMaxEdit;
	CEdit svshowMinEdit;
	CEdit sashowMaxEdit;
	CEdit sashowMinEdit;
	CEdit srshowMaxEdit;
	CEdit srshowMinEdit;
	CComboBox deviceNameCom;

	CButton screenChk1;
	CButton screenChk2;
	CButton screenChk3;
	CButton screenChk4;
	CButton screenChk5;
	CButton screenChk6;
	CButton screenChk7;
	CButton screenChk8;
	CButton screenChk9;
	CButton screenChk10;
	CButton screenChk11;
	CButton screenChk12;
	CButton screenChk13;
	CButton screenChk14;
	CButton screenChk15;
	CButton screenChk16;
	CButton screenChk17;
	CButton screenChk18;
	CButton screenChk19;
	CButton screenChk20;
	
	vector<CButton *> screenChks;
	void SaveScreenSet();

	// ����Access���ݿ�Ķ���
	_ConnectionPtr pConnection;
	_CommandPtr pCommand;
	_RecordsetPtr pRecordset;

	HRESULT hr;
	CString dbConfigPath;
	afx_msg void OnClose();

	afx_msg void OnCbnSelchangeComboScrnum();
};
