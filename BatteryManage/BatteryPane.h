// �趨�������࣬�Ե���������ɽ��п���

#pragma once
#include "CabinetInfo.h"

class CBatteryPane
{
public:
	CBatteryPane(CabinetInfo cabinetInfo);
	~CBatteryPane();

private:
	int capId;			//	������
	int groupId;		//	����
	int subGroupId;		//	������
	int tripGroupId;	//	���һ�����

	int paneType;	    //  ���滹�Ǳ���(0����,1����)
	int rowNum;			//  �ܹ��ж�����
	int colNum;			//	�ܹ��ж�����
	int subGroupBatNum;    //  ÿһ������ܹ��ж��ٿ���
	int subGroupNum;	//  ÿһ���ܹ����ٸ�����

	int groupGapWidth;		//  С��֮�����İٷֱ�
	int batteryBodyWidth;	//  �����Ŀ��
	int batteryCapWidth;		//	���ñ�Ŀ��

	int rightBlankWidth;	//	����ұߵĿհ׿��
	int groupBlankWidth;	//	�����֮��Ŀհ�
	int groupWidth;			//	�����Ŀ��

	double batHeightRowRatio;	//	��ظ߶�ռ���и߶ȵı���
	double selHeightRowRatio;	//  ��ر�ѡ��ʱ���ο�ռ���и߶ȵı���
	//double openHeightRowRatio;	//	ѡ�е�ش���ϸ����ʱ���ο�ռ���и߶ȵı���
	double bodyHeightRowRatio;	//	�����ռ���и߶ȵı���
	double batteryRowHeight;	// ���ÿһ�еĸ߶�
	double batteryBodyHeight;	// �����ĸ߶�
	double batteryCapHeight;	// ���ñ�ĸ߶�

public:	CRect paneRect;			//������Ŀռ�

public:

	int GetCapId() const { return capId; }
	void SetCapId(int val) { capId = val; }

	int GetGroupId() const { return groupId; }
	void SetGroupId(int val) { groupId = val; }

	int GetSubGroupId() const { return subGroupId; }
	void SetSubGroupId(int val) { subGroupId = val; }

	int GetTripGroupId() const { return tripGroupId; }
	void SetTripGroupId(int val) { tripGroupId = val; }

	int GetPaneType() const { return paneType; }
	void SetPaneType(int val) { paneType = val; }

	int GetRowNum() const { return rowNum; }
	void SetRowNum(int val) { rowNum = val; }

	int GetColNum() const { return colNum; }
	void SetColNum(int val) { colNum = val; }

	int GetSubGroupBatNum() const { return subGroupBatNum; }
	void SetSubGroupBatNum(int val) { subGroupBatNum = val; }

	double GetGroupGapWidth() const { return groupGapWidth; }
	void SetGroupGapWidth(double val) { groupGapWidth = val; }

	double GetBatHeightRowRatio() const { return batHeightRowRatio; }
	void SetBatHeightRowRatio(double val) { batHeightRowRatio = val; }

	double GetSelHeightRowRatio() const { return selHeightRowRatio; }
	void SetSelHeightRowRatio(double val) { selHeightRowRatio = val; }

	//double GetOpenHeightRowRatio() const { return openHeightRowRatio; }
	//void SetOpenHeightRowRatio(double val) { openHeightRowRatio = val; }

	double GetBodyHeightRowRatio() const { return bodyHeightRowRatio; }
	void SetBodyHeightRowRatio(double val) { bodyHeightRowRatio = val; }

	//CRect& GetPaneRect()  { return paneRect; }
	//void SetPaneRect(CRect val) { paneRect = val; }

	double GetBatteryRowHeight() const { return batteryRowHeight; }
	void SetBatteryRowHeight(double val) { batteryRowHeight = val; }

	double GetBatteryWidth() const { return batteryBodyWidth; }
	void SetBatteryWidth(double val) { batteryBodyWidth = val; }

	int GetSubGroupNum() const { return subGroupNum; }
	void SetSubGroupNum(int val) { subGroupNum = val; }

	double GetBatteryBodyHeight() const { return batteryBodyHeight; }
	void SetBatteryBodyHeight(double val) { batteryBodyHeight = val; }

	double GetBatteryCapHeight() const { return batteryCapHeight; }
	void SetBatteryCapHeight(double val) { batteryCapHeight = val; }

	double GetBatteryCapWidth() const { return batteryCapWidth; }
	void SetBatteryCapWidth(double val) { batteryCapWidth = val; }

	int GetRightBlankWidth() { return this->rightBlankWidth; }
	void SetRightBlankWidth(int val) { this->rightBlankWidth = val; }

	int GetGroupBlankWidth() { return this->groupBlankWidth; }
	void SetGroupBlankWidth(int val) { this->groupBlankWidth = val; }

	int GetGroupWidth() { return this->groupWidth; }
	void SetGroupWidth(int val) { this->groupWidth = val; }

	void CalParamter(CRect batPicRect);
};

