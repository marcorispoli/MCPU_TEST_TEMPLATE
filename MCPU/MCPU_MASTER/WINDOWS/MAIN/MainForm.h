
#pragma once

extern  double dtempo;
#include <Windows.h>


/// \addtogroup OPERMODEDOC
/// <div style="page-break-after: always;"></div>
/// 
/// # Startup Operating Mode
/// 
/// After the program startup (actually the Gantry power up) the following activities shall be executed
/// in the order of apparence:
/// 
/// + Application running mode definition;
/// + Application process initialization;
/// + Gantry Device Communicatin Initialization;
/// + Gantry Device Revision check;
/// 
/// ## Application running mode definition
/// 
/// The Application can work in three ways:
/// + Normal Mode;
/// + Simulation Mode;
/// + Demo mode;
/// 
/// In the \ref SystemConfig the parameter *RUNNING_MODE* sets the current running mode.
///
/// The parameter SystemIni.RUNNING_MODE = "NORMAL" starts the application in Normal Mode;
/// The parameter SystemIni.RUNNING_MODE = "SYM" starts the application in Simulation Mode;
/// The parameter SystemIni.RUNNING_MODE = "DEMO" starts the application in Demo Mode;
/// 
/// ### Application Running Normal Mode 
/// 
/// The application running normal mode is the main running mode 
/// where all operative features are running as for the system specifications.
/// 
/// ### Application Running Simulated Mode
/// 
/// The Simulated mode is a special running mode developed to 
/// help the system developing and debugging fase.
/// 
/// In simulation mode, part or all the Gantry devices can 
/// run in simulated mode. 
/// 
/// The parameter SystemIni.SYM_MODE sets several aspect of the simulation mode (see the \ref SystemConfig description)
/// 
/// In particolar, the application can set individually what are the process that shall run in normal mode or simulated mode:
/// 
/// + Can Driver process: this is the process that control the usb to Can converter device. When in simulated mode, the process doesn't open phisically the device.
/// + PCB301 device process: this is the process that control PCB301 device (service board device). 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + PCB302 device process: this is the process that control PCB302 device (compressor device). 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + PCB303 device process: this is the process that control PCB303 device (collimator device). 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + PCB304 device process: this is the process that control PCB304 device (grid control device). 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + PCB325 device process: this is the process that control PCB325 device (biopsy device). 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + PCB326 device process: this is the process that control PCB326 device (obstacle device). 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + Vertical motor device process: this is the process that control the Vertical motor driver. 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + C-ARM motor device process: this is the process that control the C-ARM motor driver. 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + Body motor device process: this is the process that control the Body motor driver. 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + Tilt motor device process: this is the process that control the Tilt motor driver. 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// + Slide motor device process: this is the process that control the Slide motor driver. 
/// When in simulated mode, the process routes the can frame to the simulator via socket connection;
/// 
/// \note
/// When a process is running in Simulated mode, it actually run as it should be in normal mode:
/// the executing code is exactly the same. The only difference is that 
/// the communication with the simulator is made with a Tcp/Ip socket instead of a Can Bus.
/// 
/// #### Simulator Device
/// 
/// The simulator is a special application that can run into the same 
/// computer or even in a different computer connected with 
/// an ethernet to the computer wher the Gantry application run.
/// 
/// The parameter SystemIni.SYM_MODE defines the IP simulator address and Port.
/// 
/// The parameter can set if the simulator shall automatically start when the application 
/// is set in Simulation mode  (option valid only if the simulator resides in the same pc of the Gantry application).
/// 
/// The simulator, for every simulated device:
/// + simulates the communication protocol;
/// + simulates the internal functions with a realistic timing;
/// + simulates the hardware interactions with other simulated device;
/// + displays the internal device status;
/// 
/// \note 
/// the device functions are simulated basically, reproducing the principal aspects that 
/// can impact with the Gantry activities.
/// 
/// See the Simulator device documentation for more details.
///    
/// ## Application process initialization
/// 
/// Based on the System running mode and related module's operating mode,
/// every device module is activated in real or simulated mode.
/// 
/// The following device modules will be activated in the given sequence:
/// 
///  + CanDriver Module: this is the first process to be activated since it as to open the can bus communication;
///  + PCB301 Module: this process connectes the PCB301 board. this process shall be the second. 
///  This process shall controls the status of the system power before any other process access its controlled device.
/// 
/// The next processes actually may be called with different orders than this:
///  + PCB302 process;
///  + PCB303 process;
///  + PCB304 process;
///  + PCB325 process;
///  + PCB326 preocess;
///  + Generator process;
///  + Vertical process;
///  + Tilt process
///  + Arm process;
///  + Slide process
///  + Body process
/// 
/// The GUI during the process initialization shows the status of the initialization fase.
/// 
/// During the initialization fase, the following activities are implemented:
/// + The bootloader and the revision of the firmware controlling the devices are requested;
/// + The device's registers and parameters are configurated;
/// + The motors are configurated and their internal status are set to a safer condition;
/// 
/// \warning
/// In case a process should fail to complete the initialization, the whole initialization process 
/// fails and the Application enters into a error loop. 
/// In this case the Application may be restarted or the problem may be fixed before to restart 
/// the application again.    
/// 
/// ## Revision Check
/// 
/// If the initializzation process should successfully complete,
/// the Application proceeds with the revision verification.
/// 
/// The \ref SystemConfig defines the expected revisions for all the controlled Gantry devices.
/// 
/// If a revision should not match the expected one, a general error message is activated 
/// preventing the system to enter the Patient Operating mode.
/// 
/// \note
/// In case the revision check process should fail, the application 
/// providdes a service tools to update the non conforming devices. 
/// 
/// \todo 
/// The revision check shall be implemented.
/// 
/// 



/// <summary>
/// \ingroup STARTUPIMPL
/// This is the startup operating mode implementing module
/// 
/// </summary>


	
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// \ingroup STARTUPIMPL
	/// 
	/// This is the Class implementing the Startup Operating mode.
	/// 
	/// </summary>
	/// 
	/// 
	/// 
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			window = static_cast<HWND>(Handle.ToPointer());
			MainFormInitialize();

		}
		
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	

	System::Timers::Timer^ startupTimer; //!< This is the Timer to step the workflow
	HWND window;//!< This is the handle of the windw for the windows message exchange
	int startupFase; //!< This is the current fase of the startup
	int startupSubFase;//!< This is the current sub-fase of the startup
	bool startupCompleted;//!< The Startup completed flag
	private: System::Windows::Forms::PictureBox^ QuitButton;
	public:

	public:

	public:
		bool startupError;//!< The Startup completed in error condition

	private: void MainFormInitialize(void);
	private: void StartupProcedure(void);

	private: bool Startup_CanDriver(void);
	private: bool Startup_PCB(void);
	


	private: System::Windows::Forms::PictureBox^ startupIcon;
	private: System::Windows::Forms::GroupBox^ infoPanel;
	private: System::Windows::Forms::Label^ labelBoardInitialization;
	private: System::Windows::Forms::Label^ labelPcbActivity;







	private: System::Windows::Forms::Label^ labelCanDriverActivity;
	private: System::Windows::Forms::Label^ label9;






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->infoPanel = (gcnew System::Windows::Forms::GroupBox());
			this->labelCanDriverActivity = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->labelPcbActivity = (gcnew System::Windows::Forms::Label());
			this->labelBoardInitialization = (gcnew System::Windows::Forms::Label());
			this->startupIcon = (gcnew System::Windows::Forms::PictureBox());
			this->QuitButton = (gcnew System::Windows::Forms::PictureBox());
			this->infoPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->startupIcon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->QuitButton))->BeginInit();
			this->SuspendLayout();
			// 
			// infoPanel
			// 
			this->infoPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(59)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->infoPanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->infoPanel->Controls->Add(this->labelCanDriverActivity);
			this->infoPanel->Controls->Add(this->label9);
			this->infoPanel->Controls->Add(this->labelPcbActivity);
			this->infoPanel->Controls->Add(this->labelBoardInitialization);
			this->infoPanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold));
			this->infoPanel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(189)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->infoPanel->Location = System::Drawing::Point(26, 248);
			this->infoPanel->Name = L"infoPanel";
			this->infoPanel->Size = System::Drawing::Size(549, 85);
			this->infoPanel->TabIndex = 1;
			this->infoPanel->TabStop = false;
			this->infoPanel->Text = L"PROCESS INITIALIZATION";
			// 
			// labelCanDriverActivity
			// 
			this->labelCanDriverActivity->AutoSize = true;
			this->labelCanDriverActivity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Italic));
			this->labelCanDriverActivity->ForeColor = System::Drawing::Color::White;
			this->labelCanDriverActivity->Location = System::Drawing::Point(216, 25);
			this->labelCanDriverActivity->Name = L"labelCanDriverActivity";
			this->labelCanDriverActivity->Size = System::Drawing::Size(86, 16);
			this->labelCanDriverActivity->TabIndex = 11;
			this->labelCanDriverActivity->Text = L"Connection ...";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(10, 25);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(127, 16);
			this->label9->TabIndex = 10;
			this->label9->Text = L"Can Driver Status";
			// 
			// labelPcbActivity
			// 
			this->labelPcbActivity->AutoSize = true;
			this->labelPcbActivity->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Italic));
			this->labelPcbActivity->ForeColor = System::Drawing::Color::White;
			this->labelPcbActivity->Location = System::Drawing::Point(216, 45);
			this->labelPcbActivity->Name = L"labelPcbActivity";
			this->labelPcbActivity->Size = System::Drawing::Size(86, 16);
			this->labelPcbActivity->TabIndex = 1;
			this->labelPcbActivity->Text = L"Connection ...";
			// 
			// labelBoardInitialization
			// 
			this->labelBoardInitialization->AutoSize = true;
			this->labelBoardInitialization->Location = System::Drawing::Point(10, 45);
			this->labelBoardInitialization->Name = L"labelBoardInitialization";
			this->labelBoardInitialization->Size = System::Drawing::Size(92, 16);
			this->labelBoardInitialization->TabIndex = 0;
			this->labelBoardInitialization->Text = L"PCB Status: ";
			// 
			// startupIcon
			// 
			this->startupIcon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->startupIcon->Location = System::Drawing::Point(50, 26);
			this->startupIcon->Name = L"startupIcon";
			this->startupIcon->Size = System::Drawing::Size(500, 185);
			this->startupIcon->TabIndex = 9;
			this->startupIcon->TabStop = false;
			// 
			// QuitButton
			// 
			this->QuitButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->QuitButton->Location = System::Drawing::Point(133, 412);
			this->QuitButton->Name = L"QuitButton";
			this->QuitButton->Size = System::Drawing::Size(300, 300);
			this->QuitButton->TabIndex = 10;
			this->QuitButton->TabStop = false;
			this->QuitButton->Click += gcnew System::EventHandler(this, &MainForm::ExitButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(59)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(600, 1024);
			this->ControlBox = false;
			this->Controls->Add(this->QuitButton);
			this->Controls->Add(this->startupIcon);
			this->Controls->Add(this->infoPanel);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(189)),
				static_cast<System::Int32>(static_cast<System::Byte>(190)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MainForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"MainForm";
			this->infoPanel->ResumeLayout(false);
			this->infoPanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->startupIcon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->QuitButton))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	protected:  virtual void WndProc(System::Windows::Forms::Message% m) override;

	private: System::Void onStartupTimeout(Object^ source, System::Timers::ElapsedEventArgs^ e)
	{
		SendMessageA(window, WM_USER + 1, 0, 0);
	}
	
	// Pusante di chiusura applicazione
	private: System::Void ExitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		exit(0);
	}
};



