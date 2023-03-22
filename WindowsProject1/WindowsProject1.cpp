// WindowsProject1.cpp : Copyright(C) 2023 http://youtube.com/programmercpp
#include "resource.h"
#include <Windows.h>
#include <ShlObj.h>
#include <memory>
std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*> フォルダ選択(HWND hwndOwner)
{
	std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*> retval{ nullptr, CoTaskMemFree };
	IFileDialog* dlg;
	auto hr = CoCreateInstance(__uuidof(FileOpenDialog), nullptr, CLSCTX_INPROC_SERVER, __uuidof(dlg), (void**)&dlg);
	if (SUCCEEDED(hr)) {
		if (SUCCEEDED(hr = dlg->SetOptions(FOS_PICKFOLDERS))) {
			if ((hr = dlg->Show(hwndOwner)) == S_OK) {
				IShellItem* item;
				if (SUCCEEDED(hr = dlg->GetResult(&item))) {
					LPWSTR pszName;
					if (SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &pszName)))
						retval.reset(pszName);
				}
			}
		}
		dlg->Release();
	}
	return retval;
}
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_Folder:
			if (const auto フォルダのパス = フォルダ選択(hDlg))
				SetDlgItemTextW(hDlg, IDC_EDIT_SelectedFolder, フォルダのパス.get());
			return true;
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
			return true;
		default:
			return false;
		}
	default:
		return false;
	}
}
int APIENTRY wWinMain
( _In_     HINSTANCE hInstance
, _In_opt_ HINSTANCE //hPrevInstance
, _In_     LPWSTR    lpCmdLine
, _In_     int       nCmdShow
)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow );

	if (SUCCEEDED(CoInitialize(nullptr))) {
		DialogBoxParamW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), nullptr, DialogProc, 0);
		CoUninitialize();
	}
}
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
