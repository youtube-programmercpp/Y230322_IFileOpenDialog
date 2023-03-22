// WindowsFormProject1.cpp : Copyright(C) 2023 http://youtube.com/programmercpp
#include "pch.h"
#include "MyForm.h"

using namespace System;

int main(array<System::String^>^ args)
{
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	System::Windows::Forms::Application::Run(gcnew WindowsFormProject1::MyForm);
	return 0;
}
