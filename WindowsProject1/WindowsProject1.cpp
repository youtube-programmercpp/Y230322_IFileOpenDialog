// WindowsProject1.cpp : Copyright(C) 2023 http://youtube.com/programmercpp
#include "resource.h"
#include <Windows.h>
#include <ShlObj.h>
#include <memory>
#include <array>
std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*> フォルダ選択(HWND hDlg)
{
	std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*> retval{ nullptr, CoTaskMemFree };
	IFileDialog* dlg;
	auto hr = CoCreateInstance(__uuidof(FileOpenDialog), nullptr, CLSCTX_INPROC_SERVER, __uuidof(dlg), (void**)&dlg);
	if (SUCCEEDED(hr)) {
		if (SUCCEEDED(hr = dlg->SetOptions(FOS_PICKFOLDERS))) {
			if ((hr = dlg->Show(hDlg)) == S_OK) {
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

std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*> フォルダ選択2(HWND hDlg)
{
	UINT ulFlags = 0;
#define	Macro(name, value)  if (IsDlgButtonChecked(hDlg, IDC_CHECK_##name)) ulFlags |= name;
#include "BIF.h"
#undef	Macro
	std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*> retval{ nullptr, CoTaskMemFree };
	wchar_t szDisplayName[MAX_PATH];
	*szDisplayName = L'\0';
	if (const std::unique_ptr<std::remove_pointer_t<PIDLIST_ABSOLUTE>, decltype(CoTaskMemFree)*> pidl
		{ /*SHSTDAPI_(PIDLIST_ABSOLUTE)*/SHBrowseForFolderW(/*_In_ LPBROWSEINFOW lpbi*/std::array< BROWSEINFOW, 1>
			{ /*HWND              hwndOwner     ;*/hDlg
			, /*PCIDLIST_ABSOLUTE pidlRoot      ;*/nullptr 
			, /*LPWSTR            pszDisplayName;*/szDisplayName// Return display name of item selected.
			, /*LPCWSTR           lpszTitle     ;*/nullptr // text to go in the banner over the tree.
			, /*UINT              ulFlags       ;*/ulFlags       // Flags that control the return stuff
			, /*BFFCALLBACK       lpfn          ;*/nullptr 
			, /*LPARAM            lParam        ;*/0 // extra info that's passed back in callbacks
			, /*int               iImage        ;*/0 // output var: where to return the Image index.
			}.data())
		, CoTaskMemFree
		}) {
		wchar_t pszPath[MAX_PATH];
		if (/*_Success_(return != 0) SHSTDAPI_(BOOL)*/SHGetPathFromIDListW
		( /*_In_                   PCIDLIST_ABSOLUTE pidl   */pidl.get()
		, /*_Out_writes_(MAX_PATH) LPWSTR            pszPath*/pszPath
		)) {
			const auto cb = (lstrlenW(pszPath) + 1) * sizeof *pszPath;
			if (const auto pszRetVal = static_cast<LPWSTR>(CoTaskMemAlloc(cb))) {
				retval.reset(pszRetVal);
				CopyMemory(pszRetVal, pszPath, cb);
			}
		}
	}
	return retval;
}
void EnableWindow_IDC_CHECK_BIF_XXX(HWND hDlg)
{
	const auto bEnable = IsDlgButtonChecked(hDlg, IDC_RADIO_SHBrowseForFolder);
#define	Macro(name, value)  EnableWindow(GetDlgItem(hDlg, IDC_CHECK_##name), bEnable); 
#include "BIF.h"
#undef	Macro
	const auto bNewDialogStyle = IsDlgButtonChecked(hDlg, IDC_CHECK_BIF_NEWDIALOGSTYLE);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_BIF_STATUSTEXT), bEnable && !bNewDialogStyle);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_BIF_UAHINT    ), bEnable &&  bNewDialogStyle);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_BIF_SHAREABLE ), bEnable &&  bNewDialogStyle);
}
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_RADIO_FileOpenDialog, BST_CHECKED);
		EnableWindow_IDC_CHECK_BIF_XXX(hDlg);
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_BUTTON_Folder:
			if (const auto フォルダのパス = IsDlgButtonChecked(hDlg, IDC_RADIO_FileOpenDialog) ? フォルダ選択(hDlg) : フォルダ選択2(hDlg) )
				SetDlgItemTextW(hDlg, IDC_EDIT_SelectedFolder, フォルダのパス.get());
			return true;
		case IDCANCEL:
			EndDialog(hDlg, IDOK);
			return true;
		case IDC_RADIO_FileOpenDialog          :
		case IDC_RADIO_SHBrowseForFolder       :
		case IDC_CHECK_BIF_NEWDIALOGSTYLE      :
			EnableWindow_IDC_CHECK_BIF_XXX(hDlg);
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
