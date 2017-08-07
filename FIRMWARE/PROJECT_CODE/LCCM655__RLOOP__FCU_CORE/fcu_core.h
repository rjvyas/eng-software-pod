/**
 * @file		FCU_CORE.H
 * @brief		Main header for the FCU
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.001
 */

#ifndef _FCU_CORE_H_
#define _FCU_CORE_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__types.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__defines.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__enums.h>

		#include <LCCM655__RLOOP__FCU_CORE/FAULTS/fcu__faults__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/BRAKES/fcu__brakes__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/ACCELEROMETERS/fcu__accel__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/LASER_OPTO/fcu__laser_opto__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/THROTTLES/fcu__throttles__fault_flags.h>
		#include <LCCM655__RLOOP__FCU_CORE/LASER_DISTANCE/fcu__laser_distance__fault_flags.h>

		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi_defines.h>
		#include <LCCM655__RLOOP__FCU_CORE/ASI_RS485/fcu__asi_types.h>

		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>
		#include <MULTICORE/LCCM418__MULTICORE__MMA8451/mma8451__types.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define C_MLP__MAX_AVERAGE_SIZE				(8U)

		/*******************************************************************************
		Structures
		*******************************************************************************/
		/** main flight control structure */
		struct _strFCU
		{
			/** Structure guard 1*/
			Luint32 u32Guard1;

			struct
			{
				E_FCU__COOLING_GS_COMM_T eGSCoolingCommand;

			}sCoolingControl;

            #if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U
			/** Navigation */
			struct
			{
				Lfloat32 f32LongitudinalPosition;
				Lfloat32 f32PositionValidity;
				Lfloat32 f32LongitudinalSpeed;
				Lfloat32 f32LongitudinalSpeedUncertainty;
				Luint8 u8LongitudinalSpeedValidity;
				Lfloat32 f32LongitudinalAcceleration;
				Luint8 u8LongitudinalAccelerationValidity;
				Luint8 u8LRFAvailable;
				Luint8 u8masterSensor;
				Luint8 u8GeneralStripeCount;
				Luint32 u3210MSNavTimer;
				Luint32 u3210MSLRFTimer;
				Luint32 u3210MSAccelHiValTimer;
				Luint32 u3210MSAccelLoValTimer;
				Luint32 u3210MSDetectStripeTimer;
				Luint32 u3210MSBetweenStripeTimer;

					struct
					{
						Luint32 u32StripeCount;
						Luint32 u32Xpos;
						Luint32 u32XPosUncert;
						Luint32 u32NoseToSensorDist;
						Luint32 u32Score;
						Luint8 u8Valid;
					}sCS[C_FCU__NAV_NUM_CONTRAST_SENSORS];

					struct
					{
						Lfloat32 f32Accel;
						Luint8 u8Valid;
					}sAccel[C_LOCALDEF__LCCM418__NUM_DEVICES];

			}sNavigation;
            #endif

			/** Hover Engines Control Structure */
			//#if C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL == 1U
			struct
			{
				/** The hover engines state machine */
				E_FCU__HOVERENGINES_STATES_T eState;

				/** The hover engines input commands from GS */
				Luint32 eGSCommands;

				/** The hover engines command values from GS */
				Luint32 u32CommandValues;


				/** Internal parameters */
				struct
				{
					Luint8  u8Enable;
					Luint8  u8RunAuto;
					Luint8  u8SpeedState;
					Luint32 u32CurrentRPMValue[8];
					Luint8  u8TempVar;

				}sIntParams;

			}sHoverEngines;
			//#endif

			/** State Machine Structure **/
			struct
			{
				/** The mission phases
				 * http://confluence.rloop.org/display/SD/1.+Determine+Mission+Phases+and+Operating+States
				 * */
				E_FCU__MISSION_PHASE_T eMissionPhase;

				/** Counter to count the time elapsed from the disconnection from the pusher **/
				Luint32 PusherCounter;

				/** Enable Counter counting time elapsed from the disconnection from the pusher **/
				Luint8 EnablePusherCounter;

				/**Counter to count the time the pod experiences acceleration higher than value speccd in the db */
				Luint32 AccelCounter;

				/**Enable the Accel Counter */
				Luint8 EnableAccelCounter;

				/** In case Pusher fails and doesn't get us to the min pushed distance */
				Luint32 MiserableStopCounter;

				/** Enable Miserable Stop Counter */
				Luint8 EnableMiserableStopCounter;

				/** Enum for Pod Status for SpaceX telemetry */
				E_FCU__POD_STATUS ePodStatus;

				/** Enum for GS commands */
				E_FCU__MAINSM_GS_COMM eGSCommands;

				/** Operating States Structure*/
				struct
				{
					/** Lifted State */
					Luint8 u8Lifted;

					/** Unlifted State */
					Luint8 u8Unlifted;

					/** Static Hovering */
					Luint8 u8StaticHovering;

					/** Gimballing Adjustment State */
					Luint8 u8GimbAdj;

					/** Ready For Push State */
					Luint8 u8ReadyForPush;

					/** Pushing State */
					Luint8 u8Pushing;

					/** Coast State */
					Luint8 u8Coasting;

					/** Braking State */
					Luint8 u8Braking;

					/** Controlled Emergency State */
					Luint8 u8CtlEmergBraking;

				}sOpStates;

			}sStateMachine;


			/** Auto sequence state machine */
			E_FCU__AUTO_SEQUENCE_STATE_T eAutoSeqState;

			/** The init statemachine */
			E_FCU__INIT_STATE_TYPES eInitStates;


			/** Fault handling subsystem */
			struct
			{
				/** top level fault tree subsystem for the flight controller */
				FAULT_TREE__PUBLIC_T sTopLevel;

			}sFaults;

			#if C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL == 1U
			struct
			{
				/** Main state machine*/
				E_FCU__DRIVEPOD_PRERUN_STATE ePreRunState;

				E_FCU__DRIVEPOD_GS_COMM eGSCommand;

				Luint8 u8100MS_Timer;

			}sDrivePod;
			#endif

			struct
			{
				struct
				{

					E_FCU__FCTL_EDDYBRAKES_DIRECTION eEddyBrakesDir;

					E_FCU__FCTL_EDDYBRAKES_ACTUATOR	eEddyBrakesAct;
				}sEddyBrakes;
			}sFctl;



			#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U

			/** Global brakes system */
			struct
			{
				/** individual brake fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The brakes state machine */
				E_FCU_BRAKES__STATES_T eBrakeStates;


				/** Brake Development mode */
				struct
				{

					/** Are we in develompent mode? */
					Luint8 u8DevMode;

					/** Key to enable develompent mode checks */
					Luint32 u32DevKey;

				}sBrakesDev;

				/** just a global movement planner ID */
				Luint32 u32MoveTaskID;

				/** Claibration Systems */
				struct
				{
					//Cal State
					E_FCU_CAL_BRAKES__STATES_T eState;

				}sCalibration;

				/** 100ms tick */
				Luint8 u8Timer_100ms;

			}sBrakesGlobal;


			/** Brake(S) Substructure */
			struct
			{

				/** Limit switch structure
				 * There are two limit switches per brake assy
				 */
				struct
				{

					/** An edge was captured on the interrupt subsystem
					 * Its up to some other layer to clear the flag once its used.
					 */
					Luint8 u8EdgeSeen;

					#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
						/** Debugs how many interrupts have been received
						 */
						Luint32 u8EdgeSeenCnt;
					#endif

					/** The program index for N2HET, even if not used on both channels */
					Luint16 u16N2HET_Prog;

					/** The current state of the switch */
					E_FCU__SWITCH_STATE_T eSwitchState;

					#ifdef WIN32
						/** Allow us to inject swiches on WIN32 */
						Luint8 u8InjectedValue;
					#endif

				}sLimits[BRAKE_SW__MAX_SWITCHES];

				/** Linear position sensor detail */
				struct
				{
					/** This is the sample from the ADC converter */
					Luint16 u16ADC_Sample;

					/** This is the filtered result from the raw sample */
					Luint16 u16ADC_FilteredSample;

					/** The zero value when the brakes are fully retracted */
					Luint16 u16ADC_Zero;

					/** Current ADC span to convert ADC units into engineering units */
					Lfloat32 f32SystemSpan;

					/** ADC value - Zero Value */
					Lint32 s32ADC_Minus_Zero;

					/** Brake linear pos feedback*/
					Lfloat32 f32BrakePosition_mm;

					/** Average Counter	for MLP filter function */
					Luint16 u16AverageCounter;

					/** Average Array for MLP filter function */
					Luint16 u16AverageArray[C_MLP__MAX_AVERAGE_SIZE];

					/** Lowest MLP Value*/
					Luint16 lowest_value;

					/** Highest MLP Value */
					Luint16 highest_value;

					#if C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES == 1U
						/** Debug how many times we get a zero */
						Luint32 zero_count;
					#endif


					#ifdef WIN32
					struct
					{
						/** The ADC sample for WIN32 emulation */
						Luint16 u16ADC_Sample;

					}sWin32;
					#endif

					/** Temporary use; identify when startup sequence has ended and mlp won't return 0. */
					Luint8 u8Running;
				}sMLP;


				/** Movement Planner */
				struct
				{

					/** The required linear veloc for the move */
					Lint32 s32LinearVeloc;

					/** The required linear accel for the move */
					Lint32 s32LinearAccel;

					/** The position that we have requested the brake to move to */
					Lint32 s32MoveToPos;

					/** The current position of the lead screw */
					Lint32 s32currentPos;

				}sMove;


				/** Current Details */
				struct
				{

					/** the screw position in mm */
					Lfloat32 f32ScrewPos_mm;

					/** I-Beam distance in mm */
					Lfloat32 f32IBeam_mm;

					/** I-Beam distance in mm */
					Lfloat32 f32MLP_mm;


				}sCurrent;


				/** The target move position */
				struct
				{
					/** The current targeted IBeam brake distance */
					Lfloat32 f32IBeam_mm;

					/** target lead screw position */
					Lfloat32 f32LeadScrew_mm;

					/** Microns for the planner */
					Luint32 u32LeadScrew_um;

				}sTarget;

				Luint8 u8BrakeSWErr;

			}sBrakes[C_FCU__NUM_BRAKES];
			#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES

			#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
			/** Accel subsystem */
			struct
			{
				/** Accel subsystem faults */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** individual accel channels */
				struct
				{
					/** most recent recorded sample from the Accel in raw units */
					Lint16 s16LastSample[MMA8451_AXIS__MAX];

					/** do some filtering on our target axis */
					Luint16 u16FilterCounter;
					Lint16 s16FilterValues[C_FCU__ACCEL_FILTER_WINDOW];
					Lint16 s16FilteredResult;

					#if C_LOCALDEF__LCCM418__ENABLE_G_FORCE == 1U
						/** Last sample of the G-Force*/
						Lfloat32 f32LastG[MMA8451_AXIS__MAX];
					#endif

					/** The current acceleration in mm/sec^2 based on the last sample */
					Lint32 s32CurrentAccel_mmss;

					/** The computed current velocity in mm/sec*/
					Lint32 s32CurrentVeloc_mms;

					/** The previous veloc has just been calculated in the last time period */
					Lint32 s32PrevVeloc_mms;

					/** Current displacement */
					Luint32 s32CurrentDisplacement_mm;

					/** Previous displacement */
					Luint32 s32PrevDisplacement_mm;



				}sChannels[C_LOCALDEF__LCCM418__NUM_DEVICES];

			}sAccel;
			#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL

			
			#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
			/** Pusher Interface Layer */
			struct
			{
				/** Guard variable 1*/
				Luint32 u32Guard1;

				/** Pusher Fault Flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The pusher subsystem state machine */
				E_FCU_PUSHER__STATES_T eState;

				/** Interlock switch status */
				E_FCU_PUSHPIN_STATE_T ePusher_Status;



				/** Timer of 10ms ticks used for switch state timing */
				Luint32 u32SwtichTimer;

				/** Switch interfaces */
				struct
				{
					/** N2HET Program index for edge interrupts*/
					Luint16 u16N2HET_Prog;

					/** The state of the switch based on the last sample */
					Luint8 u8SwitchState;

					/** Edge interrupt has occurred, meaning there has been a switch transition */
					Luint8 u8EdgeFlag;

				}sSwitches[2];

				/** Guard variable 2*/
				Luint32 u32Guard2;

			}sPusher;
			#endif //C_LOCALDEF__LCCM655__ENABLE_PUSHER


			#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
			/** Overall structure for the OPTONCDT laser interfaces */
			struct
			{
				/** Global laser fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** state machine for processing the OptoNCDT systems */
				E_FCU_OPTOLASER__STATE_T eOptoNCDTState;

				/** A 100ms counter to wait until the lasers have powered up*/
				Luint32 u32LaserPOR_Counter;

				/** The opto NCDT laser interfaces */
				struct
				{
					/** Individual laser fault flags */
					FAULT_TREE__PUBLIC_T sFaultFlags;

					/** RX byte state machine */
					E_OPTONCDT__RX_STATE_T eRxState;

					/** A new packet is available for distance processing */
					Luint8 u8NewPacket;

					/** A new packet is available and ready to be filtered */
					Luint8 u8ReadyForFiltering;

					/** Array to hold new bytes received */
					Luint8 u8NewByteArray[3U];

					/** The most recent distance*/
					Lfloat32 f32DistanceRAW;

					/** New distance has been measured, other layer to clear it */
					Luint8 u8NewDistanceAvail;

					/** is f32Distance equal to error value? */
					Luint8 u8Error;


					/** Diagnostic Counters */
					struct
					{

						/** We have received an error code from the laser */
						Luint32 u32ErrorCode;

						/** First packet byte was not in the correct place */
						Luint32 u32Byte1Wrong;

						/** Successful packet count */
						Luint32 u32Success;

					}sCounters;

					/** Filtered data structure */
					struct
					{

						/** The filtered height */
						Lfloat32 f32FilteredValue;

						/** The previous value */
						Lfloat32 f32PreviousValue;

					}sFiltered;

				}sOptoLaser[C_FCU__NUM_LASERS_OPTONCDT];

				/** Calibration storage offset */
				struct
				{
					/** The offset value */
					Lfloat32 f32Offset;

				}sCalibration[C_FCU__NUM_LASERS_OPTONCDT];

			}sLaserOpto;
			#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT

			/** structure for the laser distance interface */
			struct
			{

				/** Individual laser fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** main state machine */
				E_FCU_LASERDIST__STATE_T eLaserState;

				/** RX byte state machine */
				E_LASERDIST__RX_STATE_T eRxState;

				/** A 100ms counter to wait until the lasers have powered up*/
				Luint32 u32LaserPOR_Counter;

				/** Number of 100ms increments the new bytes have been seen */
				Luint32 u32BytesSeen_Counter;

				/** Number of 100ms increments the new packets have been seen */
				Luint32 u32PacketsSeen_Counter;


				/** A new packet is available for distance processing */
				Luint8 u8NewPacket;

				/** Array to hold new bytes received */
				Luint8 u8NewByteArray[5];

				/** The most recent distance in mm*/
				Lint32 s32Distance_mm;

				/** Previous distance of last sample */
				Lint32 s32PrevDistance_mm;

				Lint32 s32Velocity_mms;
				Lint32 s32PrevVelocity_mms;

				Lint32 s32Accel_mmss;
				Lint32 s32PrevAccel_mmss;

				/** The final filtered distance*/
				//Lfloat32 f32DistanceFiltered;

				/** New distance has been measured, other layer to clear it */
				Luint8 u8NewDistanceAvail;

				/** For emulation over UDP */
				struct
				{

					/** Is the EMU enabled ?*/
					Luint8 u8EmulationEnabled;

					/** Special Key = 0x98984343 to prevent above flag being 1 */
					Luint32 u32EmuKey;

					/** Emulated Distance */
					Lint32 s32Distance;

				}sEmu;



				/** binary mode data */
				struct
				{

					/** Hold the Rx data in binary millimeter mode */
					union
					{

						Luint8 u8[4];
						Luint32 u32;

					}unRx;

					/** Count of missed start packets */
					Luint32 u32Counter__MissedStart;

					/** Bad distance measurement */
					Luint32 u32Counter__BadDistance;

					/** Error code value counter */
					Luint32 u32Counter__ErrorCode;

				}sBinary;

			}sLaserDist;


			/** Flight Controller */
			struct
			{
				#if C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION == 1U
				/** Orientation structure */

				/** Main orientation parameter structure */
				struct
				{
					Lint16 s16Roll;
					Lint16 s16Pitch;
					Lint16 s16Yaw;
					Lfloat32 f32Lateral;
					Lint16 s16TwistPitch; // TODO s8?
					Lint16 s16TwistRoll; // TODO s8?

					//Basically the vehicle is a static reference and we recalculate the orientation
					//of the ground plane relative to the vehicle and the hover engines
					Lfloat32 f32PlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms
					Lfloat32 f32TwistPlaneCoeffs[4]; //TODO: Check this size   // ordered as: A, B, C, D, decreasing polynomial terms // to be built with vCalculateGroundPlane() using the second laser triplet

					/** sub-structure for ground lasers and their measurements*/
					struct
					{
						Lfloat32 f32Position[3]; // x,y,z
						Lfloat32 f32Measurement; // measurement returned from the distance laser
						Luint8 u8Error; //Error value as read from fcu__laser_opto.c 
					}sGroundLasers[C_FCU__NUM_LASERS_GROUND];

					/** sub-structure for beam lasers and their measurements*/
					struct
					{
						Lfloat32 f32Position[3]; // x,y,z
						Lfloat32 f32Measurement; // measurement returned from the distance laser
						Luint8 u8Error; //Error value as read from fcu__laser_opto.c 
					}sBeamLasers[C_FCU__NUM_LASERS_IBEAM];

					/** sub-structure for hover engine positions and their hover heights*/
					struct
					{
						Lfloat32 f32Position[3]; // x,y,z
						Lfloat32 f32Measurement; // height of hover engine above ground
					}sHoverEngines[C_FCU__NUM_HOVER_ENGINES];

					E_LASER_ORIENTATION__STATE_T eState;

				}sOrient;
				
				#else
					//Needed for compatibiltiy
					Luint8 u8Dummy;
				#endif


				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
				/** Track database structure */
				struct
				{
					/** Track DB fault flags system */
					FAULT_TREE__PUBLIC_T sFaultFlags;

					/** The current selected track DB, defaults to 0 and user
					 * must set from GS
					 */
					Luint32 u32CurrentDB;

				}sTrackDB;
				#endif //#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U

				#if C_LOCALDEF__LCCM655__ENABLE_GEOM == 1U
				/** Geometry */
				struct
				{
					/** F32 Geom Items */
					struct tsNUM_f32Vector_3D vf32Geom[C_FCU__GEOM__NUM_ITEMS_F32];

					/** S32 Geom Items */
					struct tsNUM_s32Vector_3D vs32Geom[C_FCU__GEOM__NUM_ITEMS_S32];

				}sGeom;
				#endif //C_LOCALDEF__LCCM655__ENABLE_GEOM

				/** Accel, Veloc and Displacement blender system */
				struct
				{

					/** The current working values we are using for flight */
					struct
					{
						Lint32 s32Accel_mmss;
						Lint32 s32Veloc_mms;
						Lint32 s32Disp_mm;

					}sWorking;

				}sBlender;


			}sFlightControl;


			#if C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH == 1U
			struct
			{

				/** The flags indicating pod health */
				FAULT_TREE__PUBLIC_T sHealthFlags;

			}sPodHealth;
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U
			/** Contrast sensor structure */
			struct
			{

				/** Upper guard */
				Luint32 u32Guard1;

				/** Top level fault system */
				FAULT_TREE__PUBLIC_T sFaultFlags;


				/** The final computed values taking into account fault tolerance and
				 * laser processing techiques */
				struct
				{

					/** The current velocity in mm/sec */
					Luint32 u32CurrentVeloc_mms;

				}sComputed;

				/** Individual contrast senors */
				struct
				{

					/** The N2HET program index */
					Luint16 u16N2HET_Index;

					/** Individual fault flags */
					FAULT_TREE__PUBLIC_T sFaultFlags;

					/** Top level distance remaining in the run in mm */
					Luint32 u32DistElapsed_mm;

					/** Distance elapsed between last stripe */
					Luint32 u32DistLastStripe_mm;

					/** Current velocity in mm/sec */
					Luint32 u32CurrentVeloc_mms;

					/** Current velocity in mm/sec */
					Luint32 u32PreviousVeloc_mms;

					/** Current acceleration */
					Lint32 s32CurrentAccel_mmss;

				}sSensors[LASER_CONT__MAX];


				Luint32 u32Guard2;

				/** a timing based list to store the rising and falling edges of each laser */
				struct
				{

					/** Rising edge time stamp */
					Luint64 u64RisingList[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** Falling edge time stamp */
					Luint64 u64FallingList[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** list of time that has elapsed between sensor marks */
					Luint64 u64ElapsedList_Rising[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** Rising edge count */
					Luint16 u16RisingCount;

					/** Can maintan a list of prev processed counts */
					Luint16 u16PrevRisingCount;

					/** Falling edge count */
					Luint16 u16FallingCount;

					/** signalled by the rising edge that a new item is avail */
					Luint8 u8NewRisingAvail;

				}sTimingList[LASER_CONT__MAX];

				Luint32 u32Guard3;

				/** The track database for each sensor */
				struct
				{
					/** The distance elapsed in the tube */
					Luint32 u32DistanceElapsed_mm[C_FCU__LASER_CONTRAST__MAX_STRIPES];

					/** The current optical marker */
					Luint8 u8ElapsedCount;

					/** Distance Remaining - computed*/
					Luint32 u32DistElapsed;

					/** Last Increment */
					Luint32 u32LastIncrement;

				}sTrackDatabase[LASER_CONT__MAX];

				Luint32 u32Guard4;

			}sContrast;
			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
			/** Ethernet comms structure */
			struct
			{
				/** our hardware MAC */
				Luint8 u8MACAddx[6];

				/** our locally assigned IP*/
				Luint8 u8IPAddx[4];

			}sEthernet;


			/** UDP diagnostics system */
			struct
			{

				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u810MS_Flag;

				/** 250ms timer for our fault data */
				Luint8 u8250MS_Flag;

				/** The next packet type to transmit */
				E_NET__PACKET_T eTxPacketType;

				/** If the user has enabled Tx streaming */
				E_NET__PACKET_T eTxStreamingType;

				/** Timer for the Drive Pod comms watchdog */
				Luint32 u32_10MS_GS_COMM_Timer;

			}sUDPDiag;

			/** SpaceX required transmission */
			struct
			{
				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u8100MS_Flag;

				/** Test counter for telemetry */
				Luint32 u32TestCounter;

			}sSpaceX;

			#endif

			#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
			/** ASI Comms Layer */
			struct
			{
				Luint32 u32Guard1;

				/** the real time scan holding values */
				struct
				{
					/** fault flags */
					Luint16 u16Faults;

					/** Temp in deg C*/
					Lfloat32 f32TempC;

					/** Motor Current */
					Lfloat32 f32MotorCurrentA;

					/** Current RPM */
					Luint16 u16RPM;

				}sHolding[C_FCU__NUM_HOVER_ENGINES];

				/** The main state machine */
				E_FCU__ASI_STATE_T eMainState;

				/** When scanning our HE's, maintain the scan index */
				Luint8 u8ScanIndex;

				/** 10ms timer used for scanning */
				Luint8 u810MS_Timer;

				/** ASI Subsystemfaults */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** the modbus state */
				E_FCU_MODBUS__STATE_T eModBusState;

				struct _strASICmd sCurrentCommand;

				/** The Rx Counter Position */
				Luint8 u8RxCount;

				/** The user has prepared a new command to send*/
				Luint8 u8NewCommandToSend;

				/** a set of timers to control tx timeouts */
				Luint32 u32ASI_turnaround_Counter;
				Luint32 u32ASI_replywait_Counter;

				#ifdef WIN32
					/** On win32 generate save the mux */
					Luint8 u8MuxChannel;
				#endif

				/** List of commands to send in round robbin*/
				E_FCU_ASI_BAC_OBJECT_TYPES__T eCommandList[C_FCU__ASI_COMMAND_LIST_MAX];

				/** Keep track of the command */
				Luint8 u8CommandListIndex;

				/** Do we need to issue a throttle command? */
				Luint8 u8ThrottleCommand[C_FCU__NUM_HOVER_ENGINES];

				/** Command issued to change ASI's into serial throttle mode */
				Luint8 u8SerialNetworkCommand[C_FCU__NUM_HOVER_ENGINES];

				/** The throttle value to change to */
				Luint16 u16Throttle[C_FCU__NUM_HOVER_ENGINES];


				/** The lower guard */
				Luint32 u32Guard2;

			}sASI;
			#endif

			/** Input data for throttle layer */
			#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
			struct strThrottleInterfaceData
			{

				/* State Variable*/
				E_THROTTLE_STATES_T eState;

				/** Throttle fault flags */
				FAULT_TREE__PUBLIC_T sFaultFlags;

				/** The requested RPM of each HE */
				Luint16 u16RequestedRPM[C_FCU__NUM_HOVER_ENGINES];

				/** The requested ramp or step mode */
				E_THROTTLE_CTRL_T eRequestedMode[C_FCU__NUM_HOVER_ENGINES];

				/** The current (actually set RPM) */
				Luint16 u16CurrentRPM[C_FCU__NUM_HOVER_ENGINES];

				/** A 100ms timer for each ramp increment */
				Luint8 u8100ms_Timer[C_FCU__NUM_HOVER_ENGINES];

				/** During run keep an index of the last servied HE */
				Luint8 u8RunIndex;

				/** For development mode */
				struct
				{

					/** Dev mode enabled */
					Luint8 u8Enabled;

					/** Dev mode security key, 0x77558833U */
					Luint32 u32SecurityKey;

				}sDevMode;

			} sThrottle;
			#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLE


			
			/** Critical info from the BMS */
			struct
			{
				/** Highest cell temp */
				Lfloat32 f32HighestTemp;

				/** Average Temp cell (battery temp) */
				Lfloat32 f32AverageTemp;

				/** Total pack voltage */
				Lfloat32 f32PackVoltage;

				/** Highest cell voltage */
				Lfloat32 f32HighestCellVoltage;

				/** Lowest cell voltage */
				Lfloat32 f32LowestCellVoltage;

				/** PV Temp */
				Lfloat32 f32PV_Temp;

				/** PV Press */
				Lfloat32 f32PV_Press;


			}sBMS[2];

			/** Structure guard 2*/
			Luint32 u32Guard2;


		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		//core
		DLL_DECLARATION void vFCU__Init(void);
		DLL_DECLARATION void vFCU__Process(void);
		DLL_DECLARATION void vFCU__RTI_100MS_ISR(void);
		DLL_DECLARATION void vFCU__RTI_10MS_ISR(void);


		//flight controller
		void vFCU_FCTL__Init(void);
		void vFCU_FCTL__Process(void);

			//main state machine
			void vFCU_FCTL_MAINSM__Init(void);
			void vFCU_FCTL_MAINSM__Process(void);
			void vFCU_FCTL_MAINSM__10MS_ISR(void);
			void vFCU_FCTL_MAINSM__100MS_ISR(void);
			void vFCU_FCTL_MAINSM__MISERABLE_STOP_100MS_ISR(void);

			//drive pod
			Luint32 u32FCU_NET_RX__GetGsCommTimer(void);

			//blender
			void vFCU_FCTL_BLENDER__Init(void);
			void vFCU_FCTL_BLENDER__Process(void);
			Lint32 s32FCU_FCTL_BLENDER__Get_Accel_mmss(void);
			Lint32 s32FCU_FCTL_BLENDER__Get_Veloc_mms(void);
			Lint32 s32FCU_FCTL_BLENDER__Get_Displacement_mm(void);
			void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Veloc_mms);
			void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Veloc_mms);
			void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Veloc_mms);
			void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Accel_mmss);
			void vFCU_FCTL_BLENDER__Accel_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Accel_mmss);
			void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Accel_mmss);
			void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Disp_mm);
			void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Disp_mm);
			void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Disp_mm);

			//track DB
			void vFCU_FCTL_TRACKDB__Init(void);
			void vFCU_FCTL_TRACKDB__Process(void);
			void vFCU_FCTL_TRACKDB__Set_CurrentDB(Luint32 u32Key, Luint32 u32TrackID);


				//get functions
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_CurrentDB(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_TrackID(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_TrackStartPosX_mm(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_Current_TrackEndPosX_mm(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_LRF_StartPosX_mm(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_NumStripes(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_StripeStartPosX_mm(Luint32 u32StripeIndex);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_EnableLRF(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_EnableAccels(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_EnableContrast(void);
				DLL_DECLARATION Luint32 u32FCU_FCTL_TRACKDB__Get_GetFooter(void);

				//mem
				void vFCU_FCTL_TRACKDB_MEM__Init(void);
				void vFCU_FCTL_TRACKDB_MEM__Process(void);
				void vFCU_FCTL_TRACKDB_MEM__UploadChunk(Luint32 u32TrackID, Luint32 u32ChunkIndex, Luint32 u32Length, Luint8 *pu8Buffer);

				//win32
				void vFCU_FCTL_TRACKDB_WIN32__Init(void);
				void vFCU_FCTL_TRACKDB_WIN32__Process(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Clear_Array(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Get_Array(Luint8 *pu8ByteArray);
				DLL_DECLARATION Luint16 u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Array(Luint8 *pu8ByteArray);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Header(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(Luint32 u32Index, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_EnableAccels(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_EnableLRF(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_EnableContrast(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(Luint32 u32Index, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Footer(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(Luint32 u32Index, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(Luint32 u32Index, Luint32 u32Value);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(Luint32 u32Index, Luint32 u32Value);
				DLL_DECLARATION Luint16 u16FCTL_TRAKDB_WIN32__ComputeCRC(void);
				DLL_DECLARATION void vFCU_FCTL_TRACKDB_WIN32__Set_CRC(Luint16 u16Value);


			//auto sequence
			void vFCU_MAINSM_AUTO__Init(void);
			void vFCU_MAINSM_AUTO__Process(void);
			Luint8 u8FCU_MAINSM_AUTO__Is_Busy(void);
			Luint8 u8FCU_MAINSM_AUTO__Is_Abort(void);

			//ethernet
			void vFCU_FCTL_ETH__Init(void);
			void vFCU_FCTL_ETH__Transmit(E_NET__PACKET_T ePacketType);

			//pod health
			void vFCU_PODHEALTH__Init(void);
			void vFCU_PODHEALTH__Process(void);

			// Laser Orientation
			void vFCU_FLIGHTCTL_LASERORIENT__Init(void);
			void vFCU_FLIGHTCTL_LASERORIENT__Process(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Roll(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Pitch(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_Yaw(void);
			Lfloat32 f32FCU_FLIGHTCTL_LASERORIENT__Get_Lateral(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_TwistRoll(void);
			Lint16 s16FCU_FLIGHTCTL_LASERORIENT__Get_TwistPitch(void);

			//contrast sensor nav
			void vFCU_FLIGHTCTL_CONTRASTNAV__Init(void);
			void vFCU_FLIGHTCTL_CONTRASTNAV__Process(void);
			Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_Position_mm(void);
			Luint8 u8FCU_FLIGHTCTL_CONTRASTNAV__Get_IsFault(void);
			Luint32 u32FCU_FLIGHTCTL_CONTRASTNAV__Get_FaultFlags(void);

			//brake profiler
			Lint16 s16FCU_FLIGHTCTL_BRAKES__Brake_Lookup(Luint32 u32Veloc_mms, Luint32 u32DragForce_n, Luint32 *pu32IBDistance_um);




		//network
		void vFCU_NET__Init(void);
		void vFCU_NET__Process(void);
		void vFCU_NET_RX__Init(void);
		Luint8 u8FCU_NET__Is_LinkUp(void);
		void vFCU_NET_RX__RxUDP(Luint8 * pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vFCU_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);

			//transmit
			void vFCU_NET_TX__Init(void);
			void vFCU_NET_TX__Process(void);
			void vFCU_NET_TX__10MS_ISR(void);
			void vFCU_NET_TX__100MS_ISR(void);

			//spaceX specific
			void vFCU_NET_SPACEX_TX__Init(void);
			void vFCU_NET_SPACEX_TX__Process(void);
			void vFCU_NET_SPACEX_TX__100MS_ISR(void);

		//fault handling layer
		void vFCU_FAULTS__Init(void);
		void vFCU_FAULTS__Process(void);
		Luint8 u8FCU_FAULTS__Get_IsFault(void);
		Luint32 u32FCU_FAULTS__Get_FaultFlags(void);

			//ethernet
			void vFCU_FAULTS_ETH__Init(void);
			void vFCU_FAULTS_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//laser contrast sensors
		void vFCU_LASERCONT__Init(void);
		void vFCU_LASERCONT__Process(void);
		void vFCU_LASERCONT__Reset(Luint32 u32Key);
		void vFCU_LASERCONT__ISR(E_FCU__LASER_CONT_INDEX_T eLaser, Luint32 u32Register);

			//timing list
			void vFCU_LASERCONT_TL__Init(void);
			void vFCU_LASERCONT_TL__Process(void);
			DLL_DECLARATION void vFCU_LASERCONT_TL__ISR(E_FCU__LASER_CONT_INDEX_T eLaser, Luint32 u32Register);
			Luint8 u8FCU_LASERCONT_TL__Get_NewRisingAvail(E_FCU__LASER_CONT_INDEX_T eLaser);
			void vFCU_LASERCONT_TL__Clear_NewRisingAvail(E_FCU__LASER_CONT_INDEX_T eLaser);
			Luint64 u64FCU_LASERCONT_TL__Get_TimeDelta(E_FCU__LASER_CONT_INDEX_T eLaser, Luint16 u16CurrentIndex);

			//velocity
			void vFCU_LASERCONT_VELOC__Init(void);
			void vFCU_LASERCONT_VELOC__Process(void);
			Luint32 u32FCU_LASERCONT_VELOC__Get_CurrentVeloc_mms(void);
			Luint32 u32FCU_LASERCONT_VELOC__Compute(Luint32 u32Distance, Luint64 u64TimeDelta);

			//track database
			void vFCU_LASERCONT_TRKDB__Init(void);
			void vFCU_LASERCONT_TRKDB__Process(void);
			void vFCU_LASERCONT_TRKDB__Inc_Marker(E_FCU__LASER_CONT_INDEX_T eLaser);
			void vFCU_LASERCONT_TRKDB__Compute(E_FCU__LASER_CONT_INDEX_T eLaser);
			Luint32 u32FCU_LASERCONT_TRKDB__Get_DistanceElapsed_mm(E_FCU__LASER_CONT_INDEX_T eLaser);
			Luint32 u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm(E_FCU__LASER_CONT_INDEX_T eLaser);

			//ethernet
			void vFCU_LASERCONT_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//Laser distance
		void vFCU_LASERDIST__Init(void);
		void vFCU_LASERDIST__Process(void);
		Lint32 s32FCU_LASERDIST__Get_Distance_mm(void);
		Lint32 s32FCU_LASERDIST__Get_Velocity_mms(void);
		void vFCU_LASERDIST__100MS_ISR(void);

		DLL_DECLARATION void vFCU_LASERDIST_WIN32__Set_DistanceRaw(Lint32 s32Value);

			//eth
			void vFCU_LASERDIST_ETH__Init(void);
			void vFCU_LASERDIST_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_LASERDIST_ETH__Enable_EmulationMode(Luint32 u32Key, Luint32 u32Enable);
			void vFCU_LASERDIST_ETH__Emulation_Injection(Lint32 s32Value);

			//filtering
			void vFCU_LASERDIST_FILT__Init(void);
			void vFCU_LASERDIST_FILT__Process(void);




		//lasers for OptoNCDT interface
		void vFCU_LASEROPTO__Init(void);
		void vFCU_LASEROPTO__Process(void);
		void vFCU_LASEROPTO__Set_CalValue(Luint32 u32Key, Lfloat32 f32Offset);
		Lfloat32 f32FCU_LASEROPTO__Get_Distance(E_FCU__LASER_OPTO__INDEX_T eLaser);
		Luint8 u8FCU_LASEROPTO__Get_Error(E_FCU__LASER_OPTO__INDEX_T eLaser);
		void vFCU_LASEROPTO__100MS_ISR(void);
		DLL_DECLARATION void vFCU_LASEROPTO_WIN32__Set_DistanceRaw(Luint32 u32Index, Lfloat32 f32Value);

			//eth
			void vFCU_LASEROPTO_ETH__Transmit(E_NET__PACKET_T ePacketType);

			//filtering
			void vFCU_LASEROPTO_FILT__FilterPacket(E_FCU__LASER_OPTO__INDEX_T eLaser);


		
		//brakes
		void vFCU_BRAKES__Init(void);
		void vFCU_BRAKES__Process(void);
		void vFCU_BRAKES__Begin_Init(Luint32 u32Key);
		void vFCU_BRAKES__Move_IBeam_Distance_mm(Lfloat32 f32Distance);
		void vFCU_BRAKES__100MS_ISR(void);
		void vFCU_BRAKES__10MS_ISR(void);
		Lfloat32 f32FCU_BRAKES__Get_ScrewPos(E_FCU__BRAKE_INDEX_T eBrake);
		E_FCU__SWITCH_STATE_T eFCU_BRAKES__Get_SwtichState(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch);
		Luint16 u16FCU_BRAKES__Get_ADC_Raw(E_FCU__BRAKE_INDEX_T eBrake);
		Lfloat32 f32FCU_BRAKES__Get_IBeam_mm(E_FCU__BRAKE_INDEX_T eBrake);
		Lfloat32 f32FCU_BRAKES__Get_MLP_mm(E_FCU__BRAKE_INDEX_T eBrake);


			//stepper drive
			void vFCU_BRAKES_STEP__Init(void);
			void vFCU_BRAKES_STEP__Process(void);
			void vFCU_BRAKES_STEP__Move(Lint32 s32Brake0Pos, Lint32 s32Brake1Pos);
			Lint32 s32FCU_BRAKES__Get_CurrentPos(E_FCU__BRAKE_INDEX_T eBrake);
			void vFCU_BRAKES_STEP__UpdateValues(Luint32 u32Brake, Luint32 u32Type, Lint32 s32Value);

			//brake switches
			void vFCU_BRAKES_SW__Init(void);
			void vFCU_BRAKES_SW__Process(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Left_SwitchExtend_ISR(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Left_SwitchRetract_ISR(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Right_SwitchExtend_ISR(void);
			DLL_DECLARATION void vFCU_BRAKES_SW__Right_SwitchRetract_ISR(void);
			E_FCU__SWITCH_STATE_T eFCU_BRAKES_SW__Get_Switch(E_FCU__BRAKE_INDEX_T eBrake, E_FCU__BRAKE_LIMSW_INDEX_T eSwitch);
			Luint8 u8FCU_BRAKES_SW__Get_FaultFlag(E_FCU__BRAKE_INDEX_T eBrake);
			#ifdef WIN32
				DLL_DECLARATION void vFCU_BRAKES_SW_WIN32__Inject_SwitchState(Luint8 u8Brake, Luint8 u8ExtendRetract, Luint8 u8Value);
			#endif

			//brakes MLP sensor
			void vFCU_BRAKES_MLP__Init(void);
			void vFCU_BRAKES_MLP__Process(void);
			#ifdef WIN32
				DLL_DECLARATION void vFCU_BRAKES_MLP_WIN32__ForceADC(Luint8 u8Brake, Luint16 u16Value);
			#endif
			void vFCU_BRAKES_MLP__ComputeCalibration_Zero(Luint32 u32Key, E_FCU__BRAKE_INDEX_T eBrake);
			void vFCU_BRAKES_MLP__ComputeCalibration_Span(Luint32 u32Key, E_FCU__BRAKE_INDEX_T eBrake);

			//eth
			void vFCU_BRAKES_ETH__Init(void);
			void vFCU_BRAKES_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_BRAKES_ETH__MoveMotor_RAW(Luint32 u32Index, Lint32 s32Position);
			void vFCU_BRAKES_ETH__MoveMotor_IBeam(Lfloat32 f32Value);
			void vFCU_BRAKES_ETH__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1);
			void vFCU_BRAKES_ETH__MLP_ZeroSpan(Luint32 u32Key0, Luint32 u32Brake, Luint32 u32Function);

			//calibration
			void vFCU_BRAKES_CAL__Init(void);
			void vFCU_BRAKES_CAL__Process(void);
			void vFCU_BRAKES_CAL__BeginCal(Luint32 u32Key);
			Luint8 u8FCU_BRAKES_CAL__Is_Busy(void);

			//WDT
			void vFCU_BRAKES_WDT__Init(void);
			void vFCU_BRAKES_WDT__Pet_Start(void);
			void vFCU_BRAKES_WDT__Pet_End(void);

		//accelerometer layer
		void vFCU_ACCEL__Init(void);
		void vFCU_ACCEL__Process(void);
		Lint16 s16FCU_ACCEL__Get_LastSample(Luint8 u8Index, Luint8 u8Axis);
		Lfloat32 f32FCU_ACCEL__Get_LastG(Luint8 u8Index, Luint8 u8Axis);
		DLL_DECLARATION Lint32 s32FCU_ACCELL__Get_CurrentAccel_mmss(Luint8 u8Channel);
		DLL_DECLARATION Lint32 s32FCU_ACCELL__Get_CurrentVeloc_mms(Luint8 u8Channel);
		DLL_DECLARATION Lint32 s32FCU_ACCELL__Get_CurrentDisplacement_mm(Luint8 u8Channel);

			//eth
			void vFCU_ACCEL_ETH__Init(void);
			void vFCU_ACCEL_ETH__Transmit(E_NET__PACKET_T ePacketType);


		//Pusher interface
		void vFCU_PUSHER__Init(void);
		void vFCU_PUSHER__Process(void);
		void vFCU_PUSHER__InterlockA_ISR(void);
		void vFCU_PUSHER__InterlockB_ISR(void);
		Luint8 u8FCU_PUSHER__Get_InterlockA(void);
		Luint8 u8FCU_PUSHER__Get_InterlockB(void);
		void vFCU_PUSHER__10MS_ISR(void);
		Luint8 u8FCU_PUSHER__Get_Switch(Luint8 u8Switch);
		E_FCU_PUSHPIN_STATE_T eFCU_PUSHER__Get_PusherState(void);

			//eth
			void vFCU_PUSHER_ETH__Init(void);
			void vFCU_PUSHER_ETH__Transmit(E_NET__PACKET_T ePacketType);


		//ASI interface
		void vFCU_ASI__Init(void);
		void vFCU_ASI__10MS_ISR(void);
		void vFCU_ASI__Process(void);
		void vFCU_ASI__MemSet(Luint8 *pu8Buffer, Luint8 u8Value, Luint32 u32Count);
		void vFCU_ASI__Set_Throttle(Luint8 u8Index, Luint16 u16RPM);


			//CRC
			void vFCU_ASI_CRC__AddCRC(Luint8 *pu8Data);
			DLL_DECLARATION Luint16 u16FCU_ASI_CRC__ComputeCRC(Luint8 *pu8Data, Luint16 u16DataLen);
			Lint16 s16FCU_ASI_CRC__CheckCRC(Luint8 *pu8Data, Luint8 u8DataLen);

			//mux
			void vFCU_ASI_MUX__Init(void);
			void vFCU_ASI_MUX__Process(void);
			void vFCU_ASI_MUX__SelectChannel(Luint8 u8ChannelIndex);
			DLL_DECLARATION Luint8 u8FCU_ASI_MUX_WIN32__Get(void);

			//eth
			void vFCU_ASI_ETH__Init(void);
			void vFCU_ASI_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//throttle layer
		void vFCU_THROTTLE__Init(void);
		void vFCU_THROTTLE__Process(void);
		void vFCU_THROTTLE__100MS_ISR(void);
		void vFCU_THROTTLE__Enable_Run(void);
		void vFCU_THROTTLE__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, E_THROTTLE_CTRL_T eRampType);

			//eth
			void vFCU_THROTTLE_ETH__Init(void);
			void vFCU_THROTTLE_ETH__Transmit(E_NET__PACKET_T ePacketType);
			void vFCU_THROTTLE_ETH__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1);
			void vFCU_THROTTLE_ETH__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, E_THROTTLE_CTRL_T eRampType);

			//geometry
		void vFCU_GEOM__Init(void);
		void vFCU_GEOM__Process(void);

			//eth
			void vFCU_GEOM_ETH__Init(void);
			void vFCU_GEOM_ETH__Transmit(E_NET__PACKET_T ePacketType);

		//hover engines
		E_FCU__HOVERENGINES_STATES_T eFCU_FCTL_HOVERENGINES__Get_State(void);
		void vFCU_FCTL_HOVERENGINES__ManualCommandsHandle(void);
		void vFCU_FCTL_HOVERENGINES__Process(void);
		void vFCU_FCTL_HOVERENGINES__Start(void);
		void vFCU_FCTL_HOVERENGINES__Stop(void);

		//ASI
		Luint16 u16FCU_ASI__ReadMotorRpm(Luint8 u8EngineIndex);
		Lfloat32 f32FCU_ASI__ReadMotorCurrent(Luint8 u8EngineIndex);
		Lfloat32 f32FCU_ASI__ReadControllerTemperature(Luint8 u8EngineIndex);

		//drive pod
		void vFCU_FCTL_DRIVEPOD__10MS_ISR(void);
		void vFCU_FCTL_DRIVEPOD__SetPodStopCmd(void);

		//aux propulsion
		void vFCU_FCTL_AUX_PROP__Stop(void);
		void vFCU_FCTL_AUX_PROP__Disable(void);

		//flight controller cooling
		void vFCU_FCTL_COOLING__ManualCommandsHandle();
		void vFCU_FCTL_COOLING__Disable(void);
		void vFCU_FCTL_COOLING__Enable(void);

		//hover engine cooling
		void vFCU_COOLING__Set_Valve(Luint8 ValveNumber, Lfloat32 TimeOn, Lfloat32 TimeOff);

		//lift mechanism
		void vFCU_FCTL_LIFTMECH_Dir(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir);
		void vFCU_FCTL_LIFTMECH__SetDirAll(E_FCU__LIFTMECH_DIRECTION dir);
		void vFCU_FCTL_LIFTMECH__SetSpeedAll(Luint32 u32speed);
		void vFCU_FCTL_LIFTMECH__Extend(void);
		//void vFCU_FCTL_LIFTMECH_Speed(E_FCU__LIFTMECH_ACTUATOR actuator, E_FCU__LIFTMECH_DIRECTION dir);
		//void vFCU_FCTL_LIFTMECH__Get_State(void);

		//brakes
		void vFCU_FCTL_EDDYBRAKES_Speed(E_FCU__FCTL_EDDYBRAKES_ACTUATOR actuator, Luint32 u32speed);
		void vFCU_FCTL_EDDYBRAKES__SetSpeedAll(Luint32 u32speed);
		void vFCU_FCTL_EDDYBRAKES__SetDirAll(E_FCU__FCTL_EDDYBRAKES_DIRECTION dir);
		void vFCU_FCTL_EDDY_BRAKES__ControlledEmergencyBrake();
		void vFCU_FCTL_EDDY_BRAKES__ApplyFullBrakes(void);
		void vFCU_FCTL_EDDY_BRAKES__Release(void);
		void vFCU_FCTL_EDDY_BRAKES__GainScheduleController(Luint32 u32speed);
		void vFCU_FCTL_EDDY_BRAKES__GimbalSpeedController(void);

		//main state machine
		Luint8 u8FCU_FCTL_MAINSM__CheckIfUnlifted(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfLifted(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfHoveringStatically(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfReadyForPush(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfPushing(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfCoasting(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfBraking(void);
		Luint8 u8FCU_FCTL_MAINSM__CheckIfControlledBraking(void);
		void vFCU_FCTL_MAINSM__100MS_ISR(void);
		void vFCU_FCTL_MAINSM__EnterPreRun_Phase();

		//navigation
		Luint32 u32FCU_FCTL_NAV__PodSpeed(void);
		Luint8 u8FCU_FCTL_NAV__GetPodSpeedTooHigh(void);
		Luint32 u32FCU_FCTL_NAV__GetFrontPos(void);
		Luint32 u32FCU_FCTL_NAV__GetRearPos(void);
		Luint32 u32FCU_FCTL_NAV__Get_Accel_mmss(void);

		// Laser Orientation
		Luint32 u32FCU_FCTL_LASERORIENT__Get_Z_Pos();

		//brake pid
		void vFCU_FLIGHTCTL_BRAKEPID__Init(void);

		//cooling
		void vFCU_FCTL_COOLING__Enable(void);

		#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U

			//only for testing
			extern struct _strFCU sFCU;

			DLL_DECLARATION void vLCCM655R0_TS_000(void);
			DLL_DECLARATION void vLCCM655R0_TS_001(void);
			DLL_DECLARATION void vLCCM655R0_TS_002(void);
			DLL_DECLARATION void vLCCM655R0_TS_003(void);
			DLL_DECLARATION void vLCCM655R0_TS_004(void);
			DLL_DECLARATION void vLCCM655R0_TS_005(void);
			DLL_DECLARATION void vLCCM655R0_TS_006(void);


			#endif


	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_FCU_CORE_H_

