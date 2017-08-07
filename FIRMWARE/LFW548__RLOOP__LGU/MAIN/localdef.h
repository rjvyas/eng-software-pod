#ifndef LOCALDEF_H_
#define LOCALDEF_H_

/*lint -e950*/

	//The launchpad
#ifndef WIN32
    #include <../../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
    #include <../../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#else
    #include <../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
    #include <../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#endif

/*******************************************************************************
RM4 GIO MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS						(0U)

		#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U

			#define GIOA_PIN_0_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_1_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_2_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_3_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_4_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_5_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_6_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_7_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_0_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_1_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_2_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_3_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_4_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_5_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_6_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_7_ISR()										vRM4_GIO_ISR__DefaultRoutine()

		#endif //#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U

		//Testing options
		#define C_LOCALDEF__LCCM133__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM133__RM4__GIO/rm4_gio.h>

	#endif //#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1


/*******************************************************************************
RM4 - RTI MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

		//globally switch on the WDT
		#define C_LOCALDEF__LCCM124__ENABLE_WDT								(0U)

		/** RTI CLOCK FREQUENCY
		 * Based on our standard system, valid values are div(2,4,8):
		 * 100 	(100MHZ)
		 * 75 	(75MHZ - ONLY ON RM57)
		 * 50	(50MHZ)
		 * 25	(25MHZ)
		 * */
		#define C_LOCALDEF__LCCM124__RTI_CLK_FREQ							(75U)

		/** RTCLK0 feeds counter 0 and is used for general purpose compare times */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER0_PRESCALER					(10U)

		/** RTCLK1 feeds counter 1 and can be used for 64bit timing */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER1_PRESCALER					(1U)


		//Sets up the time periods for each compare. Must be defined in microSeconds.
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_PERIOD_US 				(10000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_PERIOD_US 				(100000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_PERIOD_US 				(1000000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_PERIOD_US 				(1000000U)

		//these are the interrupt handlers which should point
		//to a function, otherwise leave as default
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_CALLBACK					vLGU_TIMERS__10MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_CALLBACK					vLGU_TIMERS__100MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()

		//Testing options
		#define C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC	 					(0U)

		#include <RM4/LCCM124__RM4__RTI/rm4_rti.h>

	#endif //#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
SIL3 - ETHERNET TRANSPORT
*******************************************************************************/
	#define C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

		//various protocol options
		//DHCP Client
		#define C_LOCALDEF__LCCM325__ENABLE_DHCP_CLIENT						(0U)
		//Link Layer Discovery Protocol
		#define C_LOCALDEF__LCCM325__ENABLE_LLDP							(0U)
		#define C_LOCALDEF__LCCM325__ENABLE_SNMP							(0U)

		//UDP Rx
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,dest_port)	vLGU_ETH__RxUDP(buffer, length, dest_port)
		/*vECU_ETHERNET_RX__UDPPacket*/

		//testing options
		#define C_LOCALDEF__LCCM325__ENABLE_TEST_SPEC						(0U)

		//protocol specific options
		//set to 1 to consider port numbers
		#define C_LOCALDEF__LCCM325__PROTO_UDP__ENABLE_PORT_NUMBERS			(1U)

		//main include file
		#include <MULTICORE/LCCM325__MULTICORE__802_3/eth.h>

	#endif //C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - SAFETY UDP LAYER
*******************************************************************************/
	#define C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

		/** User Rx Callback
		* Payload, Length, Type, DestPort, Faults
		*/
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vLGU_ETH__RxSafeUDP(p,l,t,d,f)

		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(C_RLOOP_NET_PORT__LGU)
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER2					(0U)

		/** Vision over SafeUDP Options */
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_TX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_RX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__MAX_BUFFER_SIZE				(640UL * 480UL * 2UL)


		/** Testing Options */
		#define C_LOCALDEF__LCCM528__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp.h>
	#endif //#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U



/*******************************************************************************
RLOOP - LANDING GEAR UNIT
*******************************************************************************/
    #define C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM667___PWM_1									N2HET_CHANNEL__1, 2U
		#define C_LOCALDEF__LCCM667___PWM_2									N2HET_CHANNEL__1, 16U
		#define C_LOCALDEF__LCCM667___PWM_3									N2HET_CHANNEL__1, 13U
		#define C_LOCALDEF__LCCM667___PWM_4									N2HET_CHANNEL__1, 9U

		#define C_LOCALDEF__LCCM667___DIR_A1								N2HET_CHANNEL__1, 18U
		#define C_LOCALDEF__LCCM667___DIR_B1								N2HET_CHANNEL__1, 6U
		#define C_LOCALDEF__LCCM667___DIR_A2								N2HET_CHANNEL__1, 14U
		#define C_LOCALDEF__LCCM667___DIR_B2								N2HET_CHANNEL__1, 13U
		#define C_LOCALDEF__LCCM667___DIR_A3								N2HET_CHANNEL__1, 4U
		#define C_LOCALDEF__LCCM667___DIR_B3								N2HET_CHANNEL__1, 27U
		#define C_LOCALDEF__LCCM667___DIR_A4								N2HET_CHANNEL__1, 22U
		#define C_LOCALDEF__LCCM667___DIR_B4								N2HET_CHANNEL__1, 29U

		#define C_LOCALDEF__LCCM667___RETRACT_1								RM4_GIO__PORT_A, 1U
		#define C_LOCALDEF__LCCM667___EXTEND_1								RM4_GIO__PORT_A, 0U
		#define C_LOCALDEF__LCCM667___RETRACT_2								RM4_GIO__PORT_A, 5U
		#define C_LOCALDEF__LCCM667___EXTEND_2								RM4_GIO__PORT_A, 2U
		#define C_LOCALDEF__LCCM667___RETRACT_3								RM4_GIO__PORT_A, 7U
		#define C_LOCALDEF__LCCM667___EXTEND_3								RM4_GIO__PORT_A, 6U
		#define C_LOCALDEF__LCCM667___RETRACT_4								RM4_GIO__PORT_B, 3U
		#define C_LOCALDEF__LCCM667___EXTEND_4								RM4_GIO__PORT_B, 2U


        /** Testing Options */
        #define C_LOCALDEF__LCCM667__ENABLE_TEST_SPEC                       (0U)

        /** Main include file */
        #include <LCCM667__RLOOP__LGU/lgu.h>
    #endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

#endif /* LOCALDEF_H_ */
