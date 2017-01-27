/**
 * @file		FCU__FLIGHT_CONTROL__COOLING_CONTROL.C
 * @brief		Cooling Control Subsystem
 * @author		Paul Le Henaff
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__FLIGHT_CTL__COOLING_CONTROL
 * @ingroup FCU
 * @{ */
/**
Inputs
=======
operating mode
speed
hover engine 1 temperature, ..., hover engine 8 temperature
stepper motor left temperature, stepper motor right temperature
PV pressure sensor value

Outputs
========
solenoid valve 1 command, ..., solenoid valve 6 command
*/
#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL == 1U

//the structure
extern struct _strFCU sFCU;

struct
{
	E_FCU__COOLING_GS_COMM_T eGSCoolingCommand;

} sCoolingControl;

typedef enum
{
	COOLING_CTL_DO_NOTHING;
	CLOSE_ALL_VALVES;
	SET_VALVE;
	
} E_FCU__COOLING_GS_COMM_T;

void vFCU_FCTL_COOLING__Init(void)
{
	sFCU.sCoolingControl.eGSCommands = COOLING_CTL_DO_NOTHING; // Set the commands from the ground station to DO_NOTHING at startup
}


void vFCU_FCTL_COOLING__Process(void)
{
	vFCU_FCTL_COOLING__ManualCommandsHandle();
	
	Luint32 u32PodSpeed = vFCU__POD_SPEED();

	switch(sFCU.eMissionPhase)
	{
		case MISSION_PHASE__TEST:
		case MISSION_PHASE__PRE_RUN:
		case MISSION_PHASE__POST_RUN:
			/** Main pod command listener*/
			switch(sFCU.eGSCommands)
			{
				case STATIC_HOVERING:
					if (sFCU.sOpStates.u8Lifted == 1U && u32PodSpeed < PODSPEED_STANDBY)
					{
						vFCU_COOLING__Enable();
					}
					break;
				case RELEASE_STATIC_HOVERING: 
					if (sFCU.sOpStates.u8StaticHovering == 1U && u32PodSpeed < PODSPEED_STANDBY)
					{
						vFCU_COOLING__Disable();
					}
					break;
			}
			break;
	}
}

void vFCU_FCTL_COOLING__ManualCommandsHandle(void)
{
	/** Cooling specific command listener*/
	switch(sFCU.sCoolingControl.eGSCommands)
	{
		// manual commands (for debugging etc)
		case CLOSE_ALL_VALVES:
			vPWR_COOLING__Solennoid_TurnAllOff();
			break;
		case SET_VALVE:
			// TODO find/write function to set the state of a valve
			break;
	}
}

/**
	Nominal commands used by the system
*/
void vFCU_COOLING__Enable(void)
{
	vPWR_COOLING__Enable(1U);
}

void vFCU_COOLING__Disable(void)
{
	vPWR_COOLING__Enable(0U);	
}

/**
	Manual commands used for debugging
*/
void vFCU_COOLING__Valve_Enable(Luint32 u32SolennoidNumber)
{
	// TODO find out what channel and pin numbers to use
	// Possible pin numbers:
	// 8U
	// 16U
	// 22U
	// 23U
	vPWR_COOLING__Solennoid_TurnOn(N2HET_CHANNEL__1, u32SolennoidNumber);
}

void vFCU_COOLING__Valve_Disable(Luint32 u32SolennoidNumber)
{
	// TODO find out what channel and pin numbers to use
	// Possible pin numbers:
	// 8U
	// 16U
	// 22U
	// 23U
	vPWR_COOLING__Solennoid_TurnOff(N2HET_CHANNEL__1, u32SolennoidNumber);
}



#endif //C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL
	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

