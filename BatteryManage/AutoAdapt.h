#pragma once  
class CAutoAdapt
{
public:
	CAutoAdapt(void);
	virtual ~CAutoAdapt(void);

public:
	void ReSize(HWND m_hWnd);
	void InitSize(HWND m_hWnd);
	POINT old;

private:

};

