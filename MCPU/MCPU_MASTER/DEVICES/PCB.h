#pragma once
#include "CanDeviceProtocol.h"
#include "ConfigurationFiles.h"

#define CAN_ADDRESS 0x19
ref class PCB : public CanDeviceProtocol
{
public:

	
	/// <summary>
	/// This class implement the protocol data structure as described in the protocol specification.
	/// </summary>
	ref class ProtocolStructure {
	public:

		ref class StatusRegister {
		public:

			enum class register_index {
				SYSTEM_STATUS_IDX = 0, //!< This is the Collimator internal status    
				NUM_REGISTERS
			};



			static bool decodeSystemStatusRegister(Register^ sys) {
				if (sys == nullptr) return false;
				

				/*
				* enable_contactor = (sys->d1 & 0x1) ? true : false;
				*/
				
				return true;
			}

			Register^ encodeSystemStatusRegister(void) {

				// Creates a register with all bytes set to 0
				CanDeviceProtocol::Register^ sys = gcnew CanDeviceProtocol::Register;

				// Byte 0 of the register
				//sys->d0 = ((unsigned char) temperature);
				

				// Returns the formatted register
				return sys;
			}


			
			static unsigned char temperature;
			
		};


		ref class DataRegister {
		public:

			enum class register_index {
				NUM_REGISTERS = 0,
			};

		};

		ref class ParameterRegister {
		public:

			enum class register_index {
				
				NUM_REGISTERS = 0
			};

		};

		ref class Commands {
		public:
			enum class command_index {
				ABORT_COMMAND = 0, //!< Abort Command (mandatory as for device protocol)
				
			};

			/* EXAMPLE
			CanDeviceCommand^ encodeSetFormatCommand(unsigned char target_format_slot) {
				// if the index is out of range, the collimatin will be st to OPEN in the device
				if (target_format_slot >= NUM_COLLIMATION_SLOTS) target_format_slot = 0;
				return gcnew CanDeviceCommand((unsigned char)command_index::SET_FORMAT, target_format_slot, 0, 0, 0);
			}*/


		};

		static StatusRegister status_register;
		static DataRegister data_register;
		static ParameterRegister parameter_register;
		static Commands command;
	};

	
	/// <summary>
	/// PCB303 Class constructor.
	/// 
	/// The construction initializes several internal variables.
	/// The constructor call the base class setting the address of the controlled device.
	/// 
	/// As soon as the base class is initialized, the communication process starts
	/// and the device is initialized with configurationLoop() routine.
	/// \ingroup PCB303_Interface
	/// </summary>
	public: PCB() : CanDeviceProtocol(CAN_ADDRESS, L"PCB")
	{
		
	}
	static PCB^ device = gcnew PCB();

	/// \ingroup PCB335_Internal
	///@{
	/// 
	protected: 	
		void resetLoop(void) override;//!< This is the Base class resetLoop override function
		void runningLoop(void) override;//!< This is the Base Class override function to handle the normal operation workflow 
		bool configurationLoop(void) override;//!< This is the Base Class override function to handle the device configuration
		
	
	private:	
		
		

	///@}
	
	

	/// \ingroup PCB_Internal
	///@{
	private: 
		static ProtocolStructure protocol; //!< This is the structure with the Status register info
		


	///@}

public:
	/// \ingroup PCB_Interface
	///@{
	
	
	///@}
};


