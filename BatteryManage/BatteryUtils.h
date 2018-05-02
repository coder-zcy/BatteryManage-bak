#define MAX_CAB_NUM 20
#define MIN_CAB_NUM 1

#define MIN_FRAME_WIDTH 720
#define MIN_FRAME_HEIGHT 480

#define STEP_COL_NUM 9

#define MAX_PATH_LENGTH 256
#define MAX_STR_LENGTH 4096

#define INT_LENGTH 10

#include "CabinetInfo.h"


class CBatteryUtils
{
public:
	static CString GetConfigPath(CString relativePath);
	//static CString GetDatabasePath(CString databasePath);
	static void GetSplitedStr(CString, CStringArray &, char);
};