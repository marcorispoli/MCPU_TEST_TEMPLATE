
#include "idleForm.h"

#include "ConfigurationFiles.h"

#include "PCB.h"
#include "../gantry_global_status.h"


#define QUIT_IMAGE Image::FromFile(Gantry::applicationResourcePath + "QuitIcon.PNG")
#define PANEL_NAME "BOART TEST TEMPLATE"

/// <summary>
/// \ingroup IDLEIMPL
/// 
/// This is the Form initialization callback.
/// 
/// </summary>
/// 
/// This routine initializes the object of the form:
/// 
/// <param name=""></param>
void IdleForm::formInitialization(void) {

	// Initialize the position of the form
	this->Left = Gantry::monitor_X0;
	this->Top = Gantry::monitor_Y0;

	// Assegna immagine al bottone di uscita
	QuitButton->BackgroundImage = QUIT_IMAGE;
	BoardTestLabel->Text = PANEL_NAME;

	/// The Idle perating Mode window timer is initialized with 100ms schedule.
	idleTimer = gcnew System::Timers::Timer(100);
	idleTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &IdleForm::onIdleTimeout);
	idleTimer->Stop();

	/// The window form is finally Hided.
	this->Hide();
	open_status = false;
}

/// <summary>
/// This function is called when the Idle Operating Status is activated
/// </summary>
/// 
/// The function initializes the content of the GUI at the current 
/// gantry status.
/// 
/// The function sets the Gantry device at the expected status:
/// 
/// + The compressor device is disabled;
/// + All the Motors are disabled;
/// + The Format collimation is set to OPEN;
/// + The Filter selector is set on the Pb to protect the Tube hole;
/// + The Mirror is set to Home position and the light switched off;
/// + The manual key buttons are disabled;
/// + The Grid device is set to Out Of Field; 
/// 
/// <param name=""></param>
void IdleForm::initIdleStatus(void) {

	/// The system date and time is initialized;
	/// \note
	/// the date and time is always showed on the bottom of the window
	System::DateTime date;
	date = System::DateTime::Now;

	
	labelDate->Text = date.Day + ":" + date.Month + ":" + date.Year;
	labelTime->Text = date.Hour + ":" + date.Minute + ":" + date.Second;

	
	/// The Idle Operatig Mode window timer is started with 100ms schedule
	idleTimer->Start();	


}

/// <summary>
/// This is the function to open the Idle Form
/// </summary>
/// 
/// The function can be called by different threads then the main thread
/// where the form resides. 
/// 
/// Beacuse the window's items can be handled only in the same thread of the window form,
/// this function put a window message on the window queue so that it will be handled into the main thread.
/// 
/// \warning
/// When the function returns, an unpredictable delay time can happen before to get the form operating.
/// 
/// <param name=""></param>
void IdleForm::open(void) {
	SendMessageA(window , WINMSG_OPEN, 0, 0); // OPEN EVENT MESSAGE
}

/// <summary>
/// This is the function to close the Idle Form
/// </summary>
/// 
/// The function can be called by different threads then the main thread
/// where the form resides. 
/// 
/// Beacuse the window's items can be handled only in the same thread of the window form,
/// this function put a window message on the window queue so that it will be handled into the main thread.
/// 
/// \warning
/// When the function returns, an unpredictable delay time can happen before to get the form disappeared.
/// 
/// <param name=""></param>
void IdleForm::close(void) {
	SendMessageA(window, WINMSG_CLOSE, 0, 0); // CLOSE EVENT MESSAGE	
}


/// <summary>
/// This is the main scheduled routine of the Idle Status management.
/// </summary>
/// 
/// This function is periodically called by the Idle Status timer, scheduled
/// every 100ms. (See the formInitializtion() )
/// 
/// The function updates the current device data that are displayed 
/// on the GUI.
/// 
/// In particolar:
/// 
/// <param name=""></param>
void IdleForm::idleStatusManagement(void) {
	static int xray_mode_status = 0;

	/// The date and the time is updated on the bottom of the windows;
	System::DateTime date;
	date = System::DateTime::Now;
	
	labelTime->Text = date.Hour + ":" + date.Minute + ":" + date.Second;

	

}

/// <summary>
/// This is the callback of the Window Message Handler.
/// </summary>
/// 
/// The window message handler is used to handle 
/// calling request from other threads then the main thread for the following 
/// pourposes:
/// + The Idle Timer timeout event: this event calls the idleStatusManagement() ;
/// + The Open form request: this is a message coming from a thread that would open the Idle Status;
/// + The Close form request: this is a message coming from a thread that would close the Idle Status;
/// <param name="m">This is the message code </param>
void IdleForm::WndProc(System::Windows::Forms::Message% m)
{
	switch (m.Msg) {

	case (WINMSG_TIMER): // onIdleTimeout
		
		idleStatusManagement();
		break;
	case (WINMSG_OPEN): // on Open Event
		if (open_status) return;
		open_status = true;
		initIdleStatus();
		this->Show();
		break;

	case (WINMSG_CLOSE): // on Close Event
		if (!open_status) return;
		open_status = false;
		idleTimer->Stop();
		
		this->Hide();
		break;
	}

	Form::WndProc(m);
}
