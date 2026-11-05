#pragma once
#include <Windows.h>

/// \addtogroup OPERMODEDOC
/// <div style="page-break-after: always;"></div>
/// 
/// # Idle Panel
/// 





using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


/// <summary>
/// \ingroup IDLEIMPL
/// 
/// This is the Idle Panel mode implementing module
/// 
/// </summary>
public ref class IdleForm :  public System::Windows::Forms::Form
{

#define WINMSG_TIMER WM_USER + 1 //!< This is the Window message used to handle the form timer
#define WINMSG_OPEN WINMSG_TIMER + 1 //!< This is the Window message used to handle a Open window request
#define WINMSG_CLOSE WINMSG_OPEN + 1 //!< This is the Window message used to handle a Close window request


public:
	System::Timers::Timer^ idleTimer; //!< This is the form Timer used to schedule the Idle Status activities
	

public:
	void idleStatusManagement(void);	//!< This is the Idel Status activity handler
	void initIdleStatus(void);			//!< Initializes the form at the Open event
	
	void open(void);					//!< Open window request method
	void close(void);					//!< Close window request method
private: System::Windows::Forms::Panel^ mAsPanel;
public:




private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ VoutLabel;


public:

public:
	bool open_status;					//!< Current Open/Close Status
	   

private:HWND window;
private: System::Windows::Forms::Label^ labelDate;

private: System::Windows::Forms::Label^ labelTime;
private: System::Windows::Forms::PictureBox^ QuitButton;
private: System::Windows::Forms::Label^ BoardTestLabel;




private: System::Windows::Forms::Panel^ mainPanel;







private:void formInitialization(void);

	
public:
	IdleForm(void)
	{
		InitializeComponent();
		window = static_cast<HWND>(Handle.ToPointer());		
		formInitialization();

	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~IdleForm()
	{
		if (components)
		{
			delete components;
		}
	}




protected:
private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->labelDate = (gcnew System::Windows::Forms::Label());
		this->labelTime = (gcnew System::Windows::Forms::Label());
		this->mainPanel = (gcnew System::Windows::Forms::Panel());
		this->mAsPanel = (gcnew System::Windows::Forms::Panel());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->VoutLabel = (gcnew System::Windows::Forms::Label());
		this->QuitButton = (gcnew System::Windows::Forms::PictureBox());
		this->BoardTestLabel = (gcnew System::Windows::Forms::Label());
		this->mainPanel->SuspendLayout();
		this->mAsPanel->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->QuitButton))->BeginInit();
		this->SuspendLayout();
		// 
		// labelDate
		// 
		this->labelDate->AutoSize = true;
		this->labelDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->labelDate->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(156)), static_cast<System::Int32>(static_cast<System::Byte>(149)),
			static_cast<System::Int32>(static_cast<System::Byte>(149)));
		this->labelDate->Location = System::Drawing::Point(12, 964);
		this->labelDate->Name = L"labelDate";
		this->labelDate->Size = System::Drawing::Size(100, 24);
		this->labelDate->TabIndex = 7;
		this->labelDate->Text = L"27/10/2023";
		// 
		// labelTime
		// 
		this->labelTime->AutoSize = true;
		this->labelTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->labelTime->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(156)), static_cast<System::Int32>(static_cast<System::Byte>(149)),
			static_cast<System::Int32>(static_cast<System::Byte>(149)));
		this->labelTime->Location = System::Drawing::Point(12, 988);
		this->labelTime->Name = L"labelTime";
		this->labelTime->Size = System::Drawing::Size(88, 24);
		this->labelTime->TabIndex = 9;
		this->labelTime->Text = L"10:35 PM";
		// 
		// mainPanel
		// 
		this->mainPanel->Controls->Add(this->BoardTestLabel);
		this->mainPanel->Controls->Add(this->mAsPanel);
		this->mainPanel->Location = System::Drawing::Point(0, 0);
		this->mainPanel->Name = L"mainPanel";
		this->mainPanel->Size = System::Drawing::Size(600, 800);
		this->mainPanel->TabIndex = 14;
		// 
		// mAsPanel
		// 
		this->mAsPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->mAsPanel->Controls->Add(this->label6);
		this->mAsPanel->Controls->Add(this->VoutLabel);
		this->mAsPanel->Location = System::Drawing::Point(16, 68);
		this->mAsPanel->Name = L"mAsPanel";
		this->mAsPanel->Size = System::Drawing::Size(247, 244);
		this->mAsPanel->TabIndex = 14;
		// 
		// label6
		// 
		this->label6->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label6->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->label6->Location = System::Drawing::Point(3, 0);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(116, 24);
		this->label6->TabIndex = 13;
		this->label6->Text = L"Tool";
		this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// VoutLabel
		// 
		this->VoutLabel->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->VoutLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(156)), static_cast<System::Int32>(static_cast<System::Byte>(149)),
			static_cast<System::Int32>(static_cast<System::Byte>(149)));
		this->VoutLabel->Location = System::Drawing::Point(174, 0);
		this->VoutLabel->Name = L"VoutLabel";
		this->VoutLabel->Size = System::Drawing::Size(72, 24);
		this->VoutLabel->TabIndex = 12;
		this->VoutLabel->Text = L"270";
		this->VoutLabel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		// 
		// QuitButton
		// 
		this->QuitButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->QuitButton->Location = System::Drawing::Point(214, 812);
		this->QuitButton->Name = L"QuitButton";
		this->QuitButton->Size = System::Drawing::Size(200, 200);
		this->QuitButton->TabIndex = 15;
		this->QuitButton->TabStop = false;
		// 
		// BoardTestLabel
		// 
		this->BoardTestLabel->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->BoardTestLabel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
			static_cast<System::Int32>(static_cast<System::Byte>(0)));
		this->BoardTestLabel->Location = System::Drawing::Point(20, 9);
		this->BoardTestLabel->Name = L"BoardTestLabel";
		this->BoardTestLabel->Size = System::Drawing::Size(555, 40);
		this->BoardTestLabel->TabIndex = 14;
		this->BoardTestLabel->Text = L"Board Test Panel";
		this->BoardTestLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// IdleForm
		// 
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
			static_cast<System::Int32>(static_cast<System::Byte>(60)));
		this->ClientSize = System::Drawing::Size(600, 1024);
		this->ControlBox = false;
		this->Controls->Add(this->QuitButton);
		this->Controls->Add(this->mainPanel);
		this->Controls->Add(this->labelDate);
		this->Controls->Add(this->labelTime);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->Name = L"IdleForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
		this->mainPanel->ResumeLayout(false);
		this->mAsPanel->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->QuitButton))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

	protected:  virtual void WndProc(System::Windows::Forms::Message% m) override;

	private: System::Void onIdleTimeout(Object^ source, System::Timers::ElapsedEventArgs^ e)
	{
		SendMessageA(window, WINMSG_TIMER, 0, 0);
	}

	
	

};

