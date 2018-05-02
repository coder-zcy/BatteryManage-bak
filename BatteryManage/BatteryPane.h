// 设定电池面板类，对电池面板的生成进行控制

#pragma once
#include "CabinetInfo.h"

class CBatteryPane
{
public:
	CBatteryPane(CabinetInfo cabinetInfo);
	~CBatteryPane();

private:
	int capId;			//	机柜编号
	int groupId;		//	组编号
	int subGroupId;		//	子组编号
	int tripGroupId;	//	最后一级编号

	int paneType;	    //  正面还是背面(0正面,1背面)
	int rowNum;			//  总共有多少行
	int colNum;			//	总共有多少列
	int subGroupBatNum;    //  每一组分组总共有多少块电池
	int subGroupNum;	//  每一行总共多少个分组

	int groupGapWidth;		//  小组之间间隔的百分比
	int batteryBodyWidth;	//  电池体的宽度
	int batteryCapWidth;		//	电池帽的宽度

	int rightBlankWidth;	//	电池右边的空白宽度
	int groupBlankWidth;	//	电池组之间的空白
	int groupWidth;			//	电池组的宽度

	double batHeightRowRatio;	//	电池高度占整行高度的比例
	double selHeightRowRatio;	//  电池被选中时矩形框占整行高度的比例
	//double openHeightRowRatio;	//	选中电池打开详细窗口时矩形框占整行高度的比例
	double bodyHeightRowRatio;	//	电池体占整行高度的比例
	double batteryRowHeight;	// 电池每一行的高度
	double batteryBodyHeight;	// 电池体的高度
	double batteryCapHeight;	// 电池帽的高度

public:	CRect paneRect;			//电池面板的空间

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

