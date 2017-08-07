/**
 * @file		FCU_CORE__NET__RX.C
 * @brief		Network Rx portion
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__CORE_NET_RX
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		5B1DE8A3F401FB4A50E331F747199F27
 * @st_funcID		LCCM655R0.FILE.018.FUNC.003
 */
void vFCU_NET_RX__Init(void)
{
	Luint8 u8Counter;

	//init
	for(u8Counter = 0U; u8Counter < 2U; u8Counter++)
	{
		sFCU.sBMS[u8Counter].f32HighestTemp = 0.0F;
		sFCU.sBMS[u8Counter].f32AverageTemp = 0.0F;
		sFCU.sBMS[u8Counter].f32PackVoltage = 0.0F;
		sFCU.sBMS[u8Counter].f32HighestCellVoltage = 0.0F;
		sFCU.sBMS[u8Counter].f32LowestCellVoltage = 0.0F;
		sFCU.sBMS[u8Counter].f32PV_Temp = 0.0F;
		sFCU.sBMS[u8Counter].f32PV_Press = 0.0F;
	}

}

/***************************************************************************//**
 * @brief
 * Rx a normal UDP packet
 * 
 * @param[in]		u16DestPort				The dest port on the UDP frame
 * @param[in]		u16Length				Length of UDP payload
 * @param[in]		*pu8Buffer				Pointer to UDP payload
 * @st_funcMD5		DC1B8CA75C73EC734B09AF640F3012B7
 * @st_funcID		LCCM655R0.FILE.018.FUNC.001
 */
void vFCU_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//Todo
	//We can interpretate messages here,

	//pass to safety udp processor
	vSIL3_SAFEUDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}

/***************************************************************************//**
 * @brief
 * Rx a SafetyUDP
 * 
 * @param[in]		u16Fault				Any fault flags with the Tx.
 * @param[in]		u16DestPort				UDP Destination Port
 * @param[in]		ePacketType				SafeUDP packet Type
 * @param[in]		u16PayloadLength		Length of only the SafeUDP payload
 * @param[in]		*pu8Payload				Pointer to the payload bytes
 * @st_funcMD5		5AD676C1CB39DA8E23F769F70DAA8534
 * @st_funcID		LCCM655R0.FILE.018.FUNC.002
 */
void vFCU_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

	Luint32 u32Block[4];
	Lfloat32 f32Block[4];
	Lint32 s32Block[4];
	Luint8 u8Device;

	//make sure we are rx'ing on our port number
	if(u16DestPort == C_RLOOP_NET_PORT__FCU)
	{

		//blocks are good for putting into functions
		//this is inhernet in the safetyUDP layer
		u32Block[0] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		f32Block[0] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		f32Block[1] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		f32Block[2] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		f32Block[3] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		s32Block[0] = s32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		s32Block[1] = s32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		s32Block[2] = s32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		s32Block[3] = s32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);


		//determine the type of packet that came in
		switch((E_NET__PACKET_T)ePacketType)
		{

			case NET_PKT__FCU_GEN__GS_HEARTBEAT:
			#if C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL == 1U
				vFCU_FCTL_DRIVEPOD__10MS_ISR();
			#endif
			break;

//			case NET_PKT__FCU_LIFTMECH__SET_DIR:
//				//set direction of specific mech lift
//				#if C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL == 1U
//				E_FCU__LIFTMECH_ACTUATOR actuator;
//				E_FCU__LIFTMECH_DIRECTION dir;
//				switch(u32Block[0])
//				{
//					case 0:
//						actuator = LIFTMECH_AftLeft;
//						break;
//					case 1:
//						actuator = LIFTMECH_AftRight;
//						break;
//					case 2:
//						actuator = LIFTMECH_ForwardLeft;
//						break;
//					case 3:
//						actuator = LIFTMECH_ForwardRight;
//						break;
//					default:
//						//report error
//						break;
//				}
//				switch(u32Block[1])
//				{
//					case 0:
//						dir = LIFTMECH_DIR_DOWN;
//						break;
//					case 1:
//						dir = LIFTMECH_DIR_UP;
//						break;
//					default:
//						//report error
//						break;
//				}
//				vFCU_FCTL_LIFTMECH_Dir(actuator, dir);
//				#endif
//				break;
//
//			case NET_PKT__FCU_LIFTMECH__SET_SPEED:
//				//set speed of specific mech lift
//				#if C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL == 1U
//					E_FCU__LIFTMECH_ACTUATOR actuator;
//					switch(u32Block[0])
//					{
//						case 0:
//							actuator = LIFTMECH_AftLeft;
//							break;
//						case 1:
//							actuator = LIFTMECH_AftRight;
//							break;
//						case 2:
//							actuator = LIFTMECH_ForwardLeft;
//							break;
//						case 3:
//							actuator = LIFTMECH_ForwardRight;
//							break;
//						default:
//							//report error
//							break;
//					}
//					vFCU_FCTL_LIFTMECH_Speed(actuator, u32Block[1]);
//				#endif
//				break;
//
//			case NET_PKT__FCU_LIFTMECH__SET_GROUP_DIR:
//				//set direction of all mech lift actuators
//				#if C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL == 1U
//					switch(u32Block[0])
//					{
//						case 0:
//							dir = LIFTMECH_DIR_DOWN;
//							break;
//						case 1:
//							dir = LIFTMECH_DIR_UP;
//							break;
//						default:
//							//report error
//							break;
//					}
//					vFCU_FCTL_LIFTMECH__SetDirAll(dir);
//				#endif
//				break;
#if C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL == 1U
			case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE1:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE2:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE3:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE4:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE5:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE6:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE7:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__M_SET_SPEED_HE8:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__STATIC_HOVERING:
						case 	NET_PKT__FCU_HOVERENGINES_CONTROL__RELEASE_STATIC_HOVERING:
							vFCU_FLIGHTCTL_HOVERENGINES__SetCommand( (Luint32)ePacketType, u32Block[0]);
							break;
#endif //C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL

			case NET_PKT__FCU_LIFTMECH__SET_GROUP_SPEED:
				//set speed of all mech lift actuators
				#if C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL == 1U
					vFCU_FCTL_LIFTMECH__SetSpeedAll(u32Block[0]);
				#endif
				break;
			case NET_PKT__FCU_LIFTMECH__RELEASE:
				//release lift mechanism
				#if C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL == 1U
					vFCU_FCTL_LIFTMECH__Extend();
				#endif
				break;

			case NET_PKT__FCU_GEN__POD_STOP_COMMAND:
				//Execute Pod Stop Command
				#if C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL == 1U
				if(u32Block[0] == 0x1234ABCDU)
				{
					//transition to the pod stop phase.
					vFCU_FCTL_DRIVEPOD__SetPodStopCmd();
				}
				else
				{
					//maybe should log this error.
				}
				#endif
				break;

			case NET_PKT__FCU_GEN__POD_EMULATION_CONTROL:

				break;

			case NET_PKT__FCU_GEN__DAQ_ENABLE:

				//configure the DAQ streaming
				#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
					if(u32Block[0] == 1U)
					{
						vSIL3_DAQ__Streaming_On();
					}
					else
					{
						//switch off the DAQ
						vSIL3_DAQ__Streaming_Off();

						//flush out whats left
						vSIL3_DAQ__ForceFlush();
					}
				#endif
				break;

			case NET_PKT__FCU_GEN__DAQ_FLUSH:
				//tell the DAQ to flush.
				#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
					vSIL3_DAQ__ForceFlush();
				#endif
				break;

			case NET_PKT__FCU_GEN__STREAMING_CONTROL:
				//if the host wants to stream data packets.
				if(u32Block[0] == 1U)
				{
					//streaming on
					sFCU.sUDPDiag.eTxStreamingType = (E_NET__PACKET_T)u32Block[1];
				}
				else
				{
					//streaming off
					sFCU.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
				}

				break;


			case NET_PKT__FCU_ACCEL__REQUEST_CAL_DATA:
				//Host wants us to transmit the calibration data for the accelerometers system
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_ACCEL__TX_CAL_DATA;
				break;

			case NET_PKT__FCU_ACCEL__REQUEST_FULL_DATA:
				//transmit a full data packet including g-force, etc
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_ACCEL__TX_FULL_DATA;
				break;

			case NET_PKT__FCU_ACCEL__AUTO_CALIBRATE:
				#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
					//enter auto calibration mode
					//block 0 = device
					vSIL3_MMA8451_ZERO__AutoZero((Luint8)u32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_ACCEL__FINE_ZERO_ADJUSTMENT:
				#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U
					//Fine Zero adjustment on a particular axis
					//block 0 = device
					//block 1 = axis
					vSIL3_MMA8451_ZERO__Set_FineZero((Luint8)u32Block[0], (MMA8451__AXIS_E)u32Block[1]);
				#endif
				break;


			case NET_PKT__LASER_OPTO__REQUEST_LASER_DATA:
				//transmit the laser opto's data
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_OPTO__TX_LASER_DATA;
				break;

			case NET_PKT__LASER_OPTO__CAL_LASER_HEIGHT:
				#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U
					//calibrate
					vFCU_LASEROPTO__Set_CalValue(u32Block[0], f32Block[1]);
				#endif
				break;

			case NET_PKT__LASER_DIST__REQUEST_LASER_DATA:
				//transmit the laser distance data
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_DIST__TX_LASER_DATA;
				break;

			case NET_PKT__LASER_DIST__ENABLE_EMULATION_MODE:
				#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
					//switch on emu mode
					vFCU_LASERDIST_ETH__Enable_EmulationMode(u32Block[0], u32Block[1]);
				#endif
				break;

			case NET_PKT__LASER_DIST__RAW_EMULATION_VALUE:
				#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
					vFCU_LASERDIST_ETH__Emulation_Injection(s32Block[0]);
				#endif
				break;

			case NET_PKT__LASER_CONT__REQUEST_LASER_DATA:
				//transmit the laser contrast sub system
				switch(u32Block[0])
				{
					case 0:
						sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_0;
						break;
					case 1:
						sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_1;
						break;
					case 2:
						sFCU.sUDPDiag.eTxPacketType = NET_PKT__LASER_CONT__TX_LASER_DATA_2;
						break;

					default:
						break;
				}
				break;

			case NET_PKT__FCU_BRAKES__ENABLE_DEV_MODE:
				//set the brake system in development mode.
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__Enable_DevMode(u32Block[0], 0xABCD0987U);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MOVE_MOTOR_RAW:
				//move the brake system in development mode.
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__MoveMotor_RAW(u32Block[0], s32Block[1]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MOVE_IBEAM:
				//move the brakes ref to the I-Bream
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__MoveMotor_IBeam(f32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__SET_MOTOR_PARAM:

				//Block 0 = Parameter Type
				//Block 1 = Channel 0, 1
				//Block 2 = Setting
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
				switch(u32Block[0])
				{

					case 0U:
						//Max Acecl
						vSIL3_STEPDRIVE_MEM__Set_MaxAngularAccel(u32Block[1], s32Block[2]);
						break;

					case 1U:
						//microns/rev
						vSIL3_STEPDRIVE_MEM__Set_MicronsPerRev(u32Block[1], s32Block[2]);
						break;

					case 2U:
						//maxRPM
						vSIL3_STEPDRIVE_MEM__Set_MaxRPM(u32Block[1], s32Block[2]);
						break;

					case 3U:
						//set microstep resolution
						vSIL3_STEPDRIVE_MEM__Set_MicroStepResolution(u32Block[1], u32Block[2]);
						break;

					default:
						//fall on
						break;

				}//switch(u32Block[0])

				//once these have been updated, re-transmit
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM;

				#endif
				break;

			case NET_PKT__FCU_BRAKES__REQ_MOTOR_PARAM:
				//transmit the motor data
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_BRAKES__TX_MOTOR_PARAM;
				break;

			case NET_PKT__FCU_BRAKES__START_CAL_MODE:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_CAL__BeginCal(u32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__INIT:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES__Begin_Init(u32Block[0]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__MLP_ZEROSPAN:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					vFCU_BRAKES_ETH__MLP_ZeroSpan(u32Block[0], u32Block[1], u32Block[2]);
				#endif
				break;

			case NET_PKT__FCU_BRAKES__VELOC_ACCEL_SET:
				#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
					if(u32Block[0] == 0xABAB1122)
					{
						vFCU_BRAKES_STEP__UpdateValues(u32Block[1], u32Block[2], s32Block[3]);
					}
					else
					{
						//not for us
					}
				#endif
				break;

			case NET_PKT__FCU_THROTTLE__ENABLE_DEV_MODE:
				#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
					vFCU_THROTTLE_ETH__Enable_DevMode(u32Block[0], 0x77558833U);
				#endif
				break;

			case NET_PKT__FCU_THROTTLE__SET_RAW_THROTTLE:
				#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
					vFCU_THROTTLE_ETH__Set_Throttle((Luint8)u32Block[0], (Luint16)u32Block[1], (E_THROTTLE_CTRL_T)u32Block[2]);
				#endif
				break;

			case NET_PKT__FCU_THROTTLE__REQUEST_DATA:
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_THROTTLE__TX_DATA;
				break;

			case NET_PKT__FCU_PUSH__REQUEST_PUSHER_DATA:
				sFCU.sUDPDiag.eTxPacketType = NET_PKT__FCU_PUSH__TX_PUSHER_DATA;
				break;

			case NET_PKT__FCU_FLT__TX_TRACK_DB_CHUNK:
				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
				//Host to send a chunk to us

				//inc to the block3's start
				pu8Payload += 12U;

				//upload the chunk
				vFCU_FCTL_TRACKDB_MEM__UploadChunk(u32Block[0], u32Block[1], u32Block[2], pu8Payload);

				#endif
				break;

			case NET_PKT__FCU_FLT__SELECT_TRACK_DB:
				#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
					vFCU_FCTL_TRACKDB__Set_CurrentDB(u32Block[0], u32Block[1]);
				#endif
				break;

			case NET_PKT__FCU_ASI__SET_THROTTLE:

				//Change the throttle.
                #if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
                    if(u32Block[0] == 0x12123434U)
                    {
                        vFCU_ASI__Set_Throttle((Luint8)u32Block[1], (Luint16)u32Block[1]);
                    }
                    else
                    {
                        //not for us
                    }
                #endif//C_LOCALDEF__LCCM655__ENABLE_THROTTLE
                break;

			case NET_PKT__FCU_GEN__ENTER_PRE_RUN_PHASE_COMMAND:
				#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
#if 0
					vFCU_FCTL_MAINSM__EnterPreRun_Phase();
#endif
				#endif
				break;

			default:
				//do nothing
				break;

		}//switch((E_FCU_NET_PACKET_TYPES)ePacketType)
	}
	else
	{
		if(u16DestPort == C_RLOOP_NET__POWER_A__PORT)
		{
			//check for the BMS packet
			switch((E_NET__PACKET_T)ePacketType)
			{
				case NET_PKT__PWR_BMS__TX_BMS_STATUS:

					u8Device = 0U;

					//fault flags
					pu8Payload += 4U;
					//temp sensor state
					pu8Payload += 1U;
					//charger state
					pu8Payload += 1U;
					//num sensors
					pu8Payload += 2U;

					//highest individual temp
					sFCU.sBMS[u8Device].f32HighestTemp = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;

					//average temp
					sFCU.sBMS[u8Device].f32AverageTemp = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;

					//highest temp sensor index
					pu8Payload += 2U;

					//pack volts
					sFCU.sBMS[u8Device].f32PackVoltage = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;

					//highest volts
					sFCU.sBMS[u8Device].f32HighestCellVoltage = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;

					//lowest volts
					sFCU.sBMS[u8Device].f32LowestCellVoltage = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;

					//BMS boards Temp
					pu8Payload += 4U;

					//node press
					sFCU.sBMS[u8Device].f32PV_Press = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;

					//node temp
					sFCU.sBMS[u8Device].f32PV_Temp = f32SIL3_NUM_CONVERT__Array(pu8Payload);
					pu8Payload += 4U;
					break;


				default:
					break;
			}//switch((E_FCU_NET_PACKET_TYPES)ePacketType)

		}
		else
		{
			if(u16DestPort == C_RLOOP_NET__POWER_B__PORT)
			{
				//check for the BMS packet
				switch((E_NET__PACKET_T)ePacketType)
				{
					case NET_PKT__PWR_BMS__TX_BMS_STATUS:

						u8Device = 1U;

						//fault flags
						pu8Payload += 4U;
						//temp sensor state
						pu8Payload += 1U;
						//charger state
						pu8Payload += 1U;
						//num sensors
						pu8Payload += 2U;

						//highest individual temp
						sFCU.sBMS[u8Device].f32HighestTemp = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//average temp
						sFCU.sBMS[u8Device].f32AverageTemp = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//highest temp sensor index
						pu8Payload += 2U;

						//pack volts
						sFCU.sBMS[u8Device].f32PackVoltage = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//highest volts
						sFCU.sBMS[u8Device].f32HighestCellVoltage = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//lowest volts
						sFCU.sBMS[u8Device].f32LowestCellVoltage = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//BMS boards Temp
						pu8Payload += 4U;

						//node press
						sFCU.sBMS[u8Device].f32PV_Press = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//node temp
						sFCU.sBMS[u8Device].f32PV_Temp = f32SIL3_NUM_CONVERT__Array(pu8Payload);
						pu8Payload += 4U;

						//need pack current

						break;

					default:
						break;
				}//switch((E_FCU_NET_PACKET_TYPES)ePacketType)
			}
			else
			{

			}
		}
	}


}

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */


