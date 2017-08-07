/**
 * @file		FCU__LASER_DISTANCE__ETHERNET.C
 * @brief		Ethernet UDP diagnostics for the laser_dist
 * @author		Lachlan Grogan
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
 * @addtogroup FCU__LASER_DISTANCE__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init Laser distance eth portion
 * 
 * @st_funcMD5		90CF579AC2F79F1D419D7122DC76A70A
 * @st_funcID		LCCM655R0.FILE.058.FUNC.001
 */
void vFCU_LASERDIST_ETH__Init(void)
{
	sFCU.sLaserDist.sEmu.u32EmuKey = 0U;
	sFCU.sLaserDist.sEmu.u8EmulationEnabled = 0U;
	sFCU.sLaserDist.sEmu.s32Distance = 0.0F;
}

/***************************************************************************//**
 * @brief
 * Transmith a laser distance eth packet
 * 
 * @param[in]		ePacketType				The packet type
 * @st_funcMD5		7CDEE346EA6FD4A5EBF1988276CEC563
 * @st_funcID		LCCM655R0.FILE.058.FUNC.002
 */
void vFCU_LASERDIST_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__LASER_DIST__TX_LASER_DATA:
			u16Length = 28U + 16U;
			break;


		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SIL3_SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{
			case NET_PKT__LASER_DIST__TX_LASER_DATA:


				//fault flags
				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserDist.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//spare 0
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sLaserDist.s32Distance_mm);
				pu8Buffer += 4U;

				//spare 1
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sLaserDist.s32PrevDistance_mm);
				pu8Buffer += 4U;

				//spare 2
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sLaserDist.s32Velocity_mms);
				pu8Buffer += 4U;

				//distance raw
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sLaserDist.s32PrevVelocity_mms);
				pu8Buffer += 4U;

				//distance filtered
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sLaserDist.s32Accel_mmss);
				pu8Buffer += 4U;

				//spare 3
				vSIL3_NUM_CONVERT__Array_S32(pu8Buffer, sFCU.sLaserDist.s32PrevAccel_mmss);
				pu8Buffer += 4U;


				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserDist.sBinary.unRx.u32);
				pu8Buffer += 4U;

				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserDist.sBinary.u32Counter__MissedStart);
				pu8Buffer += 4U;

				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserDist.sBinary.u32Counter__BadDistance);
				pu8Buffer += 4U;

				vSIL3_NUM_CONVERT__Array_U32(pu8Buffer, sFCU.sLaserDist.sBinary.u32Counter__ErrorCode);
				pu8Buffer += 4U;

				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET_PORT__FCU, C_RLOOP_NET_PORT__FCU);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}

/***************************************************************************//**
 * @brief
 * Via eth, inject some emulation value in
 * 
 * @param[in]		f32Value				The value in laser distance units
 * @st_funcMD5		C426D97404DAEA7381C135D6BE650EDE
 * @st_funcID		LCCM655R0.FILE.058.FUNC.003
 */
void vFCU_LASERDIST_ETH__Emulation_Injection(Lint32 s32Value)
{
	sFCU.sLaserDist.sEmu.s32Distance = s32Value;
}

/***************************************************************************//**
 * @brief
 * Enable emulation mode
 * 
 * @param[in]		u32Enable				1 = Enable
 * @param[in]		u32Key				 	0x01010202
 * @st_funcMD5		14B66A518C87DDDB5C890BF2B042B2C4
 * @st_funcID		LCCM655R0.FILE.058.FUNC.004
 */
void vFCU_LASERDIST_ETH__Enable_EmulationMode(Luint32 u32Key, Luint32 u32Enable)
{

	if(u32Key == 0x01010202U)
	{
		if(u32Enable == 1U)
		{
			//we are good to go
			sFCU.sLaserDist.sEmu.u32EmuKey = 0x98984343U;
			sFCU.sLaserDist.sEmu.u8EmulationEnabled = 1U;
		}
		else
		{
			//disable
			sFCU.sLaserDist.sEmu.u32EmuKey = 0U;
			sFCU.sLaserDist.sEmu.u8EmulationEnabled = 0U;
		}
	}
	else
	{
		//Wrong key, clear
		sFCU.sLaserDist.sEmu.u32EmuKey = 0U;
		sFCU.sLaserDist.sEmu.u8EmulationEnabled = 0U;
	}

}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */
