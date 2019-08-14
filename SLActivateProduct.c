__int64 __fastcall SLActivateProduct(__int64 SLC, __int64 ProductSkuId, __int64 cbAppSpecificData, __int64 pvAppSpecificData, _DWORD *pActivationInfo, __int64 pwszProxyServer, __int16 wProxyPort)
{
  int V_0; // er12
  __int64 pProductSkuId; // r14
  __int64 hSLC; // r15
  __int64 hGetTick; // rax
  int int_0; // edi
  int v12; // eax
  int v13; // er13
  __int64 v14; // rcx
  __int64 v15; // rdx
  unsigned int v16; // eax
  bool v17; // sf
  int hgETSLIDLIST; // eax
  int v19; // ecx
  int v20; // esi
  signed int v21; // eax
  __int64 v22; // rdx
  __int64 v23; // rcx
  wchar_t *v24; // rbx
  unsigned int v25; // edi
  __int64 v26; // rax
  __int128 *QueryIdType; // rdx
  signed int v28; // eax
  unsigned int lpDatas; // ebx
  unsigned int v30; // ebx
  signed int hSLgetSLIDList; // eax
  unsigned int v32; // ebx
  __int64 v33; // rcx
  __int64 v34; // rdx
  __int64 v35; // r8
  int v36; // ecx
  __int64 v37; // r8
  unsigned int v38; // ebx
  __int64 v39; // rcx
  signed int hSLIDList; // eax
  unsigned int v41; // ebx
  __int64 v42; // rcx
  unsigned int v43; // ecx
  __int64 v44; // rdx
  __int64 v45; // rcx
  char *v46; // rbx
  unsigned int hResult; // edi
  __int64 v48; // rax
  __int64 v49; // rbx
  __int64 v50; // rax
  __int64 v51; // rbx
  __int64 v52; // rax
  __int64 v53; // rbx
  __int64 v54; // rax
  __int64 hMem; // rdx
  unsigned int v57; // [rsp+30h] [rbp-D0h]
  unsigned int lpData; // [rsp+34h] [rbp-CCh]
  int v59; // [rsp+38h] [rbp-C8h]
  int v60; // [rsp+3Ch] [rbp-C4h]
  int v61; // [rsp+40h] [rbp-C0h]
  __m128i *PHKEY; // [rsp+48h] [rbp-B8h]
  __int64 ppReturnIds; // [rsp+50h] [rbp-B0h]
  __int128 *eQueryIdType; // [rsp+58h] [rbp-A8h]
  int v65; // [rsp+60h] [rbp-A0h]
  int lpcbData; // [rsp+64h] [rbp-9Ch]
  char pnReturnIds; // [rsp+68h] [rbp-98h]
  _DWORD *ptr; // [rsp+70h] [rbp-90h]
  __int64 v69; // [rsp+78h] [rbp-88h]
  __int16 v70; // [rsp+80h] [rbp-80h]
  void *Buf1; // [rsp+88h] [rbp-78h]
  __int64 *v72; // [rsp+90h] [rbp-70h]
  int int0; // [rsp+98h] [rbp-68h]
  __int64 eQueryIdTypes; // [rsp+A0h] [rbp-60h]
  __int64 v75; // [rsp+A8h] [rbp-58h]
  __int128 mem_addrs; // [rsp+B0h] [rbp-50h]
  __int64 v77; // [rsp+C0h] [rbp-40h]
  int V_1; // [rsp+C8h] [rbp-38h]
  int dword_0; // [rsp+CCh] [rbp-34h]
  char lpType; // [rsp+D0h] [rbp-30h]
  char eReturnIdType; // [rsp+D4h] [rbp-2Ch]
  char lpSystemTimeAsFileTime; // [rsp+D8h] [rbp-28h]
  __int128 mem_addr; // [rsp+E0h] [rbp-20h]
  __int128 v84; // [rsp+F0h] [rbp-10h]
  unsigned int *v85; // [rsp+120h] [rbp+20h]
  __int64 v86; // [rsp+128h] [rbp+28h]
  int *v87; // [rsp+130h] [rbp+30h]
  __int64 v88; // [rsp+138h] [rbp+38h]

  V_0 = 0;
  eQueryIdType = 0i64;
  pProductSkuId = ProductSkuId;
  ppReturnIds = 0i64;
  hSLC = SLC;
  eQueryIdTypes = 0i64;
  dword_0 = 0;
  _mm_storeu_si128((__m128i *)&mem_addrs, (__m128i)0i64);
  v77 = 0i64;
  hGetTick = GetTickCount64(SLC, ProductSkuId, cbAppSpecificData, pvAppSpecificData);
  V_1 = -1;
  v75 = hGetTick;
  PHKEY = 0i64;
  int_0 = 0;
  if ( !(unsigned int)RegOpenKeyExW(0xFFFFFFFF80000002i64, L"SYSTEM\\Setup", 0i64, 0x20019i64, &PHKEY) )
  {
    lpcbData = 4;
    if ( !(unsigned int)RegQueryValueExW(PHKEY, L"OOBEInProgress", 0i64, &lpType, &lpData, &lpcbData) )
      LOBYTE(int_0) = lpData == 1;
  }
  sub_7FFC9A7F7F8C(0);
  if ( PHKEY )
    RegCloseKey();
  v12 = V_1;
  if ( int_0 )
    v12 = 0;
  V_1 = v12;
  sub_7FFC9A7F7F8C(0);
  memset(&ptr, 0, 0x30ui64);
  v59 = 0;
  v13 = 0;
  VertifySum((unsigned int *)&unk_7FFC9A85F360, (unsigned int *)&unk_7FFC9A86C078);
  v65 = 0;
  if ( !hSLC || !pProductSkuId )
    goto LABEL_9;
  v70 = wProxyPort;
  v72 = &eQueryIdTypes;
  ptr = pActivationInfo;
  v69 = pwszProxyServer;
  int0 = 0;
  if ( pActivationInfo )
  {
    if ( *pActivationInfo < 8u )
    {
LABEL_9:
      v14 = 2147942487i64;
LABEL_10:
      v57 = v14;
LABEL_11:
      sub_7FFC9A7F7F24(v14);
      goto LABEL_91;
    }
    if ( pActivationInfo[1] != 1 )
    {
      sub_7FFC9A817294(&unk_7FFC9A85F538, &unk_7FFC9A86C1A0);
      goto LABEL_9;
    }
    v16 = GetProductSkuInformation(hSLC, pProductSkuId, (__int64)&ptr);
    goto LABEL_18;
  }
  hgETSLIDLIST = SLGetSLIDList(hSLC, 1i64, pProductSkuId);
  v19 = v60;
  v20 = hgETSLIDLIST;
  if ( hgETSLIDLIST < 0 )
    v19 = 0;
  v60 = v19;
  v21 = GetPKeyInformation(hSLC, pProductSkuId, (__int64 *)&Buf1);
  v24 = (wchar_t *)Buf1;
  v25 = v21;
  if ( v21 < 0 && Buf1 )
  {
    v26 = GetProcessHeap(v23, v22);
    HeapFree(v26, 0i64, v24 - 2);
    sub_7FFC9A7F7F8C(0);
    v24 = 0i64;
    Buf1 = 0i64;
  }
  Vertify_Sum((unsigned int *)&unk_7FFC9A860438, (unsigned int *)&unk_7FFC9A86CEC8);
  QueryIdType = &xmmword_7FFC9A84F628;
  if ( v60 )
    QueryIdType = eQueryIdType;
  sub_7FFC9A7F5404((__int64)&eQueryIdTypes, (__int64)QueryIdType, pProductSkuId, v24, 0ui64);
  v57 = v25;
  if ( (v25 & 0x80000000) != 0 )
  {
    sub_7FFC9A7F7F24(v25);
    goto LABEL_91;
  }
  if ( Buf1 )
  {
    v28 = sub_7FFC9A7F567C(Buf1, L"Volume:GVLK", &lpData);
    lpDatas = lpData;
  }
  else
  {
    lpDatas = 0;
    sub_7FFC9A7F7F8C(0);
    v28 = 0;
  }
  v57 = v28;
  if ( v28 < 0 )
    goto LABEL_34;
  if ( !lpDatas )
  {
    if ( Buf1 )
    {
      v28 = sub_7FFC9A7F567C(Buf1, L"VT:IA", &lpData);
      v30 = lpData;
    }
    else
    {
      v30 = 0;
      sub_7FFC9A7F7F8C(0);
      v28 = 0;
    }
    v57 = v28;
    if ( v28 < 0 )
      goto LABEL_34;
    if ( v30 )
    {
      V_0 = 1;
      v16 = SLpIAActivateProduct(hSLC, pProductSkuId);
      goto LABEL_18;
    }
    PHKEY = 0i64;
    hSLgetSLIDList = SLGetSLIDList(hSLC, 1i64, pProductSkuId);
    v32 = hSLgetSLIDList;
    if ( hSLgetSLIDList == -1073418222 )
    {
      v32 = -1073418220;
    }
    else if ( hSLgetSLIDList >= 0 )
    {
      if ( lpData > 0 )
      {
        _mm_storeu_si128((__m128i *)&mem_addr, *PHKEY);
        goto LABEL_51;
      }
      v32 = -2147467259;
      v33 = 2147500037i64;
LABEL_47:
      sub_7FFC9A7F7F24(v33);
LABEL_51:
      sub_7FFC9A7F7F8C(v32);
      sub_7FFC9A802B14(&PHKEY);
      v57 = v32;
      if ( (v32 & 0x80000000) != 0 )
      {
        v14 = v32;
        goto LABEL_11;
      }
      v13 = 1;
      if ( v20 >= 0
        && v60 == 1
        && *(_QWORD *)eQueryIdType == 5580477268562093876i64
        && *((_QWORD *)eQueryIdType + 1) == -6988154782983242088i64 )
      {
        if ( ppReturnIds )
          LocalFree(ppReturnIds, v34);
        if ( (unsigned int)SLGetProductSkuInformation(
                             hSLC,
                             pProductSkuId,
                             L"DependsOn",
                             0i64,
                             &pnReturnIds,
                             &ppReturnIds) == -1073418222 )
        {
          v28 = sub_7FFC9A7FCA68(&v59);
          v57 = v28;
          if ( (unsigned int)dword_7FFC9A86B000 > 5
            && qword_7FFC9A86B010 & 0x400000000000i64
            && (qword_7FFC9A86B018 & 0x400000000000i64) == qword_7FFC9A86B018 )
          {
            v85 = &v57;
            v87 = &v59;
            v86 = 4i64;
            v88 = 4i64;
            sub_7FFC9A7F1048(4, (unsigned __int64)&unk_7FFC9A863975, v35);
            v28 = v57;
          }
          if ( v28 < 0 )
            goto LABEL_34;
          if ( v59 >= 0 )
          {
            v57 = 0;
            v61 = 0;
            goto LABEL_92;
          }
          v28 = sub_7FFC9A84878C(&v65);
          v57 = v28;
          if ( v28 < 0 )
            goto LABEL_34;
          if ( v65 )
          {
            v14 = (unsigned int)v59;
            if ( v59 == -2147221164 )
            {
              v14 = 3221536771i64;
              goto LABEL_10;
            }
            v17 = v59 < 0;
            goto LABEL_19;
          }
        }
      }
      v28 = GetProductSkuInformation(hSLC, pProductSkuId, (__int64)&ptr);// 或者密钥加密信息
      v57 = v28;
      if ( v28 >= 0 )
      {
        if ( v20 < 0
          || v60 != 1
          || *(_QWORD *)eQueryIdType != 5580477268562093876i64
          || *((_QWORD *)eQueryIdType + 1) != -6988154782983242088i64 )
        {
          goto LABEL_137;
        }
        v28 = sub_7FFC9A7FCA68(&v59);
        v57 = v28;
        if ( (unsigned int)dword_7FFC9A86B000 > 5
          && qword_7FFC9A86B010 & 0x400000000000i64
          && (qword_7FFC9A86B018 & 0x400000000000i64) == qword_7FFC9A86B018 )
        {
          v85 = &v57;
          v86 = 4i64;
          v87 = &v59;
          sub_7FFC9A816F4C(&unk_7FFC9A85DD0C, &unk_7FFC9A86D080);
          v88 = 4i64;
          sub_7FFC9A7F1048(v36, (unsigned __int64)&unk_7FFC9A863975, v37);
          v28 = v57;
        }
        if ( v28 >= 0 )
        {
LABEL_137:
          if ( Buf1 )
          {
            v28 = sub_7FFC9A7F567C(Buf1, L"Volume:CSVLK", &lpData);
            v38 = lpData;
          }
          else
          {
            v38 = 0;
            sub_7FFC9A7F7F8C(0);
            v28 = 0;
          }
          v57 = v28;
          if ( v28 >= 0 )
          {
            if ( v38 && v60 )
            {
              if ( ppReturnIds )
              {
                LocalFree(ppReturnIds, v15);
                ppReturnIds = 0i64;
              }
              SLGetApplicationInformation(
                hSLC,
                eQueryIdType,
                L"IsKeyManagementService",
                &eReturnIdType,
                &pnReturnIds,
                &ppReturnIds);
            }
            goto LABEL_91;
          }
        }
      }
LABEL_34:
      v14 = (unsigned int)v28;
      goto LABEL_11;
    }
    v33 = v32;
    goto LABEL_47;
  }
  V_0 = 1;
  v16 = SLpVLActivateProduct(hSLC, pProductSkuId);
LABEL_18:
  v14 = v16;
  v17 = (v16 & 0x80000000) != 0;
LABEL_19:
  v57 = v14;
  if ( v17 )
    goto LABEL_11;
LABEL_91:
  v39 = v57;
  v61 = v57;
  if ( v57 == -1073422296 )
    goto LABEL_116;
LABEL_92:
  if ( (int)SLSetGenuineInformation(pProductSkuId, L"SL_LAST_ACT_ATTEMPT_HRESULT", 3i64) < 0 )
    goto LABEL_116;
  GetSystemTimeAsFileTime(&lpSystemTimeAsFileTime);
  SLSetGenuineInformation(pProductSkuId, L"SL_LAST_ACT_ATTEMPT_TIME", 3i64);
  if ( v61 < 0 )
  {
    v39 = (unsigned int)v59;
    if ( v59 < 0 )
    {
      v15 = 536805376i64;
      if ( (v59 & 0xF000) != 0x8000 || (v59 & 0x1FFF0000) != 4128768 || v59 >= 0 )
      {
        if ( (v59 & 0x1FFF0000) != 132186112 || (v39 = (unsigned int)(v59 >> 31), v59 >= 0) )
          int0 = 0;
      }
    }
  }
  else
  {
    int0 = -2147483647;
  }
  if ( v13 )
  {
    PHKEY = 0i64;
    hSLIDList = SLGetSLIDList(hSLC, 1i64, pProductSkuId);
    v41 = hSLIDList;
    if ( hSLIDList == -1073418222 )
    {
      v41 = -1073418220;
    }
    else if ( hSLIDList >= 0 )
    {
      if ( lpData > 0 )
      {
        _mm_storeu_si128((__m128i *)&v84, *PHKEY);
        goto LABEL_111;
      }
      v41 = -2147467259;
      v42 = 2147500037i64;
LABEL_107:
      sub_7FFC9A7F7F24(v42);
LABEL_111:
      sub_7FFC9A7F7F8C(v41);
      sub_7FFC9A802B14(&PHKEY);
      if ( (v41 & 0x80000000) != 0 || mem_addr != v84 )
        int0 = -2147483647;
      goto LABEL_114;
    }
    v42 = v41;
    goto LABEL_107;
  }
LABEL_114:
  if ( int0 )
    SLSetGenuineInformation(pProductSkuId, L"SL_LAST_ACT_ATTEMPT_SERVER_FLAGS", 3i64);
LABEL_116:
  if ( v61 >= 0 )
  {
    if ( V_0 )
      sub_7FFC9A7FCD08(hSLC, pProductSkuId);
    if ( v61 >= 0 )
      sub_7FFC9A8029D4(v39, v15);
  }
  if ( v57 == -1073418220 )
  {
    sub_7FFC9A7F7F24(1i64);
    sub_7FFC9A7F7F8C(v43);
  }
  else
  {
    sub_7FFC9A7FDB4C(&eQueryIdTypes, v57);
  }
  sub_7FFC9A7F7F8C(v57);
  v46 = (char *)Buf1;
  hResult = v57;
  if ( Buf1 )
  {
    v48 = GetProcessHeap(v45, v44);
    HeapFree(v48, 0i64, v46 - 4);
    sub_7FFC9A7F7F8C(0);
    Buf1 = 0i64;
  }
  v49 = v77;
  if ( v77 )
  {
    v50 = GetProcessHeap(v45, v44);
    HeapFree(v50, 0i64, v49 - 4);
    sub_7FFC9A7F7F8C(0);
    v77 = 0i64;
  }
  v51 = *((_QWORD *)&mem_addrs + 1);
  if ( *((_QWORD *)&mem_addrs + 1) )
  {
    v52 = GetProcessHeap(v45, v44);
    HeapFree(v52, 0i64, v51 - 4);
    sub_7FFC9A7F7F8C(0);
    *((_QWORD *)&mem_addrs + 1) = 0i64;
  }
  v53 = mem_addrs;
  if ( (_QWORD)mem_addrs )
  {
    v54 = GetProcessHeap(v45, v44);
    HeapFree(v54, 0i64, v53 - 4);
    sub_7FFC9A7F7F8C(0);
    *(_QWORD *)&mem_addrs = 0i64;
  }
  sub_7FFC9A7F4C0C(&ppReturnIds);
  if ( eQueryIdType )
    LocalFree(eQueryIdType, hMem);
  return hResult;
}



__int64 __fastcall sub_7FFC93379104(__int64 a1, __int64 *a2, __int64 a3, unsigned int a4, __int64 *a5, unsigned int *a6, __int64 *a7, __int64 *a8)
{
  __int64 v8; // rdx
  __int64 v9; // rbx
  __int64 v10; // rsi
  __int64 v11; // rdi
  unsigned int v12; // er13
  signed int v13; // eax
  __int64 v14; // rdx
  __int64 v15; // rcx
  signed int v16; // er12
  __int64 v17; // rcx
  __int64 v18; // r14
  signed int v19; // eax
  wchar_t *v20; // r15
  __int64 v21; // rdx
  __int64 v22; // rcx
  __int64 v23; // rax
  void *v24; // r15
  signed int v25; // eax
  __int64 v26; // rdx
  __int64 v27; // rcx
  __int64 v28; // rax
  void *v29; // r15
  signed int v30; // eax
  __int64 v31; // rsi
  __int64 v32; // rax
  __int64 (__fastcall *v33)(__int64, __int64, _QWORD, _QWORD); // r15
  wchar_t *v34; // r15
  BOOL v35; // eax
  __int64 v36; // rcx
  __int64 v37; // rcx
  __int64 v38; // rcx
  __int64 v39; // rdx
  __int64 v40; // rcx
  __int64 v41; // rax
  __int64 v42; // rdx
  __int64 v43; // rcx
  __int64 v44; // rax
  __int64 v45; // rdx
  __int64 v46; // rcx
  __int64 v47; // rax
  int v49; // [rsp+40h] [rbp-39h]
  unsigned int v50; // [rsp+44h] [rbp-35h]
  __int64 v51; // [rsp+48h] [rbp-31h]
  __int64 v52; // [rsp+50h] [rbp-29h]
  __int64 v53; // [rsp+58h] [rbp-21h]
  int v54; // [rsp+60h] [rbp-19h]
  __int64 v55; // [rsp+68h] [rbp-11h]
  wchar_t *Str1; // [rsp+70h] [rbp-9h]
  int v57; // [rsp+78h] [rbp-1h]
  void *Src; // [rsp+80h] [rbp+7h]
  __int64 v59; // [rsp+C8h] [rbp+4Fh]

  v8 = *a2;
  v9 = 0i64;
  v53 = 0i64;
  v55 = 0i64;
  v10 = 0i64;
  v11 = 0i64;
  v51 = 0i64;
  v12 = 0;
  v52 = 0i64;
  v13 = SLpGetLicenseAcquisitionInfo(a1, v8, a4, a3, &v54, &v50, &v53);
  v16 = v13;
  if ( v13 < 0 )
    goto LABEL_2;
  if ( v54 != 3 )
  {
LABEL_50:
    v17 = 2147942413i64;
    v16 = -2147024883;
    goto LABEL_51;
  }
  v13 = sub_7FFC9337453C(v15, v14, &v55);
  v16 = v13;
  if ( v13 < 0 )
  {
LABEL_2:
    v17 = (unsigned int)v13;
LABEL_51:
    sub_7FFC93377F24(v17);
    goto LABEL_52;
  }
  v18 = v55;
  v16 = (*(__int64 (__fastcall **)(__int64, __int64, _QWORD, _QWORD))(*(_QWORD *)v55 + 24i64))(v55, v53, v50, 0i64);
  if ( v16 < 0 )
  {
    sub_7FFC93377F24((unsigned int)v16);
    sub_7FFC933975D8(&unk_7FFC933E2168, &unk_7FFC933EBDF8);
    goto LABEL_52;
  }
  while ( 1 )
  {
    v19 = (*(__int64 (__fastcall **)(__int64, wchar_t **))(*(_QWORD *)v18 + 48i64))(v18, &Str1);
    v16 = v19;
    if ( v57 != 2 )
      goto LABEL_50;
    if ( v19 == -2147024637 )
      break;
    if ( v19 < 0 )
      goto LABEL_22;
    v20 = Str1;
    if ( !wcscmp(Str1, L"SppLAPServerURL") )
    {
      if ( v11 )
      {
        v23 = GetProcessHeap(v22, v21);
        HeapFree(v23, 0i64, v11 - 4);
        sub_7FFC93377F8C(0);
        v11 = 0i64;
        v51 = 0i64;
      }
      v24 = Src;
      if ( !Src )
      {
        LODWORD(v59) = 0;
LABEL_18:
        v25 = sub_7FFC93377DB8(v24);
        v16 = v25;
        if ( v25 < 0 )
          sub_7FFC93377F24((unsigned int)v25);
        v11 = v51;
        goto LABEL_21;
      }
      v16 = sub_7FFC93377CF8(Src, &v59);
      if ( v16 >= 0 )
        goto LABEL_18;
LABEL_15:
      sub_7FFC93377F24((unsigned int)v16);
LABEL_21:
      sub_7FFC93377F8C(v16);
      if ( v16 < 0 )
        goto LABEL_22;
    }
    else
    {
      if ( !wcscmp(v20, L"SppLAPRequestTokenType") )
      {
        if ( v9 )
        {
          v28 = GetProcessHeap(v27, v26);
          HeapFree(v28, 0i64, v9 - 4);
          sub_7FFC93377F8C(0);
          v9 = 0i64;
          v52 = 0i64;
        }
        v29 = Src;
        if ( !Src )
        {
          v49 = 0;
LABEL_30:
          v30 = sub_7FFC93377DB8(v29);
          v16 = v30;
          if ( v30 < 0 )
            sub_7FFC93377F24((unsigned int)v30);
          v9 = v52;
          goto LABEL_21;
        }
        v16 = sub_7FFC93377CF8(Src, &v49);
        if ( v16 >= 0 )
          goto LABEL_30;
        goto LABEL_15;
      }
      if ( !v20 || !*v20 || v20[1] != 58 )
        goto LABEL_50;
      ++v12;
    }
  }
  v31 = 24i64 * v12;
  if ( !is_mul_ok(v12, 0x18ui64) )
    v31 = -1i64;
  v32 = GetProcessHeap(v12, (v12 * (unsigned __int128)0x18ui64) >> 64);
  v10 = HeapAlloc(v32, 0i64, v31);
  if ( !v10 )
  {
    v16 = -2147024882;
LABEL_22:
    v17 = (unsigned int)v16;
    goto LABEL_51;
  }
  v12 = 0;
  v33 = *(__int64 (__fastcall **)(__int64, __int64, _QWORD, _QWORD))(*(_QWORD *)v18 + 24i64);
  sub_7FFC93397928(&unk_7FFC933E0E5C, &unk_7FFC933EBD08);
  v16 = v33(v18, v53, v50, 0i64);
  if ( v16 < 0 )
    goto LABEL_22;
  while ( 1 )
  {
    v13 = (*(__int64 (__fastcall **)(__int64, wchar_t **))(*(_QWORD *)v18 + 48i64))(v18, &Str1);
    if ( v13 == -2147024637 )
      break;
    v16 = v13;
    if ( v13 < 0 )
      goto LABEL_2;
    v34 = Str1;
    if ( wcscmp(Str1, L"SppLAPServerURL") && wcscmp(v34, L"SppLAPRequestTokenType") )
    {
      v35 = *v34 != 48;
      v59 = 3i64 * v12;
      *(_DWORD *)(v10 + 8 * v59) = v35;
      v13 = sub_7FFC933A07EC(Str1 + 2);
      v16 = v13;
      if ( v13 < 0 )
        goto LABEL_2;
      v13 = sub_7FFC933A07EC(Src);
      v16 = v13;
      if ( v13 < 0 )
        goto LABEL_2;
      ++v12;
    }
  }
  v36 = v10;
  v10 = 0i64;
  *a5 = v36;
  v37 = v11;
  v11 = 0i64;
  *a6 = v12;
  *a7 = v37;
  v38 = v9;
  v9 = 0i64;
  *a8 = v38;
LABEL_52:
  if ( v10 )
    sub_7FFC933A076C(v12, v10);
  sub_7FFC93377F8C(v16);
  if ( v9 )
  {
    v41 = GetProcessHeap(v40, v39);
    HeapFree(v41, 0i64, v9 - 4);
    sub_7FFC93377F8C(0);
  }
  sub_7FFC93397294(&unk_7FFC933E26A8, &unk_7FFC933ED0B8);
  if ( v11 )
  {
    v44 = GetProcessHeap(v43, v42);
    HeapFree(v44, 0i64, v11 - 4);
    sub_7FFC93377F8C(0);
  }
  if ( v10 )
  {
    sub_7FFC93396F4C(L"@\a", &unk_7FFC933ED0C8);
    v47 = GetProcessHeap(v46, v45);
    HeapFree(v47, 0i64, v10);
  }
  sub_7FFC93374AE4(&v55);
  sub_7FFC93374C0C(&v53);
  return (unsigned int)v16;
}
