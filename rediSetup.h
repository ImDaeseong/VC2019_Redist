#pragma once
class rediSetup
{
public:
	rediSetup();
	~rediSetup();

public:
	BOOL setupMicrosoftVC_redist();

	BOOL setupEdgeWebViewRunTimelib();	
	void infoEdgeUnInstall();

	DWORD GetPID(LPCTSTR szFileName);
	CString GetModulePath();

private:
	BOOL CheckMicrosoftVC_redistx64(CString strValueName, CString& strValue);
	BOOL CheckMicrosoftVC_redistx86(CString strValueName, CString& strValue);
	void InstallMicrosoftVC_redist(BOOL bX86 = TRUE);

	BOOL CheckMicrosoftEdgeWebViewRunTimelib(CString strValueName, CString& strValue);	
	BOOL CheckMicrosoftEdge(CString strValueName, CString& strValue);
	void InstallMicrosoftEdgeWebViewRunTimelib(BOOL bX86 = TRUE);
};

