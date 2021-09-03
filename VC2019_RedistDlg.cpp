#include "pch.h"
#include "framework.h"
#include "VC2019_Redist.h"
#include "VC2019_RedistDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "zip.h"
#include "unzip.h"

CVC2019RedistDlg::CVC2019RedistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VC2019_REDIST_DIALOG, pParent)
{
	bTimer = FALSE;
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
	int nKillCount = 0;

	if (nIDEvent == TIMER_SETUP_CHECK)
	{
		if (Setupobj.GetPID(L"MicrosoftEdgeWebView2RuntimeInstallerX86.exe") == 0)
		{
			nKillCount++;
		}

		if (Setupobj.GetPID(L"VC_redist.x86.exe") == 0)
		{
			nKillCount++;
		}

		if (nKillCount == 2)
		{
			KillTimer(nIDEvent);
			CDialogEx::OnOK();
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CVC2019RedistDlg::InitLib()
{
	CString strCurrentPath = Setupobj.GetModulePath();

	//설치파일 리소스에서 가져오기
	UnZiPfile(strCurrentPath);


	//엣지 브라우저 설치 정보 확인
	Setupobj.infoEdgeUnInstall();


	//엣지 런타임 설치
	BOOL bedge = Setupobj.setupEdgeWebViewRunTimelib();
	if (!bedge)
	{
		bTimer = TRUE;
	}

	//vc 재배포 패키지 설치
	BOOL bredist = Setupobj.setupMicrosoftVC_redist();
	if (!bredist)
	{
		bTimer = TRUE;
	}

	bTimer = TRUE;
	if (bTimer)
	{
		SetTimer(TIMER_SETUP_CHECK, 1000, NULL);
	}
	else
	{
		CDialogEx::OnOK();
	}
}

//설치 파일 압축 해제
void CVC2019RedistDlg::UnZiPfile(CString strCurrentPath)
{
	CString strEdge64ZipFile, strEdge86ZipFile, strVC64ZipFile, strVC86ZipFile;

	strEdge64ZipFile.Format(_T("%sMicrosoftEdgeWebView2RuntimeInstallerX64.zip"), strCurrentPath);
	if (GetReourceFiles(strEdge64ZipFile, _T("RC"), IDR_RC1) == TRUE)
	{
		if (SetUnZipFolder(strCurrentPath, strEdge64ZipFile) == FALSE)
		{
			return;
		}
	}

	strEdge86ZipFile.Format(_T("%sMicrosoftEdgeWebView2RuntimeInstallerX86.zip"), strCurrentPath);
	if (GetReourceFiles(strEdge86ZipFile, _T("RC"), IDR_RC2) == TRUE)
	{
		if (SetUnZipFolder(strCurrentPath, strEdge86ZipFile) == FALSE)
		{
			return;
		}
	}


	strVC64ZipFile.Format(_T("%sVC_redist.x64.zip"), strCurrentPath);
	if (GetReourceFiles(strVC64ZipFile, _T("RC"), IDR_RC3) == TRUE)
	{
		if (SetUnZipFolder(strCurrentPath, strVC64ZipFile) == FALSE)
		{
			return;
		}
	}


	strVC86ZipFile.Format(_T("%sVC_redist.x86.zip"), strCurrentPath);
	if (GetReourceFiles(strVC86ZipFile, _T("RC"), IDR_RC4) == TRUE)
	{
		if (SetUnZipFolder(strCurrentPath, strVC86ZipFile) == FALSE)
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

		strOutputFile.Format(_T("%s\\%s"), strCurrentPath, CString(zipItem.name));

		UnzipItem(hZip, i, strOutputFile);
	}
	CloseZip(hZip);

	::DeleteFile(strFilePath);

	return TRUE;
}

