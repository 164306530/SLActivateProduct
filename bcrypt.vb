VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "clsPRF"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

'================================
'EVENTS
'================================
Public Event Error(ByVal Number As Long, Description As String, ByVal Source As String)

Private Const MS_PRIMITIVE_PROVIDER As String = "Microsoft Primitive Provider"

'CNG Declarations
Private Declare Function BCryptOpenAlgorithmProvider Lib "bcrypt.dll" (ByRef hAlgorithm As Long, ByVal pszAlgId As Long, ByVal pszImplementation As Long, ByVal dwFlags As Long) As Long
Private Declare Function BCryptCloseAlgorithmProvider Lib "bcrypt.dll" (ByVal hAlgorithm As Long, ByVal dwFlags As Long) As Long
Private Declare Function BCryptGetProperty Lib "bcrypt" (ByVal hObject As Long, ByVal pszProperty As Long, ByVal pbOutput As Long, ByVal cbOutput As Long, ByRef cbResult As Long, ByVal dwFlags As Long) As Long
Private Declare Function BCryptCreateHash Lib "bcrypt" (ByVal hAlgorithm As Long, ByRef hHash As Long, ByVal pbHashObject As Long, ByVal cbHashObject As Long, ByVal pbSecret As Long, ByVal cbSecret As Long, ByVal dwFlags As Long) As Long
Private Declare Function BCryptHashData Lib "bcrypt" (ByVal hHash As Long, ByVal pbInput As Long, ByVal cbInput As Long, ByVal dwFlags As Long) As Long
Private Declare Function BCryptFinishHash Lib "bcrypt" (ByVal hHash As Long, ByVal pbOutput As Long, ByVal cbOutput As Long, ByVal dwFlags As Long) As Long
Private Declare Function BCryptDestroyHash Lib "bcrypt" (ByVal hHash As Long) As Long

'API memory functions
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

'CNG Buffers
Private bInBuffer() As Byte
Private bOutBuffer() As Byte
Private bRandom() As Byte
Private bSecret() As Byte
Private bSeed() As Byte
Private Function HMAC_HashData(sAlgID As String, bSecret() As Byte, Optional SeedFlg As Boolean) As Boolean
    Const Routine As String = "clsSSL.HMAC_HashData"
    Const BCRYPT_ALG_HANDLE_HMAC_FLAG As Long = 8 '&H00000008
    Dim hAlg As Long
    Dim cbResult As Long
    Dim cbHashObject As Long
    Dim cbHashLen As Long
    Dim HashObject() As Byte
    Dim Hash() As Byte
    Dim hHash As Long
    Dim lRet As Long
    Dim pSecret As Long
    If sAlgID = "SHA1" Then pSecret = GetbSize(bSecret) / 2
    lRet = BCryptOpenAlgorithmProvider(hAlg, StrPtr(sAlgID), StrPtr(MS_PRIMITIVE_PROVIDER), BCRYPT_ALG_HANDLE_HMAC_FLAG)
    If lRet <> 0 Then
        MsgBox "Error: " & Hex$(lRet) & " when opening Algorithm Provider!"
        GoTo ReleaseHandles
    End If
    lRet = BCryptGetProperty(hAlg, StrPtr("ObjectLength"), VarPtr(cbHashObject), 4, cbResult, 0)
    If lRet <> 0 Then
        MsgBox "Error: " & Hex$(lRet) & " when recovering Object length!"
        GoTo ReleaseHandles
    End If
    lRet = BCryptGetProperty(hAlg, StrPtr("HashDigestLength"), VarPtr(cbHashLen), 4, cbResult, 0)
    If lRet <> 0 Then
        MsgBox "Error: " & Hex$(lRet) & " when recovering Hash length!"
        GoTo ReleaseHandles
    End If
    ReDim HashObject(cbHashObject - 1)
    lRet = BCryptCreateHash(hAlg, hHash, VarPtr(HashObject(0)), cbHashObject, VarPtr(bSecret(pSecret)), GetbSize(bSecret) / 2, 0)
    If lRet <> 0 Then
        MsgBox "Error: " & Hex$(lRet) & " when creating Hash!"
        GoTo ReleaseHandles
    End If
    Hash = bInBuffer
HashHere:
    lRet = BCryptHashData(hHash, VarPtr(Hash(0)), GetbSize(Hash), 0)
    If lRet <> 0 Then
        MsgBox "Error: " & Hex$(lRet) & " when hashing data!"
        GoTo ReleaseHandles
    End If
    If SeedFlg Then
        Hash = bSeed
        SeedFlg = False
        GoTo HashHere
    End If
    ReDim Hash(cbHashLen - 1)
    lRet = BCryptFinishHash(hHash, VarPtr(Hash(0)), cbHashLen, 0)
    If lRet <> 0 Then
        MsgBox "Error: " & Hex$(lRet) & " when finishing Hash!"
        GoTo ReleaseHandles
    End If
    bOutBuffer = Hash
    HMAC_HashData = True
ReleaseHandles:
    BCryptDestroyHash hHash
    BCryptCloseAlgorithmProvider hAlg, 0
End Function

Private Function ByteToStr(bArray() As Byte) As String
    Dim lPntr As Long
    Dim bTmp() As Byte
    On Error GoTo ByteErr
    ReDim bTmp(UBound(bArray) * 2 + 1)
    For lPntr = 0 To UBound(bArray)
        bTmp(lPntr * 2) = bArray(lPntr)
    Next lPntr
    Let ByteToStr = bTmp
    Exit Function
ByteErr:
    ByteToStr = ""
End Function

Private Function GetbSize(bArray() As Byte) As Long
    On Error GoTo GetSizeErr
    GetbSize = UBound(bArray) + 1
    Exit Function
GetSizeErr:
    GetbSize = 0
End Function

Public Function PRF(sLabel As String, HashLen As Long) As Boolean
    Dim bLabel() As Byte
    Dim bMD5Hash() As Byte
    Dim bSHA1Hash() As Byte
    Dim bTmpBuffer() As Byte
    Dim lLen As Long
    Dim I%
    bLabel = StrToByte(sLabel)
    bSeed = bLabel
    lLen = GetbSize(bRandom)
    ReDim Preserve bSeed(UBound(bLabel) + lLen)
    CopyMemory bSeed(UBound(bLabel) + 1), bRandom(0), lLen
    'Figure out how many iterations should be performed for MD5 Hash
    I% = Int(HashLen / 16)
    If HashLen Mod 16 > 0 Then I% = I% + 1 'Adj for division not even
    ReDim bMD5Hash(0)
    For I% = 1 To I%
        If I% = 1 Then
            bInBuffer = bSeed 'First Hash uses seed
        Else
            bInBuffer = bTmpBuffer
        End If
        If Not HMAC_HashData("MD5", bSecret) Then Exit Function
        bTmpBuffer = bOutBuffer 'Save output
        bInBuffer = bOutBuffer
        If Not HMAC_HashData("MD5", bSecret, True) Then Exit Function
        lLen = GetbSize(bMD5Hash)
        If lLen > 1 Then
            ReDim Preserve bMD5Hash(lLen + UBound(bOutBuffer))
            CopyMemory bMD5Hash(lLen), bOutBuffer(0), UBound(bOutBuffer) + 1
        Else
            bMD5Hash = bOutBuffer
        End If
    Next I%
    'Figure out how many iterations should be performed for SHA1 Hash
    I% = Int(HashLen / 20)
    If HashLen Mod 20 > 0 Then I% = I% + 1 'Adj for division not even
    ReDim bSHA1Hash(0)
    For I% = 1 To I%
        If I% = 1 Then
            bInBuffer = bSeed 'First Hash uses seed
        Else
            bInBuffer = bTmpBuffer
        End If
        If Not HMAC_HashData("SHA1", bSecret) Then Exit Function
        bTmpBuffer = bOutBuffer
        bInBuffer = bOutBuffer
        If Not HMAC_HashData("SHA1", bSecret, True) Then Exit Function
        lLen = GetbSize(bSHA1Hash)
        If lLen > 1 Then
            ReDim Preserve bSHA1Hash(lLen + UBound(bOutBuffer))
            CopyMemory bSHA1Hash(lLen), bOutBuffer(0), UBound(bOutBuffer) + 1
        Else
            bSHA1Hash = bOutBuffer
        End If
    Next I%
    ReDim bOutBuffer(HashLen - 1)
    For I% = 0 To HashLen - 1
        bOutBuffer(I%) = bMD5Hash(I%) Xor bSHA1Hash(I%)
    Next I%
    PRF = True
End Function

Public Property Let Random(sNewValue As String)
    bRandom = StrToByte(sNewValue)
End Property

Public Property Let Secret(sNewValue As String)
    bSecret = StrToByte(sNewValue)
End Property

Private Function StrToByte(strInput As String) As Byte()
    Dim lPntr As Long
    Dim bTmp() As Byte
    Dim bArray() As Byte
    If Len(strInput) = 0 Then Exit Function
    ReDim bTmp(LenB(strInput) - 1) 'Memory length
    ReDim bArray(Len(strInput) - 1) 'String length
    CopyMemory bTmp(0), ByVal StrPtr(strInput), LenB(strInput)
    'Examine every second byte
    For lPntr = 0 To UBound(bArray)
        If bTmp(lPntr * 2 + 1) > 0 Then
            bArray(lPntr) = Asc(Mid$(strInput, lPntr + 1, 1))
        Else
            bArray(lPntr) = bTmp(lPntr * 2)
        End If
    Next lPntr
    StrToByte = bArray
End Function

Public Property Get InBuffer() As String
    InBuffer = ByteToStr(bInBuffer)
End Property

Public Property Let InBuffer(sNewValue As String)
    bInBuffer = StrToByte(sNewValue)
End Property

Public Property Get OutBuffer() As String
    OutBuffer = ByteToStr(bOutBuffer)
End Property

Public Property Let OutBuffer(sNewValue As String)
    bOutBuffer = StrToByte(sNewValue)
End Property

