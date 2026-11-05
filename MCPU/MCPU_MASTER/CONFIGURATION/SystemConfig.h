#pragma once
#include "ConfigFile.h"

/// \addtogroup ConfigurationFilesDescription 
/// <div style="page-break-after: always;"></div>
/// 
/// \section SystemConfig SystemInit.cnf configuration file
/// 
/// ## Overview
/// 
/// This configuration file initializes the Application and its communication interaces.
/// 
/// + **Name of the configuration file:** SystemInit.cnf
/// + **Current revision code:** 1;
/// 
/// ## Parameter Description
/// 
/// This configuration file contains the following parameter rows: 
/// + Application Running Mode: sets the application run mode as Normal, Demo, Simulated modes;
/// + Simulated Mode Definition: sets the modulee behavior when in simulated mode;
/// + Installation name: set the name of the target installaion;
/// + Package revision: sets the required revision of the Gantry devices;
/// + AWS connection parameters: sets the IP address and port number for the AWS connection;
/// + Application Log parameters: defines the parameters for the Application log file generation;
/// + Application Debug parameters: defines the parameters for the Application Debug tool;
/// 
/// 


ref class SystemConfig
{
public:
    literal System::String^ FILENAME = "SystemInit.cnf";
    literal int     FILE_REVISION = 1;

    /// \addtogroup  ConfigurationFilesDescription 
    /// 
    /// ### Application Running Mode Parameters Row
    /// 
    /// This parameter sets the Application Running Mode.
    /// 
    /// < RUNNING_MODE, Mode >
    /// 
    /// |Param|Type|Default|Range|Descrption|
    /// |:--|:--|:--|:--|:--|
    /// |Mode|String|"NORMAL"|"NORMAL"/"DEMO"/"SYM"|Application Running Mode|
    /// 
    /// + "NORMAL": the application runs normally with all the real peripherals connected and with all the Operating rules;
    /// + "DEMO": the application runs in demo mode with a subset of the peripheral connected and with a reduced operating rules;
    /// + "SYM": the application runs in simulation mode. 
    /// 
    /// When the Application runs in Simulation mode, it tries to connect with the McpuSym.exe application.
    /// The simulated peripheral (see the Simulated Mode Definition parameter) are then simulated by McpuSym.exe \n
    /// and all the communication to those peripherals are redirect to the Simulator.
    /// 
    ///     NOTE: When in Simulation mode, the Operating rules applies. 
    ///   
    /// 
    literal System::String^ PARAM_RUNNING_MODE = "RUNNING_MODE";
    literal System::String^ PARAM_RUNNING_MODE_COMMENT = "This is the Gantry Running Mode Definition: NORMAL, DEMO, SYM";
    literal int             PARAM_RUNNING_MODE_STATUS = 0;
    literal System::String^ PARAM_RUNNING_MODE_STATUS_DEFAULT = "NORMAL";

    /// \addtogroup  ConfigurationFilesDescription 
    /// 
    /// ### Simulation Mode Parameters Row
    /// 
    /// This parameter sets the Simulator behavior.
    /// 
    /// < SYM_MODE, EthIp,EthPort,SymCan,SymGenerator,SymTilt,SymArm,SymBody,SymVertical,SymSlide,SymPcb301,SymPcb302,SymPcb303,SymPcb304,SymPcb325,SymPcb326 >
    /// 
    /// |Param|Type|Default|Range|Descrption|
    /// |:--|:--|:--|:--|:--|
    /// |EthIp|Ip4 Address|"127.0.0.1"|Ip Address Range|IP Address of the Simulator process|
    /// |EthPort|16 Bit Integer|20000|Port Range|IP Port of the Simulator process|
    /// |AUTOSTART|bool|1|0:1|Automatic start the local simultor application|
    /// |SymCan|Byte|0|1/0|Can Module: 1= normal mode, 0 = simulated mode|
    /// |SymGenerator|Byte|0|1/0|Generator Module: 1= normal mode, 0 = simulated mode|
    /// |SymTilt|Byte|0|1/0|Tilt Module: 1= normal mode, 0 = simulated mode|  
    /// |SymArm|Byte|0|1/0|Arm Module: 1= normal mode, 0 = simulated mode|  
    /// |SymBody|Byte|0|1/0|Body Module: 1= normal mode, 0 = simulated mode|
    /// |SymVertical|Byte|0|1/0|Vertical Module: 1= normal mode, 0 = simulated mode| 
    /// |SymSlide|Byte|0|1/0|Slide Module: 1= normal mode, 0 = simulated mode| 
    /// |SymPcb301|Byte|0|1/0|PCB301 Module: 1= normal mode, 0 = simulated mode| 
    /// |SymPcb302|Byte|0|1/0|PCB302 Module: 1= normal mode, 0 = simulated mode|
    /// |SymPcb303|Byte|0|1/0|PCB303 Module: 1= normal mode, 0 = simulated mode|
    /// |SymPcb304|Byte|0|1/0|PCB304 Module: 1= normal mode, 0 = simulated mode|
    /// |SymPcb325|Byte|0|1/0|PCB325 Module: 1= normal mode, 0 = simulated mode|
    /// |SymPcb326|Byte|0|1/0|PCB326 Module: 1= normal mode, 0 = simulated mode|
    /// 
    literal System::String^ PARAM_SYM_MODE = "SYM_MODE";
    literal System::String^ PARAM_SYM_MODE_COMMENT = "SYM Mode Setting: [1=Run, 0=Sim]: ip, port, autostart, can-driver, generator, tilt, Arm,Body,Vertical,Slide, 301, 302, 303,304,325,326";
    literal int     SYM_MODE_IP = 0;
    literal int     SYM_MODE_PORT = 1;
    literal int     SYM_AUTOSTART = 2;
    literal int     SYM_MODE_CAN = 3;
    literal int     SYM_MODE_PCB334 = 4;
    literal System::String^ PARAM_SYM_MODE_IP_DEFAULT = "127.0.0.1";
    literal System::String^ PARAM_SYM_MODE_PORT_DEFAULT = "20000";
    literal System::String^ PARAM_SYM_AUTOSTART_DEFAULT = "1";
    literal System::String^ PARAM_SYM_MODE_CAN_DEFAULT = "0";
    literal System::String^ PARAM_SYM_MODE_PCB334_DEFAULT = "0";
    


    /// \addtogroup  ConfigurationFilesDescription 
    /// 
    /// ### Installation Name Parameters Row
    /// 
    /// This parameter sets the Installation Name string.
    /// 
    /// < INSTALL_NAME, Name >
    /// 
    /// |Param|Type|Default|Range|Descrption|
    /// |:--|:--|:--|:--|:--|
    /// |Name|String|"FACTORY INSTALLATION"|-|Name of the Installation|
    /// 
    /// The Installation name is displayed in the Top of the Gantry displays.  
    /// 
    literal System::String^ PARAM_INSTALLATION_NAME = "INSTALL_NAME";
    literal System::String^ PARAM_INSTALLATION_NAME_COMMENT = "Name of the installation";
    literal int     PARAM_INSTALLATION_NAME_TOP = 0;
    literal System::String^ PARAM_INSTALLATION_NAME_TOP_DEFAULT = "FACTORY INSTALLATION";


    
    /// \addtogroup  ConfigurationFilesDescription 
    /// 
    /// ### Application Logger Parameters Row
    /// 
    /// This parameter sets the Application Logger parameters.
    /// 
    /// < LOG_DIRECTORY, Directory, EnableLog>
    /// 
    /// |Param|Type|Default|Range|Descrption|
    /// |:--|:--|:--|:--|:--|
    /// |Directory|String|"\\GANTRY_LOGS"|-|Directory where the Log files are generated (if enabled)|
    /// |EnableLog|String|"ON"|"ON"/"OFF"|Enables (ON) or Disables (OFF) The log file generation|
    /// 
    literal System::String^ PARAM_LOG_DIRECTORY = "LOG_DIRECTORY";
    literal System::String^ PARAM_LOG_DIRECTORY_COMMENT = "The directory reserved for logs ";
    literal int PARAM_DIR = 0;
    literal int PARAM_ENA = 1;
    literal System::String^ PARAM_LOG_DIRECTORY_DEFAULT = "\\GANTRY_LOGS";
    literal System::String^ PARAM_LOG_ENA_DEFAULT = "ON";

    /// \addtogroup  ConfigurationFilesDescription 
    /// 
    /// ### Application Debugger Parameters Row
    /// 
    /// This parameter sets the Debugger parameters.
    /// 
    /// < DEBUG, DbgEna, EthIp, EthPort>
    /// 
    /// |Param|Type|Default|Range|Descrption|
    /// |:--|:--|:--|:--|:--|
    /// |DbgEna|String|"OFF"|"ON"/"OFF"|Enables (ON) or Disables (OFF) The Debugger tool |
    /// |EthIp|Ip4 Address|"127.0.0.1"|Ip Address Range|IP Address of the Debugger server socket|
    /// |EthPort|16 Bit Integer|20001|Port Range|IP Port of the Debugger server socket|
    /// 
    literal System::String^ PARAM_DEBUG = "DEBUG";
    literal System::String^ PARAM_DEBUG_COMMENT = "This is the Debug fetaures";
    literal int PARAM_DEBUG_ENA = 0;
    literal int PARAM_DEBUG_IP = 1;
    literal int PARAM_DEBUG_PORT = 2;
    literal System::String^ PARAM_DEBUG_ENA_DEFAULT = "OFF";
    literal System::String^ PARAM_DEBUG_ENA_IP_DEFAULT = "127.0.0.1";
    literal System::String^ PARAM_DEBUG_ENA_PORT_DEFAULT = "20001";

    static ConfigFile^ Configuration = gcnew ConfigFile(FILENAME, FILE_REVISION,
        CONFIG_FILE_DESCRIPTOR
        {
            CONFIG_FILE_ITEM(PARAM_RUNNING_MODE, PARAM_RUNNING_MODE_COMMENT, CONFIG_FILE_DEFAULT{
            PARAM_RUNNING_MODE_STATUS_DEFAULT,           
            }),

            CONFIG_FILE_ITEM(PARAM_SYM_MODE, PARAM_SYM_MODE_COMMENT, CONFIG_FILE_DEFAULT{            
            PARAM_SYM_MODE_IP_DEFAULT,
            PARAM_SYM_MODE_PORT_DEFAULT,
            PARAM_SYM_AUTOSTART_DEFAULT,
            PARAM_SYM_MODE_CAN_DEFAULT,
            PARAM_SYM_MODE_PCB334_DEFAULT,            
            }),


            CONFIG_FILE_ITEM(PARAM_INSTALLATION_NAME, PARAM_INSTALLATION_NAME_COMMENT, CONFIG_FILE_DEFAULT{
            PARAM_INSTALLATION_NAME_TOP_DEFAULT,            
            }),

            CONFIG_FILE_ITEM(PARAM_LOG_DIRECTORY, PARAM_LOG_DIRECTORY_COMMENT, CONFIG_FILE_DEFAULT{
            PARAM_LOG_DIRECTORY_DEFAULT,
            PARAM_LOG_ENA_DEFAULT,
            }),

            CONFIG_FILE_ITEM(PARAM_DEBUG, PARAM_DEBUG_COMMENT, CONFIG_FILE_DEFAULT{
            PARAM_DEBUG_ENA_DEFAULT,
            PARAM_DEBUG_ENA_IP_DEFAULT,
            PARAM_DEBUG_ENA_PORT_DEFAULT
            }),
            
        }
    );
};
