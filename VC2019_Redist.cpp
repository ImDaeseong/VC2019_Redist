#include "pch.h"
#include "framework.h"
#include "VC2019_Redist.h"
#include "VC2019_RedistDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CVC2019RedistApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CVC2019RedistApp::CVC2019RedistApp()
{
}

CVC2019RedistApp theApp;

BOOL CVC2019RedistApp::InitInstance()
{
	HANDLE hMutex = ::CreateMutex(NULL, FALSE, L"RedistributableEdgeVCInstall_");
#ifndef _DEBUG
	if (ERROR_ALREADY_EXISTS == ::GetLastError())
		return FALSE;
#endif

	CWinApp::InitInstance();


	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));


	CVC2019RedistDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Delete the shell manager created above.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	return FALSE;
}

