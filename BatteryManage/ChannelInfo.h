#pragma once
#include "DbColumn.h"

class ChannelInfo
{
public:
	ChannelInfo();
	~ChannelInfo();
public:

	CDbColumn idFld;
	CDbColumn testItemFld;
	CDbColumn channelPositionFld;
	CDbColumn channelFld;
	CDbColumn batchFld;
	CDbColumn batCodeFld;
	CDbColumn cellTagFld;

	vector<CDbColumn> channelInfoFlds;

};

