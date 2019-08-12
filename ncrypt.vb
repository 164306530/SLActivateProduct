Public RSA Key:
52 53 41 31 = Magic = "RSA1" = &H31415352
00 08 00 00 = BitLength = 2048
03 00 00 00 = cbPublicExp length = 3 
00 01 00 00 = cbModulus length = 256
00 00 00 00 = cbPrime1 length = 0
00 00 00 00 = cbPrime2 length = 0
01 00 01 = PublicExponent = 65,537
B2 D7 EB 22 2D 3D 97 D6 DC C9 87 C5 96 C2 68 1E 
FA EB 0F 37 77 C6 B1 64 19 06 50 6A 33 1E A3 0A 
97 A6 67 FC 80 9E 3F 89 84 90 DF 3F 0E C4 75 BA 
65 25 9E 4E DB 48 FF 2F 2D 21 FE B9 13 BA 55 16 
D9 2E 2A 2A 3E DB 27 2C F4 35 96 6D 58 31 8C C2 
8C F9 BE 4E FC E2 B1 C5 16 D9 44 3B B8 F4 0E 1E 
BD A0 8C 0F 08 E7 49 1E F6 21 58 02 B3 09 FF 2E 
D3 62 64 C1 DA 52 3E 8E 21 B4 34 01 97 52 E5 F7 
CF E5 60 7F 8A BD A1 61 84 72 C6 F2 A6 06 E5 1F 
F2 C1 9A 14 83 B2 58 FA CF 3A 4D 38 D0 5D 4E 37 
E1 60 36 78 3E B0 67 70 9C 92 B9 D3 E3 49 47 EE 
88 0D A4 70 91 02 95 08 67 79 9A 4C E4 25 3E E9 
C8 3C F4 83 D4 D7 4A 6A 60 5C DF 56 C3 66 B4 D3 
FC B3 1D 89 B2 7C 1D 07 65 5E B4 5E 02 36 33 B8 
E7 0E 14 EB 77 F1 ED 00 22 89 4D 89 AC 79 9B C0 
B4 6F 41 98 53 EA CA 9A 91 DF 7F DA 94 4A 38 93





Private Const MS_SCHANNEL_PROVIDER As String = "Microsoft SSL Protocol Provider"
Private Const NCRYPT_SSL_CLIENT_FLAG = &H1
Private Const TLS_RSA_WITH_RC4_128_SHA = &H5
Private Const TLS1_PROTOCOL_VERSION = &H301

'Blob types
Private Const BCRYPT_RSAPUBLIC_BLOB As String = "RSAPUBLICBLOB"

Private Type BCRYPT_RSAKEY_BLOB
  magic         As Long
  BitLength     As Long
  cbPublicExp   As Long
  cbModulus     As Long
  cbPrime1      As Long
  cbPrime2      As Long
End Type
'This is just the header, which is followed by the Public Exponent and Modulus
'for a Public key. A Private key also includes the 2 Primes

Private Type RSA_PUBLICKEYBLOB
    pubkey As BCRYPT_RSAKEY_BLOB
    pubexp(2) As Byte
    modulus(255) As Byte
End Type
Private Const RSA_PUBLICKEYBLOBLEN = 283
Private Type RSA_EXP_PUBLICKEYBLOB
    bPublicKey(RSA_PUBLICKEYBLOBLEN - 1) As Byte
End Type

Private Type NCryptBufferDesc
    ulVersion As Long
    cBuffers As Long
    pBuffers As Long
End Type

Private Type NCryptBuffer
    cbBuffer As Long
    BufferType As Long
    pvBuffer As Long
End Type

Private Const NCRYPTBUFFER_SSL_CLIENT_RANDOM As Long = 20
Private Const NCRYPTBUFFER_SSL_SERVER_RANDOM As Long = 21

'CNG API Declares
Private Declare Function SslOpenProvider Lib "ncrypt.dll" (ByRef hSslProvider As Long, ByVal pszProviderName As Long, ByVal dwFlags As Long) As Long
Private Declare Function SslFreeObject Lib "ncrypt.dll" (ByVal hObject As Long, ByVal dwFlags As Long) As Long
Private Declare Function SslFreeBuffer Lib "ncrypt.dll" (ByVal pvBuffer As Long) As Long
Private Declare Function SslImportKey Lib "ncrypt.dll" (ByVal hSslProvider As Long, ByRef phKey As Long, ByVal pszBlobType As Long, ByVal pbKeyBlob As Long, ByVal cbKeyBlob As Long, ByVal dwFlags As Long) As Long
Private Declare Function SslGenerateMasterKey Lib "ncrypt.dll" (ByVal hSslProvider As Long, ByVal hPrivateKey As Long, ByVal hPublicKey As Long, ByRef phMasterKey As Long, ByVal dwProtocol As Long, ByVal dwCipherSuite As Long, ByVal pParameterList As Long, ByVal pbOutput As Long, ByVal cbOutput As Long, ByRef pcbResult As Long, ByVal dwFlags As Long) As Long

'API memory functions
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)

'Constants for Cryptography API error messages
Private Const SOP As String = "SslOpenProvider"
Private Const SIK As String = "SslImportKey"
Private Const SGMK As String = "SslGenerateMasterKey"

'CNG Buffers
Private bPublicKey() As Byte
Private bClientRnd() As Byte
Private bServerRnd() As Byte

Private RSAPubKey As RSA_EXP_PUBLICKEYBLOB

Public Function ExportMasterKey() As Boolean
    Const Routine As String = "clsSSL.CreateMasterKeys"
    Dim hSslProvider As Long
    Dim hPublicKey As Long
    Dim hPrivateKey As Long
    Dim hMasterKey As Long
    Dim dwProtocol As Long
    Dim dwCipherSuite As Long
    Dim pParameterList As NCryptBufferDesc
    Dim pbOutput As Long
    Dim cbOutput As Long
    Dim pcbResult As Long
    Dim dwFlags As Long
    Dim bBuffer() As Byte
    Dim ebBuffer() As Byte
    Dim lRet As Long
    Dim ClientRandom As NCryptBuffer
    Dim ServerRandom As NCryptBuffer
    lRet = SslOpenProvider(hSslProvider, StrPtr(MS_SCHANNEL_PROVIDER), 0)
    If lRet <> 0 Then
        RaiseEvent Error(lRet, SOP, Routine)
        GoTo ReleaseHandles
    End If
    lRet = SslImportKey(hSslProvider, hPublicKey, StrPtr(BCRYPT_RSAPUBLIC_BLOB), VarPtr(RSAPubKey.bPublicKey(0)), GetbSize(RSAPubKey.bPublicKey), 0)
    If lRet <> 0 Then
        RaiseEvent Error(lRet, SIK, Routine)
        GoTo ReleaseHandles
    End If
    dwProtocol = TLS1_PROTOCOL_VERSION '&H301
    dwCipherSuite = TLS_RSA_WITH_RC4_128_SHA '&H5
    dwFlags = NCRYPT_SSL_CLIENT_FLAG '&H1
    ClientRandom.cbBuffer = GetbSize(bClientRnd) '32
    ClientRandom.BufferType = NCRYPTBUFFER_SSL_CLIENT_RANDOM '20
    ClientRandom.pvBuffer = VarPtr(bClientRnd(0))
    ServerRandom.cbBuffer = GetbSize(bServerRnd) '32
    ServerRandom.BufferType = NCRYPTBUFFER_SSL_SERVER_RANDOM '21
    ServerRandom.pvBuffer = VarPtr(bServerRnd(0))
    ReDim bBuffer(23)
    CopyMemory bBuffer(0), ClientRandom.cbBuffer, 12
    CopyMemory bBuffer(12), ServerRandom.cbBuffer, 12
    pParameterList.ulVersion = 0
    pParameterList.cBuffers = 2
    pParameterList.pBuffers = VarPtr(bBuffer(0))
    'First call with pbOutput/cbOutput = 0 returns encrypted key length in pcbResult
    lRet = SslGenerateMasterKey(hSslProvider, hPrivateKey, hPublicKey, hMasterKey, dwProtocol, dwCipherSuite, VarPtr(pParameterList.ulVersion), pbOutput, cbOutput, pcbResult, dwFlags)
    If lRet <> 0 Then
        RaiseEvent Error(lRet, SGMK, Routine)
        GoTo ReleaseHandles
    End If
    'Prepare encryption buffer
    ReDim ebBuffer(pcbResult - 1)
    pbOutput = VarPtr(ebBuffer(0))
    cbOutput = pcbResult
    lRet = SslGenerateMasterKey(hSslProvider, hPrivateKey, hPublicKey, hMasterKey, dwProtocol, dwCipherSuite, VarPtr(pParameterList.ulVersion), pbOutput, cbOutput, pcbResult, dwFlags)
    If lRet <> 0 Then
        RaiseEvent Error(lRet, SGMK, Routine)
        GoTo ReleaseHandles
    End If
ReleaseHandles:
    SslFreeObject hSslProvider, 0
End Function

Private Function GetbSize(bArray() As Byte) As Long
    On Error GoTo GetSizeErr
    GetbSize = UBound(bArray) + 1
    Exit Function
GetSizeErr:
    GetbSize = 0
End Function
