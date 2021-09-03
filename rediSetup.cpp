#include "pch.h"
#include "rediSetup.h"

rediSetup::rediSetup()
{
}

rediSetup::~rediSetup()
{
}

//vc ����� ��Ű�� ��ġ
BOOL rediSetup::setupMicrosoftVC_redist()
{
	BOOL bVC_redistInstall = FALSE;
	CString strDisplayName64, strDisplayName86;

	if (CheckMicrosoftVC_redistx64(L"DisplayName", strDisplayName64))
	{
		bVC_redistInstall = TRUE;
	}

	if (CheckMicrosoftVC_redistx86(L"DisplayName", strDisplayName86))
	{
		bVC_redistInstall = TRUE;
	}

	//CString strResult;
	//strResult.Format(_T("%s / %s"), strDisplayName64, strDisplayName64);

	//���� ��Ÿ�� ���̺귯�� ��ġ ������ ������ ��ġ
	if (!bVC_redistInstall)
	{
		bVC_redistInstall = FALSE;
		InstallMicrosoftVC_redist();
	}

	return bVC_redistInstall;
}

//Microsoft Visual C++ 2019 ����� ��Ű�� ��ġ ���(x64)
BOOL rediSetup::CheckMicrosoftVC_redistx64(CString strValueName, CString& strValue)
{
	CString strKey = CString("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{4b2f3795-f407-415e-88d5-8c8ab322909d}");

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

//Microsoft Visual C++ 2019 ����� ��Ű�� ��ġ ���(x86)
BOOL rediSetup::CheckMicrosoftVC_redistx86(CString strValueName, CString& strValue)
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

//Microsoft Visual C++ 2019 ����� ��Ű�� silent mode ��ġ
void rediSetup::InstallMicrosoftVC_redist(BOOL bX86)
{
	CString strSetupFile;

	if (bX86)
		strSetupFile.Format(_T("%s\\VC_redist.x86.exe"), GetModulePath());
	else
		strSetupFile.Format(_T("%s\\VC_redist.x64.exe"), GetModulePath());

	SHELLEXECUTEINFO SHInfo = { 0 };
	SHInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	SHInfo.fMask = SEE_MASK_NOASYNC;
	SHInfo.lpVerb = L"runas";
	SHInfo.lpFile = strSetupFile;
	SHInfo.lpParameters = L" /install /quiet /norestart";
	SHInfo.hProcess = NULL;
	SHInfo.nShow = SW_HIDE;
	ShellExecuteEx(&SHInfo);
}



//���� ��Ÿ�� ��ġ 
BOOL rediSetup::setupEdgeWebViewRunTimelib()
{
	//���� ��Ÿ�� ���̺귯�� ��ġ ����
	BOOL bEdgeruntimeInstall = FALSE;
	CString strDisplayName, strDisplayVersion;

	if (CheckMicrosoftEdgeWebViewRunTimelib(L"DisplayName", strDisplayName))
	{
		bEdgeruntimeInstall = TRUE;
	}

	if (CheckMicrosoftEdgeWebViewRunTimelib(L"DisplayVersion", strDisplayVersion))
	{
		bEdgeruntimeInstall = TRUE;
	}

	//CString strResult;
	//strResult.Format(_T("%s - %s"), strDisplayName, strDisplayVersion);

	//���� ��Ÿ�� ���̺귯�� ��ġ ������ ������ ��ġ
	if (!bEdgeruntimeInstall)
	{
		bEdgeruntimeInstall = FALSE;
		InstallMicrosoftEdgeWebViewRunTimelib();
	}

	return bEdgeruntimeInstall;
}

//���� ��Ÿ�� ���̺귯�� ��ġ ���
BOOL rediSetup::CheckMicrosoftEdgeWebViewRunTimelib(CString strValueName, CString& strValue)
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

//Microsoft Edge ������ ��ġ ���
BOOL rediSetup::CheckMicrosoftEdge(CString strValueName, CString& strValue)
{
	CString strKey = CString("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Microsoft Edge");

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

//���� ��Ÿ�� ���̺귯�� silent mode ��ġ
void rediSetup::InstallMicrosoftEdgeWebViewRunTimelib(BOOL bX86)
{
	CString strSetupFile;

	if (bX86)
		strSetupFile.Format(_T("%s\\MicrosoftEdgeWebView2RuntimeInstallerX86.exe"), GetModulePath());
	else
		strSetupFile.Format(_T("%s\\MicrosoftEdgeWebView2RuntimeInstallerX64.exe"), GetModulePath());


	SHELLEXECUTEINFO SHInfo = { 0 };
	SHInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	SHInfo.fMask = SEE_MASK_NOASYNC;
	SHInfo.lpVerb = L"runas";
	SHInfo.lpFile = strSetupFile;
	SHInfo.lpParameters = L" /silent /install";
	SHInfo.hProcess = NULL;
	SHInfo.nShow = SW_HIDE;
	ShellExecuteEx(&SHInfo);
}

void rediSetup::infoEdgeUnInstall()
{
	//���� ������ ��ġ ���� Ȯ��
	CString strDisplayVersion, strInstallLocation;
	if (CheckMicrosoftEdge(L"DisplayVersion", strDisplayVersion))
	{
	}

	if (CheckMicrosoftEdge(L"InstallLocation", strInstallLocation))
	{
	}

	CString strResult;
	strResult.Format(_T("%s %s"), strDisplayVersion, strInstallLocation);
}



DWORD rediSetup::GetPID(LPCTSTR szFileName)
{
	CString szFile;
	PROCESSENTRY32 proc;
	DWORD pid = 0;

	proc.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hsnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		BOOL bRes = ::Process32First(hsnap, &proc);
		while (bRes)
		{
			if (_tcscmp(proc.szExeFile, szFileName) == 0)
			{
				pid = proc.th32ProcessID;
				break;
			}

			bRes = ::Process32Next(hsnap, &proc);
		}

		CloseHandle(hsnap);
	}

	return pid;
}

CString rediSetup::GetModulePath()
{
	TCHAR tPath[MAX_PATH];
	::GetModuleFileName(NULL, tPath, MAX_PATH);

	CString strPath = tPath;
	strPath = strPath.Left(strPath.ReverseFind('\\') + 1);
	return strPath;
}
