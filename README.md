# SLActivateProduct

看看激活过程系统做了些什么东西

hResult = SLActivateProduct(hSLC, bSkuId, null, null, null, null, 0);

![image](https://github.com/laomms/SLActivateProduct/blob/master/00.png)

关联API及函数:


WINHTTP.DLL    WinHttpCrackUrl   WinHttpOpen inHttpGetDefaultProxyConfiguration WinHttpSetTimeouts  WinHttpConnect WinHttpOpenRequest  WinHttpCreateUrl  WinHttpSetOption  WinHttpGetIEProxyConfigForCurrentUser
               WinHttpGetProxyForUrl  WinHttpCrackUrl  WinHttpCloseHandle  WinHttpSendRequest  WinHttpAddRequestHeaders   WinHttpCreateUrl   WinHttpSetStatusCallback  WinHttpGetProxyForUrlEx2  WinHttpFreeProxyResultEx
               WinHttpReceiveResponse  WinHttpQueryHeaders  WinHttpReadData  



大致应该是这样(密钥激活过程):加密密钥及硬件等信息，利用httprequest post这些信息到指定网址,如果错误返回错误代码,如果正确返回合法licenseID. 将这些信息存储到SSL Store.Windows调用一系列算法如果该license对应的各种信息是合法就激活系统。

经过拦截WinHttpOpen找到sppcext.dll中的调用加密密钥数据后调用httprequest的关键部分：

```c
int __fastcall GetEncryptKey(int hSLCs, SLID *pAppIDs, int a3)
{
  char *v3; // esi
  void *v4; // ecx
  char *v5; // edi
  int hSLpSetActivationInProgress; // ebx
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int hRes; // eax
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
  SLID *pAppId; // [esp+38h] [ebp-4h]
  int savedregs; // [esp+3Ch] [ebp+0h]

  hslc = hSLCs;
  v3 = 0;
  v16 = 0;
  v4 = *(void **)(a3 + 12);
  v5 = 0;
  v15 = 0;
  int_1 = 0;
  pAppId = pAppIDs;
  v19 = 0;
  v20 = 0;
  hSLpSetActivationInProgress = sub_55C06B08(v4, &v18);
  if ( hSLpSetActivationInProgress < 0 )
    goto LABEL_2;
  v7 = GetProductSkuInformation(hslc, (int)pAppId, &a3a);
  hSLpSetActivationInProgress = v7;
  if ( v7 < 0 )
  {
    sub_55C08E2B(v7);
    sub_55C21625(dword_55BEF908, &unk_55C4C738);
    goto LABEL_22;
  }
  if ( !a3a )
  {
    if ( v18 )
      goto LABEL_22;
    hSLpSetActivationInProgress = SLpSetActivationInProgress(hslc, pAppId);
    if ( hSLpSetActivationInProgress >= 0 )
    {
      int_1 = 1;
      hRes = geterrercode((int)pAppId, hslc, (int)&savedregs, 0, 0, a3);
      hSLpSetActivationInProgress = hRes;
      if ( hRes >= 0 )
        goto LABEL_21;
      sub_55C08E2B(hRes);
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
    hSLpSetActivationInProgress = SLSetGenuineInformation(
                                    pAppId,
                                    L"SL_ACTIVATION_VALIDATION_IN_PROGRESS",
                                    SL_DATA_DWORD,
                                    4u,
                                    pbValue);
    if ( hSLpSetActivationInProgress >= 0 )
      goto LABEL_11;
LABEL_2:
    sub_55C08E2B(hSLpSetActivationInProgress);
    goto LABEL_22;
  }
  hSLpSetActivationInProgress = SLpSetActivationInProgress(hslc, pAppId);
  sub_55C20DA2(&dword_55C022C0, &unk_55C4C4D0);
  if ( hSLpSetActivationInProgress < 0 )
    goto LABEL_2;
  int_1 = 1;
  v8 = sub_55C0AB42(hslc, pAppId, a3);
  hSLpSetActivationInProgress = v8;
  if ( v8 >= 0 )
  {
LABEL_11:
    hSLpSetActivationInProgress = sub_55C0AD04(&v19, &v20);
    if ( hSLpSetActivationInProgress < 0
      || (hSLpSetActivationInProgress = SLOpen(&v16), hSLpSetActivationInProgress < 0) )
    {
      sub_55C08E2B(hSLpSetActivationInProgress);
      v3 = v19;
      v5 = v20;
    }
    else
    {
      v5 = v20;
      v3 = v19;
      v9 = sub_55C1ED09(v19, v20, 0, pAppId, v18 == 0 ? a3 : 0, 1, &v15, &v12);
      hSLpSetActivationInProgress = v9;
      if ( v9 < 0 )
        sub_55C08E2B(v9);
    }
    goto LABEL_20;
  }
  sub_55C08E2B(v8);
LABEL_21:
  SLpClearActivationInProgress(hslc, pAppId);
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

![image](https://github.com/laomms/SLActivateProduct/blob/master/33.png)
![image](https://github.com/laomms/SLActivateProduct/blob/master/44.png)
