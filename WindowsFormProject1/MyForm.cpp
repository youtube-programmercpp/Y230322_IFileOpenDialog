// WindowsFormProject1.cpp : Copyright(C) 2023 http://youtube.com/programmercpp
#include "pch.h"
#include "MyForm.h"
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
System::Void WindowsFormProject1::MyForm::button_Folder_Click(System::Object^ sender, System::EventArgs^ e)
{
	textBox_SelectedFolder->Text = gcnew String(フォルダ選択(nullptr).get());
}
#pragma comment(lib, "Ole32")
#pragma comment(lib, "user32")
