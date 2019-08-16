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

经过拦截WinHttpOpen找到sppcext.dll中的调用加密密钥数据后调用httprequest的关键部分,这样可以不通过安装密钥的模式直接通过sppcext.dll获取错误代码.
```asm
.text:572CCD4B lea     eax, [ebp-0ACh]
.text:572CCD51 mov     edx, esi                        ; pSKUId
.text:572CCD53 push    eax                             ; ActivationInfo
.text:572CCD54 mov     ecx, ebx                        ; hSLCs
.text:572CCD56 call    GetEncryptKey                   ; 第一层
.text:572CCD5B ; 232:         *(_DWORD *)Data = hGet;
.text:572CCD5B mov     [ebp-70h], eax


text:572CAFC1 push    [ebp+ActivationInfo]            ; ActivationInfo
.text:572CAFC4 mov     edx, [ebp+pSKUID]               ; skuid
.text:572CAFC7 mov     ecx, [ebp+hslc]                 ; hSlc
.text:572CAFCA ; 51:       int_1 = 1;
.text:572CAFCA mov     [ebp+int_1], 1
.text:572CAFD1 call    geterrercode                    ; 第二层
.text:572CAFD6 ; 53:       hSLpSetActivationInProgress = hErrorcode;
.text:572CAFD6 mov     ebx, eax

.text:572CA8AF push    eax
.text:572CA8B0 call    GetResult                       ; 第三层
.text:572CA8B5 mov     esi, eax

.text:572CA125 push    [ebp+lpMem]                     ; int
.text:572CA128 lea     edx, [esi+64h]
.text:572CA12B push    [ebp+var_C]                     ; int
.text:572CA12E push    eax                             ; psz
.text:572CA12F push    ecx                             ; int
.text:572CA130 push    edx                             ; int
.text:572CA131 mov     ecx, esi
.text:572CA133 call    GetRes                          ; 第四层
.text:572CA138 mov     [esi+60h], eax
.text:572CA13B ; 107:     sub_572C8E58(0);
.text:572CA13B xor     ecx, ecx
```

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
 hErrorcode = (void *)geterrercode(hslc,(int)pSKUID, (int)&savedregs, 0, 0, ActivationInfo);
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
 private delegate int GetErrerCode(IntPtr hSLC, byte[] pProductSkuId,  IntPtr unknown, int unk1, int unk2, SL_ACTIVATION_INFO_HEADER pActivationInfo);
//第三个参数具体不详,可能会引起内存写入异常
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
                    hResult = SLpSetActivationInProgress( hSLC, GuidSkuId.ToByteArray()); //判断是否有其他激活进程
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
                            var pGetErrerCode = hMod + 0x2A791;
                            GetErrerCode GetErrerCodeFunc = (GetErrerCode)Marshal.GetDelegateForFunctionPointer(pGetErrerCode, typeof(GetErrerCode));
                            IntPtr Values = Marshal.AllocHGlobal(128);
                            var hErrorCode = GetErrerCodeFunc(hSLC, GuidSkuId.ToByteArray(), Values, 0, 0, pActInfo);
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

64位dll:
```asm
.text:00007FF9B03DD380 lea     r8, [rsp+180h+ptr]              ; ptr
.text:00007FF9B03DD385 mov     rdx, r14                        ; pProductSkuId
.text:00007FF9B03DD388 mov     rcx, r15                        ; hSLC
.text:00007FF9B03DD38B call    GetResult                       ; 第一层
.text:00007FF9B03DD390 ; 290:       hrCode = hRes;
.text:00007FF9B03DD390 mov     [rsp+180h+hrCode], eax
 hRes = GetResult(hSLC, pProductSkuId, (__int64)&ptr);// 第一层
 
 .text:00007FF9B03DAC43 mov     r8, r13                         ; activateinfo
.text:00007FF9B03DAC46 ; 77:     v36 = 1;
.text:00007FF9B03DAC46 mov     [rbp+arg_10], 1
.text:00007FF9B03DAC4D mov     rdx, r14                        ; SKUID
.text:00007FF9B03DAC50 mov     rcx, r15                        ; hSLC
.text:00007FF9B03DAC53 call    GetRes                          ; 第二层
  hResult = GetRes(SLC, SKUID, intptr);       // 第二层
  
  .text:00007FF9B03DA33C mov     rax, [rbp+30h+var_B0]
.text:00007FF9B03DA340 lea     rcx, [rsi+28h]                  ; slc
.text:00007FF9B03DA344 ; 76:       Dst = v19;
.text:00007FF9B03DA344 mov     [rbp+30h+Dst], rax
.text:00007FF9B03DA348 lea     r8, [rbp+30h+Dst]               ; a3
.text:00007FF9B03DA34C mov     rax, [rbp+30h+var_A0]
.text:00007FF9B03DA350 mov     rdx, r14                        ; skuid
.text:00007FF9B03DA353 ; 77:       v27 = v20;
.text:00007FF9B03DA353 mov     [rbp+30h+var_38], rax
.text:00007FF9B03DA357 ; 78:       v28 = v21;
.text:00007FF9B03DA357 mov     eax, [rbp+30h+var_98]
.text:00007FF9B03DA35A mov     [rbp+30h+var_30], eax
.text:00007FF9B03DA35D call    activateinfo                    ; 第三层
errorcode = ::activateinfo((_DWORD *)pActivateinfo + 10, slc, (__int64)&Dst);

.text:00007FF9B03D9829 loc_7FF9B03D9829:                       ; CODE XREF: activateinfo+21A↑j
.text:00007FF9B03D9829 test    rax, rax
.text:00007FF9B03D982C mov     r8d, r12d
.text:00007FF9B03D982F ; 159:     if ( v17 )
.text:00007FF9B03D982F cmovnz  r9, rax
.text:00007FF9B03D9833 mov     rax, [r13+58h]
.text:00007FF9B03D9837 mov     edx, [rax+0Ch]
.text:00007FF9B03D983A call    Get                             ; 第四层
Get(v14, *(unsigned int *)(*(_QWORD *)(v4 + 88) + 12i64), (unsigned int)RESULTS, v16, v6);// 第四层
```c
