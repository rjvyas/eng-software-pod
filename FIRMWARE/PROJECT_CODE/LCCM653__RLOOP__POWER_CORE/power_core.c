/**
 * @file		POWER_CORE.C
 * @brief		Top Level for the Power Node Core systems
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__CORE
 * @ingroup POWER_NODE
 * @{ */

#include "power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the power node, this should be the first call
 * 
 * @st_funcMD5		C31656CC99825E8482652B26957C9295
 * @st_funcID		LCCM653R0.FILE.000.FUNC.001
 */
void vPWRNODE__Init(void)
{

	//init the fault handling system
	vPWRNODE_FAULTS__Init();

	//setup the power node basic states and allow the process function to bring all the devices and
	//subsystems on line.
	sPWRNODE.sInit.eState = INIT_STATE__START;

	//init the guarding systems
	sPWRNODE.u32Guard1 = 0xABCD9876U;
	sPWRNODE.u32Guard2 = 0x12983465U;

	sPWRNODE.u32NodePressCounter = 0U;
	sPWRNODE.u32NodeTempCounter = 0U;

}


/***************************************************************************//**
 * @brief
 * Process the power node states, this should be called as quick as possible from
 * the main program loop.
 * 
 * @st_funcMD5		29444FE8792442CF1FBD5ACA34CF1776
 * @st_funcID		LCCM653R0.FILE.000.FUNC.002
 */
void vPWRNODE__Process(void)
{

	Luint8 u8Test;
	Luint32 u32Test;

	//handle the init states here
	/**
	\dot
	 digraph G {
	 INIT_STATE__START -> INIT_STATE__COMMS [label = "After Setup"];
	 INIT_STATE__COMMS -> INIT_STATE__BATT_TEMP_START [label = "After configure serial comms devices"];
	 INIT_STATE__CELL_TEMP_START -> INIT_STATE__CELL_TEMP_SEARCH;
	 INIT_STATE__CELL_TEMP_SEARCH -> INIT_STATE__CELL_TEMP_SEARCH [label = "u8DS18B20_ADDX__SearchSM_IsBusy() == 1"];
	 INIT_STATE__CELL_TEMP_SEARCH -> INIT_STATE__CELL_TEMP_SEARCH_DONE  [label = "u8DS18B20_ADDX__SearchSM_IsBusy() == 0"];
	 INIT_STATE__CELL_TEMP_SEARCH_DONE -> INIT_STATE__BMS
	 }
	 \enddot
	 */
	switch(sPWRNODE.sInit.eState)
	{

		case INIT_STATE__UNKNOWN:
			//todo
			//should never get here.
			break;

		case INIT_STATE__START:
#ifndef WIN32
			//We have been put into Init Start state, bring up the basic low level
			//RM4 systems that do not return error codes

			//setup flash memory access
			vRM4_FLASH__Init();

			//int the RM4's EEPROM
			#if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U
				vRM4_EEPROM__Init();
			#endif

			//init the EEPROM Params
			#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U
				vSIL3_EEPARAM__Init();
			#endif

			//not an ideal place, but we need our personality
			u8Test = u8SIL3_EEPARAM_CRC__Is_CRC_OK(	C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A,
												C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B,
												C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_CRC);
			if(u8Test == 1U)
			{
				//we are good
				u32Test = u32SIL3_EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A);
				if(u32Test < (Luint32)PWRNODE_TYPE__PACK_MAX)
				{
					//Set the new personality
					sPWRNODE.ePersonality = (E_PWRNODE_TYPE_T)u32Test;
				}
				else
				{
					//default
					sPWRNODE.ePersonality = PWRNODE_TYPE__PACK_A;
				}


			}
			else
			{
				//reload
				vSIL3_EEPARAM__WriteU32(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A, (Luint32)PWRNODE_TYPE__PACK_A, DELAY_T__DELAYED_WRITE);
				vSIL3_EEPARAM__WriteU32(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B, (Luint32)PWRNODE_TYPE__PACK_A, DELAY_T__IMMEDIATE_WRITE);

				vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A,
														C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B,
														C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_CRC);
				sPWRNODE.ePersonality = PWRNODE_TYPE__PACK_A;
			}

			if(sPWRNODE.ePersonality == PWRNODE_TYPE__PACK_B)
			{
				sPWRNODE.u16EthPort = 9111U;
			}
			else
			{
				sPWRNODE.u16EthPort = 9110U;
			}


			//DMA
			vRM4_DMA__Init();

			//GIO
			vRM4_GIO__Init();

			//CPU Load monitoring
			vRM4_CPULOAD__Init();

			//setup UART, SCI2 = Pi Connection
#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U
			vRM4_SCI__Init(SCI_CHANNEL__2);
			vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 57600U);
#endif
			//vRM4_SCI_HELPERS__DisplayText(SCI_CHANNEL__2, "LOK\r\n", 5U);
			//vRM4_SCI_INT__Enable_Notification(SCI_CHANNEL__2, SCI_RX_INT);
			//vRM4_SCI__TxByte(SCI_CHANNEL__2, 0xAAU);

#else
			//on win32 set personality
			sPWRNODE.ePersonality = PWRNODE_TYPE__PACK_A;

			//Init any win32 variables
			vPWRNODE_WIN32__Init();

			//emit a message
			DEBUG_PRINT("INIT_STATE__START");
#endif

			//start the pi comms layer
			#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
				#if C_LOCALDEF__LCCM653__ENABLE_PI_COMMS == 1U
					vPWRNODE_PICOMMS__Init();
				#endif
			#endif


			//move to next state
			sPWRNODE.sInit.eState = INIT_STATE__COMMS;

			break;


		case INIT_STATE__COMMS:
#ifndef WIN32
			//init any comms channels

			//get the SPI up for the BMS system
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

			//get the I2C up for the networked sensors
			vRM4_I2C_USER__Init();
#endif
			//startup the ethernet
			#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
				vPWRNODE_NET__Init();
			#endif

			//move to next state
			//if we have the batt temp system enabled (DS18B20) then start the cell temp system
			sPWRNODE.sInit.eState = INIT_STATE__DC_CONVERTER;
			break;

		case INIT_STATE__DC_CONVERTER:

			//startup the ADC for voltage and current measurement.
#ifndef WIN32
			vRM4_ADC_USER__Init();
#endif

			//make sure we latch on the DC/DC converter now.
			#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
				vPWRNODE_DC__Init();
			#endif

			//do the charger too
			#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U

				vPWRNODE_CHG__Init();
			#endif

			//move to next state
			//if we have the batt temp system enabled (DS18B20) then start the cell temp system
			sPWRNODE.sInit.eState = INIT_STATE__CELL_TEMP_START;
			break;


		case INIT_STATE__CELL_TEMP_START:

			#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
				//start the battery temp system
				vPWRNODE_BATTTEMP__Init();

			#endif

			//Start the BMS
			sPWRNODE.sInit.eState = INIT_STATE__BMS;
			break;


		case INIT_STATE__BMS:

			//init the BMS layer
			#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
				vPWRNODE_BMS__Init();
			#endif

			//start the TSYS01 temp sensor
			sPWRNODE.sInit.eState = INIT_STATE__TSYS01;
			break;


		case INIT_STATE__TSYS01:

			#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U
				// Init the node temp subsystem
				vPWRNODE_NODETEMP__Init();
			#endif

			//Start the node pressure system
			sPWRNODE.sInit.eState = INIT_STATE__MS5607;
			break;

		case INIT_STATE__MS5607:
			#if C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS == 1U
				// Init the node pressure subsystem
				vPWRNODE_NODEPRESS__Init();
			#endif

			//change to run state
			sPWRNODE.sInit.eState = INIT_STATE__START_TIMERS;
			break;


		case INIT_STATE__START_TIMERS:
#ifndef WIN32
			//int the RTI
			vRM4_RTI__Init();

			//start the relevant RTI interrupts going.
			//100ms timer
			vRTI_COMPARE__Enable_CompareInterrupt(0);
			//10ms timer
			vRTI_COMPARE__Enable_CompareInterrupt(1);

			vRM4_RTI__Start_Interrupts();
			//Starts the counter zero
			vRM4_RTI__Start_Counter(0);
			vRM4_RTI__Start_Counter(1);

			//kick off the ADC too
			vRM4_ADC_USER__StartConversion();
#endif //win32
			//move state
			sPWRNODE.sInit.eState = INIT_STATE__START_LOW_SYSTEM;
			break;

		case INIT_STATE__START_LOW_SYSTEM:

			#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U
				vPWR_PVPRESS__Init();
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_COOLING == 1U
				vPWR_COOLING__Init();
			#endif

			//move state
			sPWRNODE.sInit.eState = INIT_STATE__RUN;
			break;

		case INIT_STATE__RUN:

#ifndef WIN32
			//CPU load monitoring processing.
			vRM4_CPULOAD__Process();

			//mark the entry point
			vRM4_CPULOAD__While_Entry();

			//process any ADC averaging.
			vRM4_ADC_USER__Process();
#endif //#ifndef WIN32

			//normal run state
			#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
				#if C_LOCALDEF__LCCM653__ENABLE_PI_COMMS == 1U
					vPWRNODE_PICOMMS__Process();
				#endif
			#endif

			//process the DC/DC conveter, may need to pet the watchdog, etc
			#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
				vPWRNODE_DC__Process();
			#endif

			//do the charger too
			#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
				vPWRNODE_CHG__Process();

			#endif

			//process any BMS tasks
			#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
				vPWRNODE_BMS__Process();
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
				//process the DS18B20 1-wire subsystem
				vPWRNODE_BATTTEMP__Process();
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP == 1U
				if(sPWRNODE.u32NodeTempCounter == 1U)
				{
					// Process the node temp subsystem
					vPWRNODE_NODETEMP__Process();
					sPWRNODE.u32NodeTempCounter = 0U;
				}
				else
				{
					//come back later
				}
			#endif
			#if C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS == 1U
				if(sPWRNODE.u32NodePressCounter == 1U)
				{
					// Process the node pressure subsystem
					vPWRNODE_NODEPRESS__Process();
					sPWRNODE.u32NodePressCounter = 0U;
				}
				else
				{
					//check later
				}
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U
				vPWR_PVPRESS__Process();
			#endif

			#if C_LOCALDEF__LCCM653__ENABLE_COOLING == 1U
				vPWR_COOLING__Process();
			#endif

			//process the main state machine
			vPWRNODE_SM__Process();

#ifndef WIN32
			//mark th exit point
			vRM4_CPULOAD__While_Exit();
#endif

		break;



		default:
			//todo:
			break;

	}//switch(sPWRNODE.sInit.eState)


	if(sPWRNODE.sInit.eState > INIT_STATE__COMMS)
	{
		//process the ethernet.
		#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
			vPWRNODE_NET__Process();
		#endif

	}

}


/***************************************************************************//**
 * @brief
 * 100ms timer
 * 
 * @st_funcMD5		2113B1C62D2E2C21EB9C42EAAD17D8B5
 * @st_funcID		LCCM653R0.FILE.000.FUNC.003
 */
void vPWRNODE__RTI_100MS_ISR(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_PI_COMMS == 1U
		vPWRNODE_PICOMMS__100MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
		//tell the DC/DC converter about us for pod safe command.
		vPWRNODE_DC__100MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U
		vPWR_PVPRESS__100MS_ISR();
	#endif
	#if C_LOCALDEF__LCCM653__ENABLE_COOLING == 1U
		vPWR_COOLING_EDDY__100MS_ISR();
		vPWR_COOLING_HOVER__100MS_ISR();
		vPWR_COOLING__100MS_ISR();
	#endif

	sPWRNODE.u32NodePressCounter = 1U;
	sPWRNODE.u32NodeTempCounter = 1U;

}


/***************************************************************************//**
 * @brief
 * 10ms timer
 * 
 * @st_funcMD5		6A863930CAD007EDEE0C5B0179EA027A
 * @st_funcID		LCCM653R0.FILE.000.FUNC.004
 */
void vPWRNODE__RTI_10MS_ISR(void)
{
	#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
		#if C_LOCALDEF__LCCM644__USE_10MS_ISR == 1U
			vDS18B20__10MS_ISR();
		#endif
	#endif

	#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
		vPWRNODE_NET__10MS_ISR();
	#endif

	#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
		vATA6870__10MS_ISR();
	#endif
}


//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_ETHERNET
	#error
#endif
#ifndef C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP
	#error
#endif

#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

