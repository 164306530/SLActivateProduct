# SLActivateProduct

看看激活过程系统做了些什么东西

hResult = SLActivateProduct(hSLC, bSkuId, null, null, null, null, 0);

![image](https://github.com/laomms/SLActivateProduct/blob/master/22.png)

关联API及函数:

weibio.dll

WINHTTP.DLL    WinHttpCrackUrl   WinHttpOpen inHttpGetDefaultProxyConfiguration WinHttpSetTimeouts  WinHttpConnect WinHttpOpenRequest  WinHttpCreateUrl  WinHttpSetOption  WinHttpGetIEProxyConfigForCurrentUser
               WinHttpGetProxyForUrl  WinHttpCrackUrl  WinHttpCloseHandle  WinHttpSendRequest  WinHttpAddRequestHeaders   WinHttpCreateUrl   WinHttpSetStatusCallback  WinHttpGetProxyForUrlEx2  WinHttpFreeProxyResultEx
               WinHttpReceiveResponse  WinHttpQueryHeaders  WinHttpReadData  

sppcext.dll
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
