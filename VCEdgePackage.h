#pragma once

class VCEdgePackage
{
public:
	VCEdgePackage();
	virtual ~VCEdgePackage();

public:
	BOOL setup_redist();
	BOOL setup_EdgeRunTimelib();
	CString GetModulePath();

public:
	BOOL Check_redist(CString strValueName, CString& strValue);
	BOOL Check_redistWOW(CString strValueName, CString& strValue);
	void Install_redist();

	BOOL Check_EdgeRunTimeLib(CString strValueName, CString& strValue);
	BOOL Check_EdgeRunTimeLibWOW(CString strValueName, CString& strValue);
	void Install_EdgeRunTimeLib();	
};
