// ConsoleApplication1.cpp : Copyright(C) 2023 http://youtube.com/programmercpp
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
void 結果表示(const std::unique_ptr<wchar_t, decltype(CoTaskMemFree)*>& フォルダのパス)
{
	if (フォルダのパス)
		MessageBoxW(nullptr, フォルダのパス.get(), L"結果", 0);
	else
		MessageBoxW(nullptr, L"フォルダは選択されませんでした。", L"結果", MB_ICONSTOP);
}
int main()
{
	if (SUCCEEDED(CoInitialize(nullptr))) {
		結果表示(フォルダ選択(nullptr));
		CoUninitialize();
	}
}
