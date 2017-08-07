﻿Namespace SIL3.rLoop.rPodControl.Panels.FlightControl

    ''' <summary>
    ''' ASI Interface System
    ''' </summary>
    ''' <remarks></remarks>
    Public Class ASI
        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate

#Region "CONSTANTS"
        Private Const C_NUM_ASI_CONTROLLERS As Integer = 8
        Private Const C_NUM__THROTTLES As Integer = 8
#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_iRxCount As Integer
        Private m_txtCount As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        Private m_txtFlags As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags
        Private m_txtMainState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtModbusState As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtScanIndex As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtCurTx__CurrCommand As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16

        'for the current Tx packet
        Private m_txtCurTx__SlaveAddx As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtCurTx__FunctionCode As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8
        Private m_txtCurTx__BACObject As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16
        Private m_txtCurTx__ParamValue As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16
        Private m_txtCurTx__VarType As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8

        Private m_txtCurRx__ErrorType As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay
        Private m_txtCurRx__Value As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16

        'actual data
        Private m_txtAct_Faults(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16
        Private m_txtAct_TempC(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtAct_Current(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32
        Private m_txtAct_RPM(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16

        'setup the HE
        Private m_cboHE As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper
        Private m_cboMode As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper
        Private m_txtSetRPM As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        ''' <summary>
        ''' The logging directory
        ''' </summary>
        Private m_sLogDir As String


#End Region '#Region "MEMBERS"

#Region "NEW"
        ''' <summary>
        ''' New instance
        ''' </summary>
        ''' <param name="sPanelText"></param>
        ''' <remarks></remarks>
        Public Sub New(sPanelText As String, sLog As String)
            MyBase.New(sPanelText)

            Me.m_sLogDir = sLog
            Me.m_sLogDir = Me.m_sLogDir & "ASI\"

            'check our folder
            LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir, True)


        End Sub
#End Region '#Region "New"

#Region "EVENTS"

        ''' <summary>
        ''' Raised wehen we want to transmit a control packet
        ''' </summary>
        ''' <param name="u16Type"></param>
        ''' <param name="u32Block0"></param>
        ''' <param name="u32Block1"></param>
        ''' <param name="u32Block2"></param>
        ''' <param name="u32Block3"></param>
        ''' <remarks></remarks>

        Public Event UserEvent__SafeUDP__Tx_X4(eEndpoint As SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS, u16Type As UInt16, u32Block0 As UInt32, u32Block1 As UInt32, u32Block2 As UInt32, u32Block3 As UInt32)


        ''' <summary>
        ''' New Packet In
        ''' </summary>
        ''' <param name="ePacketType"></param>
        ''' <param name="u16PayloadLength"></param>
        ''' <param name="u8Payload"></param>
        ''' <param name="u16CRC"></param>
        Public Sub InernalEvent__UDPSafe__RxPacketB(ByVal ePacketType As SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T, ByVal u16PayloadLength As LAPP188__RLOOP__LIB.SIL3.Numerical.U16, ByRef u8Payload() As Byte, ByVal u16CRC As LAPP188__RLOOP__LIB.SIL3.Numerical.U16)

            'only do if we have been created
            If MyBase.m_bLayout = True Then

                'match thepacket
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ASI__TX_ASI_DATA Then

                    Dim iOffset As Integer = 0

                    iOffset += Me.m_txtFlags.Flags__Update(u8Payload, iOffset, True)

                    Me.m_txtMainState.Value__Update(u8Payload(iOffset))
                    iOffset += 1
                    Me.m_txtModbusState.Value__Update(u8Payload(iOffset))
                    iOffset += 1
                    Me.m_txtScanIndex.Value__Update(u8Payload, iOffset)
                    iOffset += 1
                    iOffset += Me.m_txtCurTx__CurrCommand.Value__Update(u8Payload, iOffset)

                    iOffset += Me.m_txtCurTx__SlaveAddx.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCurTx__FunctionCode.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCurTx__BACObject.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCurTx__ParamValue.Value__Update(u8Payload, iOffset)
                    iOffset += Me.m_txtCurTx__VarType.Value__Update(u8Payload, iOffset)

                    Me.m_txtCurRx__ErrorType.Value__Update(u8Payload(iOffset))
                    iOffset += 1
                    iOffset += Me.m_txtCurRx__Value.Value__Update(u8Payload, iOffset)

                    For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                        iOffset += Me.m_txtAct_Faults(iCounter).Value__Update(u8Payload, iOffset)
                    Next
                    For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                        iOffset += Me.m_txtAct_TempC(iCounter).Value__Update(u8Payload, iOffset)
                    Next
                    For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                        iOffset += Me.m_txtAct_Current(iCounter).Value__Update(u8Payload, iOffset)
                    Next
                    For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                        iOffset += Me.m_txtAct_RPM(iCounter).Value__Update(u8Payload, iOffset)
                    Next

                    Me.m_iRxCount += 1
                    Me.m_txtCount.Threadsafe__SetText(Me.m_iRxCount.ToString)


                End If
            End If

        End Sub


#End Region '#Region "EVENTS"

#Region "PANEL LAYOUT"
        ''' <summary>
        ''' Create our layout prior to being shown
        ''' </summary>
        ''' <remarks></remarks>
        Public Overrides Sub LayoutPanel()

            Dim l0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Streaming Control", MyBase.m_pInnerPanel)
            Dim btnOn As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Stream On", AddressOf btnStreamOn__Click)
            btnOn.Layout__BelowControl(l0)
            Dim l11 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Rx Count")
            l11.Layout__AboveRightControl(l0, btnOn)
            Me.m_txtCount = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l11)

            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Fault Flags")
            l1.Layout__BelowControl(btnOn)
            Me.m_txtFlags = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_FaultFlags(100, l1)

            Dim l2 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Main State Machine")
            l2.Layout__AboveRightControl(l1, Me.m_txtFlags)
            Me.m_txtMainState = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(300, l2)

            Dim l3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Modbus State Machine")
            l3.Layout__AboveRightControl(l2, Me.m_txtMainState)
            Me.m_txtModbusState = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(300, l3)

            Dim l4 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Scan Index")
            l4.Layout__BelowControl(Me.m_txtFlags)
            Me.m_txtScanIndex = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(100, l4)

            Dim l44 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Current Command")
            l44.Layout__AboveRightControl(l4, Me.m_txtScanIndex)
            Me.m_txtCurTx__CurrCommand = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16(200, l44)
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__OVER_TEMP_THRESHOLD", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(90))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__FOLDBACK_STARING_TEMP", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(91))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__FOLDBACK_END_TEMP", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(92))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__COMMAND_SOURCE", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(208))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__CONTROLLER_STATUS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(257))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__FAULTS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(&H102))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__CONT_TEMP", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(259))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__TEMPERATURE", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(261))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__MOTOR_CURRENT", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(262))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__MOTOR_RPM ", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(263))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__LAST_FAULT", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(269))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__RAW_SENSOR_TEMPERATURE", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(273))
            Me.m_txtCurTx__CurrCommand.List__Add("C_FCU_ASI__SAVE_SETTINGS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(511))

            'current command
            Dim l55 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Current Command (Tx)")
            l55.Layout__BelowControl(Me.m_txtScanIndex)
            Dim l5 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Slave Addx")
            l5.Layout__BelowControl(l55)
            Me.m_txtCurTx__SlaveAddx = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(100, l5)

            Dim l6 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Modbus Function")
            l6.Layout__AboveRightControl(l5, Me.m_txtCurTx__SlaveAddx)
            Me.m_txtCurTx__FunctionCode = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(200, l6)
            Me.m_txtCurTx__FunctionCode.List__Add("FUNC_CODE__READ_COILS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(1))
            Me.m_txtCurTx__FunctionCode.List__Add("FUNC_CODE__READ_DISCRETE_INPUTS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(2))
            Me.m_txtCurTx__FunctionCode.List__Add("FUNC_CODE__READ_HOLDING_REGS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(3))
            Me.m_txtCurTx__FunctionCode.List__Add("FUNC_CODE__READ_INPUT_REGS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(4))
            Me.m_txtCurTx__FunctionCode.List__Add("FUNC_CODE__WRITE_SINGLE_COIL", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(5))
            Me.m_txtCurTx__FunctionCode.List__Add("FUNC_CODE__WRITE_SINGLE_REG", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(6))


            Dim l7 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("BAC Object Code")
            l7.Layout__AboveRightControl(l6, Me.m_txtCurTx__FunctionCode)
            Me.m_txtCurTx__BACObject = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16(200, l7)
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__OVER_TEMP_THRESHOLD", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(90))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__FOLDBACK_STARING_TEMP", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(91))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__FOLDBACK_END_TEMP", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(92))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__COMMAND_SOURCE", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(208))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__CONTROLLER_STATUS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(257))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__FAULTS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(&H102))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__CONT_TEMP", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(259))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__TEMPERATURE", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(261))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__MOTOR_CURRENT", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(262))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__MOTOR_RPM ", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(263))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__LAST_FAULT", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(269))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__RAW_SENSOR_TEMPERATURE", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(273))
            Me.m_txtCurTx__BACObject.List__Add("C_FCU_ASI__SAVE_SETTINGS", New LAPP188__RLOOP__LIB.SIL3.Numerical.U16(511))

            Dim l8 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Param Value")
            l8.Layout__AboveRightControl(l7, Me.m_txtCurTx__BACObject)
            Me.m_txtCurTx__ParamValue = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16(100, l8)

            Dim l9 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Variable Type")
            l9.Layout__AboveRightControl(l8, Me.m_txtCurTx__ParamValue)
            Me.m_txtCurTx__VarType = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U8(100, l9)
            Me.m_txtCurTx__VarType.List__Add("E_INT8", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H11))
            Me.m_txtCurTx__VarType.List__Add("E_UINT8", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H12))
            Me.m_txtCurTx__VarType.List__Add("E_INT16", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H21))
            Me.m_txtCurTx__VarType.List__Add("E_UINT16", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H22))
            Me.m_txtCurTx__VarType.List__Add("E_INT32", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H41))
            Me.m_txtCurTx__VarType.List__Add("E_UINT32", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H42))
            Me.m_txtCurTx__VarType.List__Add("E_INT64", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H81))
            Me.m_txtCurTx__VarType.List__Add("E_UINT64", New LAPP188__RLOOP__LIB.SIL3.Numerical.U8(&H82))

            'setup the main states
            Me.m_txtMainState.States__Add("ASI_STATE__IDLE")
            Me.m_txtMainState.States__Add("ASI_STATE__CONFIG_MUX")
            Me.m_txtMainState.States__Add("ASI_STATE__ISSUE_COMMAND")
            Me.m_txtMainState.States__Add("ASI_STATE__WAIT_COMMAND_COMPLETE")
            Me.m_txtMainState.States__Add("ASI_STATE__INC_SCAN_INDEX")

            Me.m_txtModbusState.States__Add("ASI_COMM_STATE__IDLE")
            Me.m_txtModbusState.States__Add("ASI_COMM_STATE__WAIT_TURNAROUND_DELAY")
            Me.m_txtModbusState.States__Add("ASI_COMM_STATE__WAIT_REPLY")
            Me.m_txtModbusState.States__Add("ASI_COMM_STATE__PROCESS_REPLY")
            Me.m_txtModbusState.States__Add("ASI_COMM_STATE__PROCESS_ERROR")


            Dim l56 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Last Command (Rx)")
            l56.Layout__BelowControl(Me.m_txtCurTx__SlaveAddx)

            Dim l10 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Rx Type")
            l10.Layout__BelowControl(l56)
            Me.m_txtCurRx__ErrorType = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_StateDisplay(200, l10)

            Me.m_txtCurRx__ErrorType.States__Add("E_NONE")
            Me.m_txtCurRx__ErrorType.States__Add("E_SLAVE_MISMATCH")
            Me.m_txtCurRx__ErrorType.States__Add("E_CRC_CHECK_FAILED")
            Me.m_txtCurRx__ErrorType.States__Add("E_REPLY_TIMEOUT_EXPIRED")
            Me.m_txtCurRx__ErrorType.States__Add("E_ERROR_RESPONSE")

            Dim l12 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Rx Value")
            l12.Layout__AboveRightControl(l10, Me.m_txtCurRx__ErrorType)
            Me.m_txtCurRx__Value = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16(100, l12)

            Dim l30 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Actual Parameters")
            l30.Layout__BelowControl(Me.m_txtCurRx__ErrorType)

            Dim l31(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                l31(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(iCounter.ToString & ": Faults")
                If iCounter = 0 Then
                    l31(iCounter).Layout__BelowControl(l30)
                Else
                    l31(iCounter).Layout__AboveRightControl(l31(iCounter - 1), Me.m_txtAct_Faults(iCounter - 1))
                End If
                Me.m_txtAct_Faults(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16(100, l31(iCounter))
            Next

            Dim l32(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                l32(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(iCounter.ToString & ": Temp C")
                If iCounter = 0 Then
                    l32(iCounter).Layout__BelowControl(Me.m_txtAct_Faults(0))
                Else
                    l32(iCounter).Layout__AboveRightControl(l32(iCounter - 1), Me.m_txtAct_TempC(iCounter - 1))
                End If
                Me.m_txtAct_TempC(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l32(iCounter))
            Next

            Dim l33(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                l33(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(iCounter.ToString & ": Current A")
                If iCounter = 0 Then
                    l33(iCounter).Layout__BelowControl(Me.m_txtAct_TempC(0))
                Else
                    l33(iCounter).Layout__AboveRightControl(l33(iCounter - 1), Me.m_txtAct_Current(iCounter - 1))
                End If
                Me.m_txtAct_Current(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_F32(100, l33(iCounter))
            Next

            Dim l34(C_NUM_ASI_CONTROLLERS - 1) As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper
            For iCounter As Integer = 0 To C_NUM_ASI_CONTROLLERS - 1
                l34(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(iCounter.ToString & ": RPM")
                If iCounter = 0 Then
                    l34(iCounter).Layout__BelowControl(Me.m_txtAct_Current(0))
                Else
                    l34(iCounter).Layout__AboveRightControl(l34(iCounter - 1), Me.m_txtAct_RPM(iCounter - 1))
                End If
                Me.m_txtAct_RPM(iCounter) = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper_U16(100, l34(iCounter))
            Next

            Dim l90 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Throttle Index")
            l90.Layout__BelowControl(Me.m_txtAct_RPM(0))
            Me.m_cboHE = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper(100)
            Me.m_cboHE.Layout__BelowControl(l90)
            For iCounter As Integer = 0 To C_NUM__THROTTLES - 1
                Me.m_cboHE.Threadsafe__AddItem(iCounter.ToString)
            Next
            Me.m_cboHE.Threadsafe__AddItem("ALL")
            Me.m_cboHE.Threadsafe__SetSelectedIndex(0)

            Dim l91 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Throttle Mode")
            l91.Layout__AboveRightControl(l90, Me.m_cboHE)
            Me.m_cboMode = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper(100, l91)
            Me.m_cboMode.Threadsafe__AddItem("STEP")
            Me.m_cboMode.Threadsafe__AddItem("RAMP")
            Me.m_cboMode.Threadsafe__SetSelectedIndex(0)

            Dim l92 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Target RPM")
            l92.Layout__AboveRightControl(l91, Me.m_cboMode)
            Me.m_txtSetRPM = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l92)
            Me.m_txtSetRPM.Threadsafe__SetText("0")

            Dim btnChange As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Change", AddressOf Me.btnChange__Click)
            btnChange.Layout__RightOfControl(Me.m_txtSetRPM)


        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"


        ''' <summary>
        ''' Change our HE index
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnChange__Click(s As Object, e As EventArgs)

            Dim iHE As Integer = Me.m_cboHE.SelectedIndex
            If iHE < 0 Then
                MsgBox("Error: Invalid HE Index")
                Exit Sub
            End If

            RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_THROTTLE__SET_RAW_THROTTLE,
                                                 iHE,
                                                 UInt32.Parse(Me.m_txtSetRPM.Text),
                                                 Me.m_cboMode.SelectedIndex, 0)
        End Sub

        ''' <summary>
        ''' Control streaming
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnStreamOn__Click(s As Object, e As EventArgs)

            Dim pSB As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper = CType(s, LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper)

            If pSB.Text = "Stream On" Then
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 1, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ASI__TX_ASI_DATA, 0, 0)

                pSB.Text = "Stream Off"
            Else
                RaiseEvent UserEvent__SafeUDP__Tx_X4(SIL3.rLoop.rPodControl.Ethernet.E_POD_CONTROL_POINTS.POD_CTRL_PT__FCU,
                                                 SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_GEN__STREAMING_CONTROL,
                                                 0, SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__FCU_ASI__TX_ASI_DATA, 0, 0)

                pSB.Text = "Stream On"
            End If

        End Sub


#End Region '#Region "BUTTON HELPERS"

    End Class


End Namespace
