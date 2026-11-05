
#include "PCB.h"
#include "ConfigurationFiles.h"
#include "Log.h"
#include <thread>

void PCB::runningLoop(void) {
    static bool commerr = false;
   
    // Test the communication status
    if (commerr != isCommunicationError()) {
        commerr = isCommunicationError();
        if (isCommunicationError()) {
            LogClass::logInFile("COMMUNICATION ERROR");
        }
        else {
            LogClass::logInFile("COMMUNICATION OK");
        }
    }


    //	System Status Register
    protocol.status_register.decodeSystemStatusRegister(readStatusRegister((unsigned char)ProtocolStructure::StatusRegister::register_index::SYSTEM_STATUS_IDX));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    return;


   
}



/// <summary>
/// 
/// </summary>
/// 
/// This function activate a One Shot alarm notifying the 
/// operator that the device has been reset. 
/// 
/// 
/// <param name=""></param>
void PCB::resetLoop(void) {

    LogClass::logInFile("RESET EVENT");
}

/// <summary>
/// This is the configuration loop routine executed at the beginning of the 
/// device connection, before to execute the runningLoop() routine.
/// 
/// 
/// </summary>
/// <param name=""></param>
/// <returns>true if the configuration success</returns>
bool PCB::configurationLoop(void) {
    
    LogClass::logInFile("CONFIGURATION EVENT");

    return true;
}
