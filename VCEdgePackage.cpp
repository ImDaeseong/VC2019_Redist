#include "pch.h"
#include "VCEdgePackage.h"

VCEdgePackage::VCEdgePackage()
{
}

VCEdgePackage::~VCEdgePackage()
{
}

//vc 재배포 패키지 설치
BOOL VCEdgePackage::setup_redist()
{
	CString strDisplay;

	if (Check_redist(L"DisplayName", strDisplay))
	{
		return TRUE;
	}

	if (Check_redistWOW(L"DisplayName", strDisplay))
	{
		return TRUE;
	}

	//설치 
	Install_redist();

	return FALSE;
}

//엣지 런타임 설치 
BOOL VCEdgePackage::setup_EdgeRunTimelib()
{
	CString strDisplayName;

	if (Check_EdgeRunTimeLib(L"DisplayName", strDisplayName))
	{
		return TRUE;
	}

	if (Check_EdgeRunTimeLibWOW(L"DisplayName", strDisplayName))
	{
		return TRUE;
	}

	//설치
	Install_EdgeRunTimeLib();

	return FALSE;
}

//Microsoft Visual C++ 2019 재배포 패키지 설치 경로(x86)
BOOL VCEdgePackage::Check_redist(CString strValueName, CString& strValue)
{
	CString strKey = CString("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{dfea0fad-88b2-4a1f-8536-3f8f9391f4ef}");

	HKEY hRegKey = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0, KEY_ALL_ACCESS, &hRegKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		TCHAR tszValue[1024];
		memset(tszValue, 0, sizeof(tszValue));
		DWORD dwByte = sizeof(tszValue);

		if (RegQueryValueEx(hRegKey, strValueName, 0, &dwType, (LPBYTE)tszValue, (LPDWORD)&dwByte) == ERROR_SUCCESS)
		{
			strValue.Format(_T("%s"), tszValue);
			::RegCloseKey(hRegKey);
			return TRUE;
		}
	}
	::RegCloseKey(hRegKey);
	return FALSE;
}

BOOL VCEdgePackage::Check_redistWOW(CString strValueName, CString& strValue)
{
	CString strKey = CString("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{dfea0fad-88b2-4a1f-8536-3f8f9391f4ef}");

	HKEY hRegKey = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0, KEY_ALL_ACCESS, &hRegKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		TCHAR tszValue[1024];
		memset(tszValue, 0, sizeof(tszValue));
		DWORD dwByte = sizeof(tszValue);

		if (RegQueryValueEx(hRegKey, strValueName, 0, &dwType, (LPBYTE)tszValue, (LPDWORD)&dwByte) == ERROR_SUCCESS)
		{
			strValue.Format(_T("%s"), tszValue);
			::RegCloseKey(hRegKey);
			return TRUE;
		}
	}
	::RegCloseKey(hRegKey);
	return FALSE;
}

//Microsoft Visual C++ 2019 재배포 패키지 silent mode 설치
void VCEdgePackage::Install_redist()
{
	CString strSetupFile;
	strSetupFile.Format(L"%sVC_redist.x86.exe", GetModulePath());

	/*
	SHELLEXECUTEINFO SHInfo = { 0 };
	SHInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	SHInfo.fMask = SEE_MASK_NOASYNC;
	SHInfo.lpVerb = L"runas";
	SHInfo.lpFile = strSetupFile;
	SHInfo.lpParameters = L" /install /quiet /norestart";
	SHInfo.hProcess = NULL;
	SHInfo.nShow = SW_HIDE;
	ShellExecuteEx(&SHInfo);
    */

	CString strParams;
	strParams.Format(L"/install /quiet /norestart");

	HINSTANCE hInstance = ::ShellExecute(NULL, L"open", strSetupFile, strParams, NULL, SW_SHOW);
}

//엣지 런타임 라이브러리 설치 경로
BOOL VCEdgePackage::Check_EdgeRunTimeLib(CString strValueName, CString& strValue)
{
	CString strKey = CString("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft EdgeWebView");

	HKEY hRegKey = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0, KEY_ALL_ACCESS, &hRegKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		TCHAR tszValue[1024];
		memset(tszValue, 0, sizeof(tszValue));
		DWORD dwByte = sizeof(tszValue);

		if (RegQueryValueEx(hRegKey, strValueName, 0, &dwType, (LPBYTE)tszValue, (LPDWORD)&dwByte) == ERROR_SUCCESS)
		{
			strValue.Format(_T("%s"), tszValue);
			::RegCloseKey(hRegKey);
			return TRUE;
		}
	}
	::RegCloseKey(hRegKey);
	return FALSE;
}

BOOL VCEdgePackage::Check_EdgeRunTimeLibWOW(CString strValueName, CString& strValue)
{
	CString strKey = CString("SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft EdgeWebView");

	HKEY hRegKey = NULL;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, strKey, 0, KEY_ALL_ACCESS, &hRegKey) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_SZ;
		TCHAR tszValue[1024];
		memset(tszValue, 0, sizeof(tszValue));
		DWORD dwByte = sizeof(tszValue);

		if (RegQueryValueEx(hRegKey, strValueName, 0, &dwType, (LPBYTE)tszValue, (LPDWORD)&dwByte) == ERROR_SUCCESS)
		{
			strValue.Format(_T("%s"), tszValue);
			::RegCloseKey(hRegKey);
			return TRUE;
		}
	}
	::RegCloseKey(hRegKey);
	return FALSE;
}

//엣지 런타임 라이브러리 silent mode 설치
void VCEdgePackage::Install_EdgeRunTimeLib()
{
	CString strSetupFile;
	strSetupFile.Format(L"%sMicrosoftEdgeWebView2RuntimeInstallerX86.exe", GetModulePath());

	CString strParams;
	strParams.Format(L"/silent /install");

	HINSTANCE hInstance = ::ShellExecute(NULL, L"open", strSetupFile, strParams, NULL, SW_SHOW);
}

CString VCEdgePackage::GetModulePath()
{
	TCHAR tPath[MAX_PATH];
	::GetModuleFileName(NULL, tPath, MAX_PATH);

	CString strPath = tPath;
	strPath = strPath.Left(strPath.ReverseFind('\\') + 1);
	return strPath;
}