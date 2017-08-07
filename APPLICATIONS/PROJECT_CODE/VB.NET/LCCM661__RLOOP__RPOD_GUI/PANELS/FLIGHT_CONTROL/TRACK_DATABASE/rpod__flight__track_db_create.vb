﻿Namespace SIL3.rLoop.rPodControl.Panels.FlightControl.TrackDatabase

    ''' <summary>
    ''' Create the track database files on disk
    ''' </summary>
    ''' <remarks></remarks>
    Public Class Creator
        Inherits LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.PanelTemplate


#Region "DLL"
        ''' <summary>
        ''' The name of our DLL, could be a bit better done with relative paths
        ''' </summary>
        Private Const C_DLL_NAME As String = "..\..\..\PROJECT_CODE\DLLS\LDLL174__RLOOP__LCCM655\bin\Debug\LDLL174__RLOOP__LCCM655.dll"


        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Clear_Array()
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Get_Array(pu8ByteArray() As Byte)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Function u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize() As UInt16
        End Function
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Array(pu8ByteArray() As Byte)
        End Sub

        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Header(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_EnableAccels(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_EnableLRF(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_EnableContrast(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Footer(u32Value As UInt32)
        End Sub

        'profile system
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(u32Index As UInt32, u32Value As UInt32)
        End Sub
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Function u16FCTL_TRAKDB_WIN32__ComputeCRC() As UInt16
        End Function
        <System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)>
        Public Shared Sub vFCU_FCTL_TRACKDB_WIN32__Set_CRC(u16Value As UInt16)
        End Sub

#End Region ' #Region "DLL"

#Region "CONSTANTS"

        Private Const C_FCTL_TRACKDB__HEADER_SPARE_WORDS As Integer = 16
        Private Const C_FCTL_TRACKDB__PROFILE_SPARE_WORDS As Integer = 16

        '/** Total number of track databases stored in memory */
        Private Const C_FCTL_TRACKDB__MAX_MEM_DATABASES As Integer = 8

        '/** Max number of stripes the track DB knows about */
        Private Const C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES As Integer = 64


        '/** The maximum number of setpoints */
        Private Const C_FCTL_TRACKDB__MAX_SETPOINTS As Integer = 1024

#End Region '#Region "CONSTANTS"

#Region "MEMBERS"

        Private m_sLogDir As String

        Private m_txtTrackID As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtTrackHumanName As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtTrack_StartXPos As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtTrack_EndXPos As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtLRF_BeginXPos As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper
        Private m_txtNumStripes As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper

        Private m_chkEnableAccels As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper
        Private m_chkEnableLRF As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper
        Private m_chkEnableContrast As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper



        ''' <summary>
        ''' The database directory
        ''' </summary>
        Private m_sDBDir As String

        ''' <summary>
        ''' The CSV to read the track databse system
        ''' </summary>
        Private m_pCSV As LAPP188__RLOOP__LIB.SIL3.FileSupport.CSV

        ''' <summary>
        ''' Choose the database
        ''' </summary>
        Private m_cboDatabase As LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper

        ''' <summary>
        ''' The current selected index.
        ''' </summary>
        Private m_iCurrentIndex As Integer = -1

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
            Me.m_sLogDir = Me.m_sLogDir & "TRACK_DB\"

            'check our folder
            LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.Folder__CheckWarnMake(Me.m_sLogDir)

            Me.m_sDBDir = "..\..\..\..\FIRMWARE\PROJECT_CODE\LCCM655__RLOOP__FCU_CORE\FLIGHT_CONTROLLER\TRACK_DATABASE\DATABASES\"

            'for now
            Return

            'create the log files in prep
            Me.m_pCSV = New LAPP188__RLOOP__LIB.SIL3.FileSupport.CSV(Me.m_sDBDir & "databases.csv", ",", False, False)
            If Me.m_pCSV.File__Exists = False Then

                If MsgBox("Warn: A new track database CSV will be created, are you sure?", MsgBoxStyle.YesNo) = MsgBoxResult.Yes Then


                    'load up some headers
                    Me.m_pCSV.Header__Add("TRACK_INDEX")
                    Me.m_pCSV.Header__Add("TRACK_HUMAN_NAME")
                    Me.m_pCSV.Header__Add("LAST_EDIT_TIME")

                    Me.m_pCSV.Header__Add("TRACK_START_XPOS_MM")
                    Me.m_pCSV.Header__Add("TRACK_END_XPOS_MM")
                    Me.m_pCSV.Header__Add("LRF_START_POS_MM")
                    Me.m_pCSV.Header__Add("NUM_STRIPES")

                    Me.m_pCSV.Header__Add("ENABLE_ACCELS")
                    Me.m_pCSV.Header__Add("ENABLE_LRF")
                    Me.m_pCSV.Header__Add("ENABLE_CONTRAST")


                    For iCounter As Integer = 0 To C_FCTL_TRACKDB__HEADER_SPARE_WORDS - 1
                        Me.m_pCSV.Header__Add("SPARE_" & iCounter.ToString("00"))
                    Next

                    'save off the new headers
                    Me.m_pCSV.Header__Save()

                    'read the file.
                    Me.m_pCSV.File__Read()


                    'now add some stuff
                    For iCounter As Integer = 0 To C_FCTL_TRACKDB__MAX_MEM_DATABASES - 1
                        Dim pSB As New System.Text.StringBuilder

                        'index
                        pSB.Append(iCounter.ToString & ",")
                        pSB.Append("N/A" & ",")
                        pSB.Append(Now.ToString.Replace(",", "_") & ",")

                        pSB.Append("0" & ",")
                        pSB.Append("0" & ",")
                        pSB.Append("0" & ",")
                        pSB.Append("0" & ",")

                        For iCounter2 As Integer = 0 To C_FCTL_TRACKDB__HEADER_SPARE_WORDS - 1
                            pSB.Append("0" & ",")
                        Next

                        Dim sL As String = pSB.ToString
                        sL = sL.Remove(sL.Length - 1, 1)
                        Me.m_pCSV.Write_CSV_Line(sL)


                        'now write out a list of points to a single file
                        Dim lStripe As New List(Of String)
                        For iStripes As Integer = 0 To C_FCTL_TRACKDB__MAX_CONTRAST_STRIPES - 1
                            lStripe.Add("0")
                        Next
                        'save it off
                        LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__stripes.txt", lStripe)

                        'create the setpoint list
                        Dim lSet As New List(Of String)
                        For iSet As Integer = 0 To C_FCTL_TRACKDB__MAX_SETPOINTS - 1
                            lSet.Add("0")
                        Next
                        'save it off
                        LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__set_xpos.txt", lSet)
                        LAPP188__RLOOP__LIB.SIL3.FileSupport.FileHelpers.File__WriteLines(Me.m_sDBDir & iCounter.ToString("00") & "__set_veloc.txt", lSet)

                    Next 'For iCounter As Integer = 0 To C_FCTL_TRACKDB__MAX_MEM_DATABASES - 1

                End If

            Else

                'read the file
                Me.m_pCSV.File__Read()


            End If


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

                'check for our sim packet type
                If ePacketType = SIL3.rLoop.rPodControl.Ethernet.E_NET__PACKET_T.NET_PKT__LASER_CONT__TX_LASER_DATA_0 Then


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

            Dim l0 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper(10, 10, "Track Database List", MyBase.m_pInnerPanel)
            Me.m_cboDatabase = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ComboBoxHelper(500, l0)

            'fill
            For iCounter As Integer = 0 To Me.m_pCSV.m_alRows.Count - 1
                Dim pAL As ArrayList = Me.m_pCSV.m_alRows(iCounter)
                Me.m_cboDatabase.Threadsafe__AddItem("INDEX = " & pAL.Item(0).ToString & " [DESCRIPTION = " & pAL.Item(1).ToString & "]")
            Next

            Me.m_cboDatabase.Threadsafe__SetSelectedIndex(0)

            Dim btnChoose As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Choose", AddressOf Me.btnChooseDB__Click)
            btnChoose.Layout__RightOfControl(Me.m_cboDatabase)

            Dim btnGenBinary As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Gen Binary", AddressOf Me.btnGenBinary__Click)
            btnGenBinary.Layout__BelowControl(Me.m_cboDatabase)

            Dim l1 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track ID")
            l1.Layout__BelowControl(btnGenBinary)
            Me.m_txtTrackID = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l1)
            Me.m_txtTrackID.ReadOnly = True

            Dim l2 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Track Human Name")
            l2.Layout__AboveRightControl(l1, Me.m_txtTrackID)
            Me.m_txtTrackHumanName = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(200, l2)

            Dim l3 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Start XPos (mm)")
            l3.Layout__AboveRightControl(l2, Me.m_txtTrackHumanName)
            Me.m_txtTrack_StartXPos = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l3)

            Dim l4 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("End XPos (mm)")
            l4.Layout__AboveRightControl(l3, Me.m_txtTrack_StartXPos)
            Me.m_txtTrack_EndXPos = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l4)

            Dim l5 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("LRF Start X (mm)")
            l5.Layout__AboveRightControl(l4, Me.m_txtTrack_EndXPos)
            Me.m_txtLRF_BeginXPos = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l5)

            Dim l6 As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.LabelHelper("Num Stripes")
            l6.Layout__BelowControl(Me.m_txtTrackID)
            Me.m_txtNumStripes = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.TextBoxHelper(100, l6)

            Me.m_chkEnableAccels = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper("Enable Accels")
            Me.m_chkEnableAccels.Layout__BelowControl(Me.m_txtNumStripes)

            Me.m_chkEnableLRF = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper("Enable LRF")
            Me.m_chkEnableLRF.Layout__RightOfControl(Me.m_chkEnableAccels)

            Me.m_chkEnableContrast = New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.CheckBoxHelper("Enable Contrast")
            Me.m_chkEnableContrast.Layout__RightOfControl(Me.m_chkEnableLRF)

            Dim btnSave As New LAPP188__RLOOP__LIB.SIL3.ApplicationSupport.ButtonHelper(100, "Save", AddressOf Me.btnSave__Click)
            btnSave.Layout__RightOfControl(Me.m_txtLRF_BeginXPos)

        End Sub

#End Region '#Region "PANEL LAYOUT"

#Region "BUTTON HELPERS"

        ''' <summary>
        ''' Save the current edited page
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnSave__Click(s As Object, e As EventArgs)

            If Me.m_txtTrackHumanName.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_HUMAN_NAME", Me.m_iCurrentIndex, Me.m_txtTrackHumanName.Text, True)
                Me.m_txtTrackHumanName.Dirty = False
            End If

            If Me.m_txtTrack_StartXPos.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_START_XPOS_MM", Me.m_iCurrentIndex, Me.m_txtTrack_StartXPos.Text, True)
                Me.m_txtTrack_StartXPos.Dirty = False
            End If

            If Me.m_txtTrack_EndXPos.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("TRACK_END_XPOS_MM", Me.m_iCurrentIndex, Me.m_txtTrack_EndXPos.Text, True)
                Me.m_txtTrack_EndXPos.Dirty = False
            End If

            If Me.m_txtLRF_BeginXPos.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("LRF_START_POS_MM", Me.m_iCurrentIndex, Me.m_txtLRF_BeginXPos.Text, True)
                Me.m_txtLRF_BeginXPos.Dirty = False
            End If

            If Me.m_txtNumStripes.Dirty = True Then
                Me.m_pCSV.Cell__SetContents("NUM_STRIPES", Me.m_iCurrentIndex, Me.m_txtNumStripes.Text, True)
                Me.m_txtNumStripes.Dirty = False
            End If

            If Me.m_chkEnableAccels.Checked = True Then
                Me.m_pCSV.Cell__SetContents("ENABLE_ACCELS", Me.m_iCurrentIndex, "1", True)
            Else
                Me.m_pCSV.Cell__SetContents("ENABLE_ACCELS", Me.m_iCurrentIndex, "0", True)
            End If

            If Me.m_chkEnableLRF.Checked = True Then
                Me.m_pCSV.Cell__SetContents("ENABLE_LRF", Me.m_iCurrentIndex, "1", True)
            Else
                Me.m_pCSV.Cell__SetContents("ENABLE_LRF", Me.m_iCurrentIndex, "0", True)
            End If

            If Me.m_chkEnableContrast.Checked = True Then
                Me.m_pCSV.Cell__SetContents("ENABLE_CONTRAST", Me.m_iCurrentIndex, "1", True)
            Else
                Me.m_pCSV.Cell__SetContents("ENABLE_CONTRAST", Me.m_iCurrentIndex, "0", True)
            End If

        End Sub

        ''' <summary>
        ''' Choose the database
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnChooseDB__Click(s As Object, e As EventArgs)

            'assign the current index.
            Me.m_iCurrentIndex = Me.m_cboDatabase.SelectedIndex

            'see if the points file exists
            Me.m_txtTrackID.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(0).ToString)
            Me.m_txtTrackHumanName.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(1).ToString)
            Me.m_txtTrack_StartXPos.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(3).ToString)
            Me.m_txtTrack_EndXPos.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(4).ToString)
            Me.m_txtLRF_BeginXPos.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(5).ToString)
            Me.m_txtNumStripes.Threadsafe__SetText(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(6).ToString)

            If CInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(7).ToString) = 1 Then
                Me.m_chkEnableAccels.Checked = True
            Else
                Me.m_chkEnableAccels.Checked = False
            End If
            If CInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(8).ToString) = 1 Then
                Me.m_chkEnableLRF.Checked = True
            Else
                Me.m_chkEnableLRF.Checked = False
            End If
            If CInt(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(9).ToString) = 1 Then
                Me.m_chkEnableContrast.Checked = True
            Else
                Me.m_chkEnableContrast.Checked = False
            End If

        End Sub

        ''' <summary>
        ''' Generate the binary file
        ''' </summary>
        ''' <param name="s"></param>
        ''' <param name="e"></param>
        Private Sub btnGenBinary__Click(s As Object, e As EventArgs)
            If Me.m_iCurrentIndex = -1 Then
                MsgBox("You have not selected an index yet")
                Exit Sub
            End If
            Me.Database__GenBinary(Me.m_iCurrentIndex)
        End Sub

#End Region '#Region "BUTTON HELPERS"

#Region "LOAD DATABASE"

        ''' <summary>
        ''' Load the track database files in text format
        ''' </summary>
        ''' <param name="iIndex"></param>
        Private Sub Database__LoadText(iIndex As Integer)



        End Sub

        ''' <summary>
        ''' Generate the binary form of the database file
        ''' </summary>
        ''' <param name="iIndex"></param>
        Private Sub Database__GenBinary(iIndex As UInt32)

            Dim iNumStripes As UInt32 = 41
            Dim u32NumSetpoints As UInt32 = 88

            'clear the internal mem array
            vFCU_FCTL_TRACKDB_WIN32__Clear_Array()

            'setup the header
            vFCU_FCTL_TRACKDB_WIN32__Set_Header(&HABCD1234L)

            vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(32)
            vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(iIndex)
            vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(3).ToString))
            vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(4).ToString))
            vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(5).ToString))
            vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(6).ToString))

            For u32Counter As UInt32 = 0 To iNumStripes - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(u32Counter, u32Counter * 10)
            Next

            vFCU_FCTL_TRACKDB_WIN32__Set_EnableAccels(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(7).ToString))
            vFCU_FCTL_TRACKDB_WIN32__Set_EnableLRF(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(8).ToString))
            vFCU_FCTL_TRACKDB_WIN32__Set_EnableContrast(UInt32.Parse(Me.m_pCSV.m_alRows(Me.m_iCurrentIndex).item(9).ToString))

            For u32Counter As UInt32 = 0 To C_FCTL_TRACKDB__HEADER_SPARE_WORDS - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(u32Counter, 0)
            Next

            vFCU_FCTL_TRACKDB_WIN32__Set_Footer(&H12345678L)


            'setup the profile
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(0)
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(1200)
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(1500)
            vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(u32NumSetpoints)
            For u32Counter = 0 To u32NumSetpoints - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(u32Counter, u32Counter * 22)
                vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(u32Counter, u32Counter * 33)
            Next

            For u32Counter As UInt32 = 0 To C_FCTL_TRACKDB__PROFILE_SPARE_WORDS - 1
                vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(u32Counter, 0)
            Next

            Dim u16CRC As UInt16 = u16FCTL_TRAKDB_WIN32__ComputeCRC()
            vFCU_FCTL_TRACKDB_WIN32__Set_CRC(u16CRC)


            'do the save
            Dim u8Array() As Byte
            Dim u16Size As UInt16 = u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize()
            ReDim u8Array(u16Size - 1)

            Dim pS As New System.IO.FileStream(Me.m_sDBDir & Me.m_iCurrentIndex.ToString("00") & ".bin", IO.FileMode.Create)
            Dim pW As New System.IO.BinaryWriter(pS)

            'load
            vFCU_FCTL_TRACKDB_WIN32__Get_Array(u8Array)

            'file it
            pW.Write(u8Array, 0, u16Size)

            'close off
            pW.Close()
            pS.Close()

            MsgBox("File Saved...")

        End Sub

#End Region '#Region "LOAD DATABASE"

    End Class


End Namespace
