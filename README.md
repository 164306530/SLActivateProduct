# SLActivateProduct

看看激活过程系统做了些什么东西

hResult = SLActivateProduct(hSLC, bSkuId, null, null, null, null, 0);

![image](https://github.com/laomms/SLActivateProduct/blob/master/00.png)
![image](https://github.com/laomms/SLActivateProduct/blob/master/33.png)
![image](https://github.com/laomms/SLActivateProduct/blob/master/44.png)

关联API及函数:


WINHTTP.DLL    WinHttpCrackUrl   WinHttpOpen inHttpGetDefaultProxyConfiguration WinHttpSetTimeouts  WinHttpConnect WinHttpOpenRequest  WinHttpCreateUrl  WinHttpSetOption  WinHttpGetIEProxyConfigForCurrentUser
               WinHttpGetProxyForUrl  WinHttpCrackUrl  WinHttpCloseHandle  WinHttpSendRequest  WinHttpAddRequestHeaders   WinHttpCreateUrl   WinHttpSetStatusCallback  WinHttpGetProxyForUrlEx2  WinHttpFreeProxyResultEx
               WinHttpReceiveResponse  WinHttpQueryHeaders  WinHttpReadData  



大致应该是这样(密钥激活过程):加密密钥及硬件等信息，利用httprequest post这些信息到指定网址,如果错误返回错误代码,如果正确返回合法licenseID. 将这些信息存储到SSL Store.Windows调用一系列算法如果该license对应的各种信息是合法就激活系统。

经过拦截WinHttpOpen找到sppcext.dll中的调用加密密钥数据后调用httprequest的关键部分：

```c
void *__fastcall GetEncryptKey(int hSLCs, SLID *pSKUId, int ActivationInfo)
{
  char *v3; // esi
  void *v4; // ecx
  char *v5; // edi
  void *hSLpSetActivationInProgress; // ebx
  void *hGetProductSku; // eax
  void *v8; // eax
  void *v9; // eax
  void *hErrorcode; // eax
  char v12; // [esp+10h] [ebp-2Ch]
  BYTE pbValue[4]; // [esp+14h] [ebp-28h]
  int a3a; // [esp+18h] [ebp-24h]
  int v15; // [esp+1Ch] [ebp-20h]
  int v16; // [esp+20h] [ebp-1Ch]
  int int_1; // [esp+24h] [ebp-18h]
  int v18; // [esp+28h] [ebp-14h]
  char *v19; // [esp+2Ch] [ebp-10h]
  char *v20; // [esp+30h] [ebp-Ch]
  int hslc; // [esp+34h] [ebp-8h]
  SLID *pSKUID; // [esp+38h] [ebp-4h]
  int savedregs; // [esp+3Ch] [ebp+0h]

  hslc = hSLCs;
  v3 = 0;
  v16 = 0;
  v4 = *(void **)(ActivationInfo + 12);
  v5 = 0;
  v15 = 0;
  int_1 = 0;
  pSKUID = pSKUId;
  v19 = 0;
  v20 = 0;
  hSLpSetActivationInProgress = (void *)sub_55C06B08(v4, &v18);
  if ( (signed int)hSLpSetActivationInProgress < 0 )
    goto LABEL_2;
  hGetProductSku = (void *)GetProductSkuInformation(hslc, (int)pSKUID, &a3a);
  hSLpSetActivationInProgress = hGetProductSku;
  if ( (signed int)hGetProductSku < 0 )
  {
    sub_55C08E2B(hGetProductSku);
    sub_55C21625(dword_55BEF908, &unk_55C4C738);
    goto LABEL_22;
  }
  if ( !a3a )
  {
    if ( v18 )
      goto LABEL_22;
    hSLpSetActivationInProgress = (void *)SLpSetActivationInProgress(hslc, pSKUID);
    if ( (signed int)hSLpSetActivationInProgress >= 0 )
    {
      int_1 = 1;
      hErrorcode = (void *)geterrercode((int)pSKUID, hslc, (int)&savedregs, 0, 0, ActivationInfo);
      hSLpSetActivationInProgress = hErrorcode;
      if ( (signed int)hErrorcode >= 0 )
        goto LABEL_21;
      sub_55C08E2B(hErrorcode);
      sub_55C21348(&dword_55C03228, &unk_55C4BC00);
LABEL_20:
      if ( !int_1 )
        goto LABEL_22;
      goto LABEL_21;
    }
    goto LABEL_2;
  }
  if ( v18 )
  {
    *(_DWORD *)pbValue = 1;
    hSLpSetActivationInProgress = (void *)SLSetGenuineInformation(
                                            pSKUID,
                                            L"SL_ACTIVATION_VALIDATION_IN_PROGRESS",
                                            SL_DATA_DWORD,
                                            4u,
                                            pbValue);
    if ( (signed int)hSLpSetActivationInProgress >= 0 )
      goto LABEL_11;
LABEL_2:
    sub_55C08E2B(hSLpSetActivationInProgress);
    goto LABEL_22;
  }
  hSLpSetActivationInProgress = (void *)SLpSetActivationInProgress(hslc, pSKUID);
  sub_55C20DA2(&dword_55C022C0, &unk_55C4C4D0);
  if ( (signed int)hSLpSetActivationInProgress < 0 )
    goto LABEL_2;
  int_1 = 1;
  v8 = (void *)sub_55C0AB42(hslc, pSKUID, ActivationInfo);
  hSLpSetActivationInProgress = v8;
  if ( (signed int)v8 >= 0 )
  {
LABEL_11:
    hSLpSetActivationInProgress = (void *)sub_55C0AD04(&v19, &v20);
    if ( (signed int)hSLpSetActivationInProgress < 0
      || (hSLpSetActivationInProgress = (void *)SLOpen(&v16), (signed int)hSLpSetActivationInProgress < 0) )
    {
      sub_55C08E2B(hSLpSetActivationInProgress);
      v3 = v19;
      v5 = v20;
    }
    else
    {
      v5 = v20;
      v3 = v19;
      v9 = (void *)sub_55C1ED09(v19, v20, 0, pSKUID, v18 == 0 ? ActivationInfo : 0, 1, &v15, &v12);
      hSLpSetActivationInProgress = v9;
      if ( (signed int)v9 < 0 )
        sub_55C08E2B(v9);
    }
    goto LABEL_20;
  }
  sub_55C08E2B(v8);
LABEL_21:
  SLpClearActivationInProgress(hslc, pSKUID);
LABEL_22:
  sub_55C08E58(hSLpSetActivationInProgress);
  sub_55C0B09C(&v15);
  if ( v5 )
  {
    sub_55C08F07(v5);
    sub_55C2107D(&dword_55C0371C, &unk_55C4B99C);
  }
  if ( v3 )
    sub_55C08F07(v3);
  sub_55C0B049(&v16);
  return hSLpSetActivationInProgress;
}
```
主要就一处,只要从外部找到这个函数(因为不是输出函数,只能通过基地址加函数入口地址的偏移量定位),直接就可以调用这个函数获取错误代码:
```c
 hErrorcode = (void *)geterrercode((int)pSKUID, hslc, (int)&savedregs, 0, 0, ActivationInfo);
 ```
以32位的10.0.18362.1为例,比如dll的入口地址为0x10000000,该函数的地址为0x1002A791‬,偏移量为0x2A791.如果不会算可以找个已有的输出函数做为中间值计算.
```c#
       public enum SL_ACTIVATION_TYPE
        {
            SL_ACTIVATION_TYPE_DEFAULT,
            SL_ACTIVATION_TYPE_ACTIVE_DIRECTORY
        }
        public struct SL_ACTIVATION_INFO_HEADER
        {
            public uint cbSize;
            public SL_ACTIVATION_TYPE type;
        }

        public struct SL_AD_ACTIVATION_INFO
        {
            public SL_ACTIVATION_INFO_HEADER header;
            public string pwszProductKey;
            public string pwszActivationObjectName;
        }
 [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
 private delegate int GetErrerCode(byte[] pProductSkuId, IntPtr hSLC, IntPtr unknown, int unk1, int unk2, SL_ACTIVATION_INFO_HEADER pActivationInfo);

    RetID = PidGenX(Keys, pkeyfilePath, "XXXXX", 0, PID, DPID3, DPID4);
    if (RetID == 0)
            {

                DigitalProductId3 pid3 = (DigitalProductId3)Marshal.PtrToStructure(DPID3, typeof(DigitalProductId3));
                DigitalProductId4 pid4 = (DigitalProductId4)Marshal.PtrToStructure(DPID4, typeof(DigitalProductId4));
                string szActivationId = Encoding.Unicode.GetString(pid4.szActivationId).Replace("\0", "");
                Guid GuidSkuId = new Guid(szActivationId);
                IntPtr hSLC = new IntPtr();
                int hResult = SLOpen(ref hSLC);
                if (hResult == 0)
                {
                    hResult = SLpSetActivationInProgress( hSLC, GuidSkuId.ToByteArray());
                    if (hResult==0)
                    {
                        IntPtr pDll = LoadLibrary("sppcext.dll");
                        if (pDll != IntPtr.Zero)
                        {
                            var hMod = GetModuleHandle("sppcext");
                            if (hMod == IntPtr.Zero)
                            {
                                Console.WriteLine(Marshal.GetLastWin32Error());
                            }
                            var pAddressHwidGetCurrentEx = hMod + 0x2A791;
                            GetErrerCode GetErrerCodeFunc = (GetErrerCode)Marshal.GetDelegateForFunctionPointer(pAddressHwidGetCurrentEx, typeof(GetErrerCode));
                            SL_ACTIVATION_INFO_HEADER pActInfo = new SL_ACTIVATION_INFO_HEADER();
                            IntPtr Values = Marshal.AllocHGlobal(128);
                            var hErrorCode = GetErrerCodeFunc(GuidSkuId.ToByteArray(), hSLC, Values, 0, 0, pActInfo);
                            if (hErrorCode != 0)
                            {
                                Console.WriteLine(hResult.ToString());
                            }
                            else
                            {
                                Console.WriteLine("在线密钥");
                            }
                            bool hFree = FreeLibrary(pDll);
                            Marshal.FreeHGlobal(Values);
                        }
                    }              
                    hResult = SLpClearActivationInProgress(hSLC, GuidSkuId.ToByteArray());                   
                }
            }
        }

```     
