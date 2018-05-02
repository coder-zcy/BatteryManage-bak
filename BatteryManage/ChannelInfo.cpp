#include "stdafx.h"
#include "ChannelInfo.h"


ChannelInfo::ChannelInfo()
{
	idFld = CDbColumn("ID", NUM_TYPE, 10, false);
	testItemFld = CDbColumn("TESTITEM", INT_TYPE, 10, true);
	channelPositionFld = CDbColumn("CHANNEL_POSITION", STR_TYPE, 10, true);
	channelFld = CDbColumn("CHANNEL", INT_TYPE, 10, true);
	batchFld = CDbColumn("BATCH", STR_TYPE, 10, true);
	batCodeFld = CDbColumn("BAT_CODE", STR_TYPE, 50, true);
	cellTagFld = CDbColumn("CELL_TAG", STR_TYPE, 50, true);

	channelInfoFlds.push_back(idFld);
	channelInfoFlds.push_back(testItemFld);
	channelInfoFlds.push_back(channelPositionFld);
	channelInfoFlds.push_back(channelFld);
	channelInfoFlds.push_back(batchFld);
	channelInfoFlds.push_back(batCodeFld);
	channelInfoFlds.push_back(cellTagFld);

}


ChannelInfo::~ChannelInfo()
{
}
