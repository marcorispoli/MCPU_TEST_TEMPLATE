#include "gantry_global_status.h"
#include "IDLE/IdleForm.h"
#include "ConfigurationFiles.h"
#include <mutex>
#include "PCB.h"
#include "Debugger.h"
#include "Log.h"

using namespace System;
using namespace System::Diagnostics;
using namespace System::Windows::Forms;

Gantry::Gantry() {

    // Sets the resource path
    applicationResourcePath = System::IO::Directory::GetCurrentDirectory() + "\\RESOURCES\\";

    // Monitor Identification
    int monitors = Screen::AllScreens->Length;

    // Gets the Monitors position
    for (int i = 0; i < monitors; i++) {

        int H = Screen::AllScreens[i]->Bounds.Height;
        int W = Screen::AllScreens[i]->Bounds.Width;

        if (W == 600) {
            monitor_X0 = Screen::AllScreens[i]->Bounds.Left;
            monitor_Y0 = Screen::AllScreens[i]->Bounds.Top;
        }
    }
    LogClass::logInFile("SELECTED MONITOR: X0 = " + monitor_X0.ToString() + ", Y0 = " + monitor_Y0.ToString());




}


void Gantry::initialize(void) {

    // Debugger Tool Activation if requested 
    if (SystemConfig::Configuration->getParam(SystemConfig::PARAM_DEBUG)[SystemConfig::PARAM_DEBUG_ENA] == "ON") {
        Gantry::pDebugger = gcnew DebuggerCLI(SystemConfig::Configuration->getParam(SystemConfig::PARAM_DEBUG)[SystemConfig::PARAM_DEBUG_IP], System::Convert::ToInt16(SystemConfig::Configuration->getParam(SystemConfig::PARAM_DEBUG)[SystemConfig::PARAM_DEBUG_PORT]));
    }

    
    
    // Creates the status Windows
    pIdleForm = gcnew IdleForm();

}


