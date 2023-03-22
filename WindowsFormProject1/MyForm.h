#pragma once

namespace WindowsFormProject1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm の概要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_Folder;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox_SelectedFolder;


	protected:

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_Folder = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox_SelectedFolder = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button_Folder
			// 
			this->button_Folder->Location = System::Drawing::Point(126, 26);
			this->button_Folder->Name = L"button_Folder";
			this->button_Folder->Size = System::Drawing::Size(75, 23);
			this->button_Folder->TabIndex = 0;
			this->button_Folder->Text = L"フォルダー...";
			this->button_Folder->UseVisualStyleBackColor = true;
			this->button_Folder->Click += gcnew System::EventHandler(this, &MyForm::button_Folder_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 58);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(108, 12);
			this->label1->TabIndex = 1;
			this->label1->Text = L"選択されたフォルダー: ";
			// 
			// textBox_SelectedFolder
			// 
			this->textBox_SelectedFolder->Location = System::Drawing::Point(126, 55);
			this->textBox_SelectedFolder->Name = L"textBox_SelectedFolder";
			this->textBox_SelectedFolder->Size = System::Drawing::Size(355, 19);
			this->textBox_SelectedFolder->TabIndex = 2;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(493, 102);
			this->Controls->Add(this->textBox_SelectedFolder);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_Folder);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_Folder_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
