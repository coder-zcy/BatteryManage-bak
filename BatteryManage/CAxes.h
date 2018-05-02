// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

#import "C:\\Program Files (x86)\\TeeChart Pro v5 ActiveX Control\\TeeChart5.ocx" no_namespace
// CAxes ��װ����

class CAxes : public COleDispatchDriver
{
public:
	CAxes(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CAxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CAxes(const CAxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// IAxes ����
public:
	LPDISPATCH get_Left()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Right()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Top()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Bottom()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Depth()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_DrawAxesBeforeSeries()
	{
		BOOL result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DrawAxesBeforeSeries(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long AddCustom(BOOL IsHorizontal)
	{
		long result;
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_I4, (void*)&result, parms, IsHorizontal);
		return result;
	}
	LPDISPATCH get_Custom(long CustomAxisIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, CustomAxisIndex);
		return result;
	}
	long get_CustomCount()
	{
		long result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void RemoveCustom(long CustomAxisIndex)
	{
		static BYTE parms[] = VTS_I4;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomAxisIndex);
	}
	void RemoveAllCustom()
	{
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// IAxes ����
public:

};
