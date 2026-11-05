#include "gantry_global_status.h"
#include "MainForm.h"
#include "IDLE/idleForm.h"
#include "ConfigurationFiles.h"
#include "CanDriver.h"
#include "CanDeviceProtocol.h"
#include "PCB.h"
#include "Log.h"




#define STARTUP_IMAGE Image::FromFile(Gantry::applicationResourcePath + "BoardStartupIcon.PNG")
#define QUIT_IMAGE Image::FromFile(Gantry::applicationResourcePath + "QuitIcon.PNG")

/// <summary>
/// \ingroup STARTUPIMPL
/// 
/// This is the gui initializtion routine
/// </summary>
/// 
/// This routine initializes the labels of the window
/// and the main window timer.
/// 
/// \note
/// The window timer runs every 100ms and determines the 
/// schedule time for the startup sequences.
/// 
/// 
/// <param name=""></param>
void MainForm::MainFormInitialize(void) {

	// Initialize the position of the form
	this->Left = Gantry::monitor_X0;
	this->Top = Gantry::monitor_Y0;
	

	// Debug on the System Configuration File
	if (SystemConfig::Configuration->isWarning()) {
		LogClass::logInFile("SYSTEM CONFIGURATION FILE:" + SystemConfig::Configuration->getWarningString());
	}

	// Initialize the Package field 
	if (SystemConfig::Configuration->isWarning()) {
		LogClass::logInFile( "> " + SystemConfig::Configuration->getWarningString());
	}

	// Program Icon
	startupIcon->BackgroundImage = STARTUP_IMAGE;
	QuitButton->BackgroundImage = QUIT_IMAGE;

	
	
	// Initialize the Activities
	labelPcbActivity->Text = "Waiting ..";
	labelCanDriverActivity->Text = "Waiting ..";
	

	startupFase = 0;
	startupSubFase = 0;
	startupCompleted = false;
	startupError = false;

	
	// Start the startup session
	startupTimer = gcnew System::Timers::Timer(100);
	startupTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &MainForm::onStartupTimeout);
	startupTimer->Start();
	
	
}


/// <summary>
/// \ingroup STARTUPIMPL
/// This procedure executes the startup of the CanDriver process.
///  
/// </summary>
/// 
/// The procedure determines if the module 
/// shall be activated as simulated mode or Normal mode. 
/// 
/// After the device module is started this procedure 
/// waits for the process initialization completion.
/// 
/// The procedure is called by the window timer 
/// every 100ms and handles the steps with a status machine approach.
/// 
///  
/// <param name=""></param>
/// <returns>
/// + true: the initialization is successfully terminated;
/// + false: the initialization is in progress;
/// 
/// \remarks
/// In case of an error should be detected, 
/// the global variable StartupOperatingModeForm::startupError is set to true;
///  
/// </returns>
bool MainForm::Startup_CanDriver(void) {
	System::String^ string;

	switch (startupSubFase) {

	case 0: // Creates the Can Driver Object
		CanDriver::startNormalMode();
		labelCanDriverActivity->Text = "Connection ..";
		startupSubFase++;
		break;

	case 1:
		if (CanDriver::isError()) {
			labelCanDriverActivity->Text = "STARTUP ERROR!";
			LogClass::logInFile("can driver error : " + CanDriver::getErrorString());
			startupError = true;
			break;
		}

		if (CanDriver::isConnected(false)) {
			labelCanDriverActivity->Text = "RUN IN NORMAL MODE";
			string =  "can driver revision: ";
			string += " API:" + CanDriver::apirev_maj.ToString() + "." + CanDriver::apirev_min.ToString();
			string += " SW:" + CanDriver::swrev_maj.ToString() + "." + CanDriver::swrev_min.ToString();
			string += " HW:" + CanDriver::hwrev_maj.ToString() + "." + CanDriver::hwrev_min.ToString();			
			LogClass::logInFile(string);
			labelCanDriverActivity->ForeColor = Color::LightGreen;
			return true; // Completed
		}

		break;
	
	}

	return false;
}

bool MainForm::Startup_PCB(void) {
	System::String^ string;

	switch (startupSubFase) {

	case 0: // Creates the PCB301 process
		labelPcbActivity->Text = "CONNECTION ..";
		string =  "pcb initialization ..";
		LogClass::logInFile(string);
		PCB::device->runMode();
		startupSubFase++;
		break;

	case 1: // Wait the connection and configuration
		

		if (PCB::device->getModuleStatus() > CanDeviceProtocol::status_options::WAITING_REVISION) {
			labelPcbActivity->Text = "CONFIGURATION ..";
			string =  "pcb firmware revision: ";
			string += " BOOT:" + PCB::device->getBootStatus().ToString() + ", REV:" + PCB::device->getBootRevision();
			string += " APP:" + PCB::device->getAppRevision();
			LogClass::logInFile(string);
			startupSubFase++;
		}
		break;

	case 2: // Wait the connection and configuration		
		if (PCB::device->getModuleStatus() == CanDeviceProtocol::status_options::DEVICE_RUNNING) {
			labelPcbActivity->Text = "RUN IN NORMAL MODE";
			labelPcbActivity->ForeColor = Color::LightGreen;
			return true;
		}

		break;

	}
	return false;
}


/// <summary>
/// \ingroup STARTUPIMPL
/// This procedure is called by the window timer
/// and handles the initialization process sequence.
/// 
/// </summary>
/// 
/// This routine is directly called by the window timer
/// throug the window messages so the thread is the main hread.
/// 
/// 
/// <param name=""></param>
void MainForm::StartupProcedure(void) {
	
	///\todo
	///The initialization nerror condition should be handled properly.
	/// 
	// In case a procedure should set this variable 
	// the initialization process stops here	
	if (startupError) {
		startupTimer->Stop();
		return;
	}

	
	// In case the initialization termines, the Idle Operating Mode is called.
	if (startupCompleted) {
		startupTimer->Stop();
		this->Hide();
		((IdleForm^) Gantry::pIdleForm)->open();
		return;
	}

	// Defines the seqeunce order
	enum {
		INITSEQ = 0,
		CANSEQ,		
		PCBSEQ,
		FINESEQ
	};

	switch (startupFase) {
	case INITSEQ:	startupFase++; break;
	case CANSEQ:	if (Startup_CanDriver())	{ startupFase++; startupSubFase = 0; } break; // Startup of the Can Driver process
	case PCBSEQ: if (Startup_PCB())		{ startupFase++; startupSubFase = 0; } break; // Startup of the PCB301 process
	case FINESEQ:	startupCompleted = true; break;
	}
}

/// <summary>
/// \ingroup STARTUPIMPL
/// 
/// This procedure is called by the Window Message Pipe
/// when the window timer expires. 
/// </summary>
/// 
/// The window timer is called in the thread pull and
/// consequently cannot be used to call any form item 
/// because they resides in the main thread.
/// 
/// When the timer expires a window message (WM_USER + 1) 
/// is used: the WndProc is a callback generated by the window message pump 
/// and resides in the main window thread.
/// 
/// <param name="m"></param>
void MainForm::WndProc(System::Windows::Forms::Message% m)
{
	switch (m.Msg) {

	case (WM_USER + 1): // onStartupTimeout		
		StartupProcedure();
		break;

	case (WM_USER + 2): 
		
		break;
	case (WM_USER + 3): 
		
		break;

	case (WM_USER + 4): 
		
		break;

	case (WM_USER + 5): 
		
		break;
	}


	Form::WndProc(m);
}
