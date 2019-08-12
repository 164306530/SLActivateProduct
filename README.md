# SLActivateProduct

看看激活过程系统做了些什么东西

hResult = SLActivateProduct(hSLC, bSkuId, null, null, null, null, 0);

![image](https://github.com/laomms/SLActivateProduct/blob/master/00.png)

关联API及函数:

weibio.dll

WINHTTP.DLL    WinHttpCrackUrl   WinHttpOpen inHttpGetDefaultProxyConfiguration WinHttpSetTimeouts  WinHttpConnect WinHttpOpenRequest  WinHttpCreateUrl  WinHttpSetOption  WinHttpGetIEProxyConfigForCurrentUser
               WinHttpGetProxyForUrl  WinHttpCrackUrl  WinHttpCloseHandle  WinHttpSendRequest  WinHttpAddRequestHeaders   WinHttpCreateUrl   WinHttpSetStatusCallback  WinHttpGetProxyForUrlEx2  WinHttpFreeProxyResultEx
               WinHttpReceiveResponse  WinHttpQueryHeaders  WinHttpReadData  

sppcext.dll    SLActivateProduct

WINSCard.dll

msxml3.dll/msxml6.dll            DllGetClassObject   DllUnregisterServer 

dhcpcsvc6.dll

dhcpcsvc.dll

schannel.dll    SpUserModeInitialize

ncrypt.dll     SslOpenProvider  SslIncrementProviderReferenceCount   SslImportKey  SslLookupCipherSuiteInfo  SslLookupCipherLengths  SslEncryptPacket  SslDecrementProviderReferenceCount SslFreeObject

bcryptprimitives.dll    GetHashInterface  GetCipherInterface 

userrenv.dll

gpapi.dll


sspicli.dll    EnumerateSecurityPackagesW   LsaFreeReturnBuffer   LsaFreeReturnBuffer FreeContextBuffer AcquireCredentialsHandleW   InitializeSecurityContextW   QueryContextAttributesExW  SealMessage FreeContextBuffer  DeleteSecurityContext 
               FreeCredentialsHandle 

credssp.dll

secur32.dll

rasadhlp.dll

mskeyprotect.dll

ntasn1.dll

ncryptsslp.dll

dpapi.dll

FWPUCLNT.DLL

crypt32.dll     I_CryptAllocTlsEx   I_CryptAllocTlsEx  CertOpenStore CertAddEncodedCertificateToStore  CryptDecodeObjectEx  CryptEnumOIDFunction I_CryptGetAsn1Decoder  CertAddEncodedCertificateToStore CertFreeCertificateContext 
                CertCloseStore CryptFindOIDInfo CryptEnumOIDFunction  CryptMemFree   CryptHashCertificate2  CertFreeCertificateContext CertOpenStore  CertAddEncodedCertificateToStore  CertSetCertificateContextProperty CertGetCertificateChain
                CertGetCertificateContextProperty CryptMemFree CertOpenStore CryptEnumOIDFunction I_CryptSetTls CertAddStoreToCollection CertFindCertificateInStore  CertAddSerializedElementToStore  CertDuplicateCertificateContext  
                CertVerifyCertificateChainPolicy  CryptGetOIDFunctionAddress CryptEnumOIDFunction CertVerifyCertificateChainPolicy CertFindExtension  I_CryptCreateLruCache  
                
ws2_32.dll  WSAStartup WahCreateHandleContextTable WahOpenApcHelper  socket WSASocketW WahCreateHandleContextTable WahInsertHandleContext setsockopt WahReferenceContextByHandle WSAIoctl WahReferenceContextByHandle  WSAIoctl closesocket
            WahReferenceContextByHandle WSACreateEvent  GetAddrInfoExW  WSALookupServiceBeginW  WSALookupServiceEnd ntohs  WSALookupServiceEnd   GetAddrInfoExOverlappedResult  FreeAddrInfoExW setsockopt bind getsockopt  WSCEnumProtocols
            WSCEnumProtocolsEx  WSCEnumProtocols WSCEnumProtocolsEx WSACloseEvent getpeername WSARecv WSASend 
            
nsi.dll   NsiGetAllParameters NsiAllocateAndGetTable  NsiGetAllParametersEx NsiFreeTable  NsiGetParameter NsiGetAllParameters 

大致应该是这样(密钥激活过程):加密密钥及硬件等信息，利用httprequest post这些信息到指定网址,如果错误返回错误代码,如果正确返回合法licenseID. 将这些信息存储到SSL Store.Windows调用一系列算法如果该license对应的各种信息是合法就激活系统。如果利用pidgenx.dll解码出密钥SKUID,然后经过某些API算出加密后的密钥数据(加密后的硬件信息可以固定为某值),然后直接POST这些数据到指定的网址,应该就可以得到错误代码而达到检测密钥的效果,省略了安装激活过程.

![image](https://github.com/laomms/SLActivateProduct/blob/master/33.png)
![image](https://github.com/laomms/SLActivateProduct/blob/master/44.png)
