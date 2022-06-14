#include "pch.h"
#include "framework.h"
#include "VC2019_Redist.h"
#include "VC2019_RedistDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CVC2019RedistDlg::CVC2019RedistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VC2019_REDIST_DIALOG, pParent)
{
	m_nCheckCount = 0;
}

void CVC2019RedistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVC2019RedistDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CVC2019RedistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW, 0);
	MoveWindow(-333, -333, 0, 0, TRUE);

	InitLib();

	return TRUE; 
}

void CVC2019RedistDlg::OnPaint()
{
	CPaintDC dc(this);
}

void CVC2019RedistDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nCheckCount > 5)
	{
		if (GetPID(L"MicrosoftEdgeWebView2RuntimeInstallerX86.exe") == 0 && GetPID(L"VC_redist.x86.exe") == 0)
		{
			KillTimer(1);
			CDialogEx::OnOK();
		}
	}

	m_nCheckCount++;

	CDialogEx::OnTimer(nIDEvent);
}

void CVC2019RedistDlg::InitLib()
{
	VCEdgePackage obj;

	//unzip resource
	UnZiPfile(obj.GetModulePath());


	//엣지 런타임/vc 재배포 패키지 설치여부 체크
	if (obj.setup_EdgeRunTimelib() && obj.setup_redist())
	{
		CDialog::OnOK();
		return;
	}

	//설치 프로세스 감시	
	SetTimer(1, 1000, NULL);
}

//설치 파일 압축 해제
void CVC2019RedistDlg::UnZiPfile(CString strCurrentPath)
{
	CString strEdgeFile, strVcFile;

	strEdgeFile.Format(L"%s\\MicrosoftEdgeWebView2RuntimeInstallerX86.zip", strCurrentPath);
	if (GetReourceFiles(strEdgeFile, _T("RC"), IDR_RC1) == TRUE)
	{
		if (SetUnZipFolder(strCurrentPath, strEdgeFile) == FALSE)
		{
			return;
		}
	}

	strVcFile.Format(L"%s\\VC_redist.x86.zip", strCurrentPath);
	if (GetReourceFiles(strVcFile, _T("RC"), IDR_RC2) == TRUE)
	{
		if (SetUnZipFolder(strCurrentPath, strVcFile) == FALSE)
		{
			return;
		}
	}
}

//리소스 파일 가져오기
BOOL CVC2019RedistDlg::GetReourceFiles(CString strFileName, CString strResourceID, UINT nID)
{
	HINSTANCE hInst = AfxGetInstanceHandle();

	HRSRC hExeFile;
	hExeFile = ::FindResource(hInst, MAKEINTRESOURCE(nID), strResourceID);
	if (hExeFile == NULL)
		return FALSE;

	HGLOBAL hRes = ::LoadResource(hInst, hExeFile);
	if (hRes != NULL)
	{
		DWORD dwSize = ::SizeofResource(hInst, hExeFile);

		UINT FAR* lpnRes = (UINT FAR*)::LockResource(hRes);

		TRY
		{
			CFile file(strFileName, CFile::modeCreate | CFile::modeWrite);
			file.Write(lpnRes, dwSize);
			file.Flush();
		}
			CATCH(CFileException, e)
		{
		}
		END_CATCH

			::FreeResource(hRes);

		return TRUE;
	}

	return FALSE;
}

//파일 압축 해제
BOOL CVC2019RedistDlg::SetUnZipFolder(CString strCurrentPath, CString strFilePath)
{
	HZIP hZip;
	ZIPENTRY zipEntry;
	ZIPENTRY zipItem;
	CString strOutputFile;

	hZip = OpenZip(strFilePath, "");
	if (!hZip) return FALSE;

	GetZipItem(hZip, -1, &zipEntry);
	for (int i = 0; i < zipEntry.index; i++)
	{
		GetZipItem(hZip, i, &zipItem);

		strOutputFile.Format(L"%s\\%s", strCurrentPath, CString(zipItem.name));

		UnzipItem(hZip, i, strOutputFile);
	}
	CloseZip(hZip);

	::DeleteFile(strFilePath);

	return TRUE;
}

DWORD CVC2019RedistDlg::GetPID(LPCTSTR szFileName)
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