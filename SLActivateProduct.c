__int64 __fastcall SLActivateProduct(__int64 SLC, __int64 ProductSkuId, __int64 cbAppSpecificData, __int64 pvAppSpecificData, _DWORD *pActivationInfo, __int64 pwszProxyServer, __int16 wProxyPort)
{
  int v7; // er12
  __int64 pProductSkuId; // r14
  __int64 hSLC; // r15
  __int64 v10; // rax
  int v11; // edi
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
  char *v24; // rbx
  unsigned int v25; // edi
  __int64 v26; // rax
  __int128 *v27; // rdx
  signed int v28; // eax
  unsigned int v29; // ebx
  unsigned int v30; // ebx
  signed int v31; // eax
  unsigned int v32; // ebx
  __int64 v33; // rcx
  __int64 v34; // rdx
  __int64 v35; // r8
  int v36; // ecx
  __int64 v37; // r8
  unsigned int v38; // ebx
  __int64 v39; // rcx
  signed int v40; // eax
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
  _DWORD *Dst; // [rsp+70h] [rbp-90h]
  __int64 v69; // [rsp+78h] [rbp-88h]
  __int16 v70; // [rsp+80h] [rbp-80h]
  void *Buf1; // [rsp+88h] [rbp-78h]
  __int64 *v72; // [rsp+90h] [rbp-70h]
  int v73; // [rsp+98h] [rbp-68h]
  __int64 v74; // [rsp+A0h] [rbp-60h]
  __int64 v75; // [rsp+A8h] [rbp-58h]
  __int128 mem_addrs; // [rsp+B0h] [rbp-50h]
  __int64 v77; // [rsp+C0h] [rbp-40h]
  int v78; // [rsp+C8h] [rbp-38h]
  int v79; // [rsp+CCh] [rbp-34h]
  char lpType; // [rsp+D0h] [rbp-30h]
  char eReturnIdType; // [rsp+D4h] [rbp-2Ch]
  char lpSystemTimeAsFileTime; // [rsp+D8h] [rbp-28h]
  __int128 mem_addr; // [rsp+E0h] [rbp-20h]
  __int128 v84; // [rsp+F0h] [rbp-10h]
  unsigned int *v85; // [rsp+120h] [rbp+20h]
  __int64 v86; // [rsp+128h] [rbp+28h]
  int *v87; // [rsp+130h] [rbp+30h]
  __int64 v88; // [rsp+138h] [rbp+38h]

  v7 = 0;
  eQueryIdType = 0i64;
  pProductSkuId = ProductSkuId;
  ppReturnIds = 0i64;
  hSLC = SLC;
  v74 = 0i64;
  v79 = 0;
  _mm_storeu_si128((__m128i *)&mem_addrs, (__m128i)0i64);
  v77 = 0i64;
  v10 = GetTickCount64(SLC, ProductSkuId, cbAppSpecificData, pvAppSpecificData);
  v78 = -1;
  v75 = v10;
  PHKEY = 0i64;
  v11 = 0;
  if ( !(unsigned int)RegOpenKeyExW(0xFFFFFFFF80000002i64, L"SYSTEM\\Setup", 0i64, 0x20019i64, &PHKEY) )
  {
    lpcbData = 4;
    if ( !(unsigned int)RegQueryValueExW(PHKEY, L"OOBEInProgress", 0i64, &lpType, &lpData, &lpcbData) )
      LOBYTE(v11) = lpData == 1;
  }
  sub_7FFC93207F8C(0);
  if ( PHKEY )
    RegCloseKey();
  v12 = v78;
  if ( v11 )
    v12 = 0;
  v78 = v12;
  sub_7FFC93207F8C(0);
  memset(&Dst, 0, 0x30ui64);
  v59 = 0;
  v13 = 0;
  UNKNOWNCALL((unsigned int *)&unk_7FFC9326F360, (unsigned int *)&unk_7FFC9327C078);
  v65 = 0;
  if ( !hSLC || !pProductSkuId )
    goto LABEL_9;
  v70 = wProxyPort;
  v72 = &v74;
  Dst = pActivationInfo;
  v69 = pwszProxyServer;
  v73 = 0;
  if ( pActivationInfo )
  {
    if ( *pActivationInfo < 8u )
    {
LABEL_9:
      v14 = 2147942487i64;
LABEL_10:
      v57 = v14;
LABEL_11:
      sub_7FFC93207F24(v14);
      goto LABEL_91;
    }
    if ( pActivationInfo[1] != 1 )
    {
      sub_7FFC93227294(&unk_7FFC9326F538, &unk_7FFC9327C1A0);
      goto LABEL_9;
    }
    v16 = sub_7FFC9320AA4C(hSLC, pProductSkuId, &Dst);
    goto LABEL_18;
  }
  hgETSLIDLIST = SLGetSLIDList(hSLC, 1i64, pProductSkuId);
  v19 = v60;
  v20 = hgETSLIDLIST;
  if ( hgETSLIDLIST < 0 )
    v19 = 0;
  v60 = v19;
  v21 = sub_7FFC9321234C(hSLC, pProductSkuId, &Buf1);
  v24 = (char *)Buf1;
  v25 = v21;
  if ( v21 < 0 && Buf1 )
  {
    v26 = GetProcessHeap(v23, v22);
    HeapFree(v26, 0i64, v24 - 4);
    sub_7FFC93207F8C(0);
    v24 = 0i64;
    Buf1 = 0i64;
  }
  sub_7FFC93226C14(&unk_7FFC93270438, &unk_7FFC9327CEC8);
  v27 = &xmmword_7FFC9325F628;
  if ( v60 )
    v27 = eQueryIdType;
  sub_7FFC93205404(&v74, v27, pProductSkuId, v24, 0i64);
  v57 = v25;
  if ( (v25 & 0x80000000) != 0 )
  {
    sub_7FFC93207F24(v25);
    goto LABEL_91;
  }
  if ( Buf1 )
  {
    v28 = sub_7FFC9320567C(Buf1, L"Volume:GVLK");
    v29 = lpData;
  }
  else
  {
    v29 = 0;
    sub_7FFC93207F8C(0);
    v28 = 0;
  }
  v57 = v28;
  if ( v28 < 0 )
    goto LABEL_34;
  if ( !v29 )
  {
    if ( Buf1 )
    {
      v28 = sub_7FFC9320567C(Buf1, L"VT:IA");
      v30 = lpData;
    }
    else
    {
      v30 = 0;
      sub_7FFC93207F8C(0);
      v28 = 0;
    }
    v57 = v28;
    if ( v28 < 0 )
      goto LABEL_34;
    if ( v30 )
    {
      v7 = 1;
      v16 = SLpIAActivateProduct(hSLC, pProductSkuId);
      goto LABEL_18;
    }
    PHKEY = 0i64;
    v31 = SLGetSLIDList(hSLC, 1i64, pProductSkuId);
    v32 = v31;
    if ( v31 == -1073418222 )
    {
      v32 = -1073418220;
    }
    else if ( v31 >= 0 )
    {
      if ( lpData > 0 )
      {
        _mm_storeu_si128((__m128i *)&mem_addr, *PHKEY);
        goto LABEL_51;
      }
      v32 = -2147467259;
      v33 = 2147500037i64;
LABEL_47:
      sub_7FFC93207F24(v33);
LABEL_51:
      sub_7FFC93207F8C(v32);
      sub_7FFC93212B14(&PHKEY);
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
          v28 = sub_7FFC9320CA68(&v59);
          v57 = v28;
          if ( (unsigned int)dword_7FFC9327B000 > 5
            && qword_7FFC9327B010 & 0x400000000000i64
            && (qword_7FFC9327B018 & 0x400000000000i64) == qword_7FFC9327B018 )
          {
            v85 = &v57;
            v87 = &v59;
            v86 = 4i64;
            v88 = 4i64;
            sub_7FFC93201048(4, (unsigned __int64)&unk_7FFC93273975, v35);
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
          v28 = sub_7FFC9325878C(&v65);
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
      v28 = sub_7FFC9320AA4C(hSLC, pProductSkuId, &Dst);
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
        v28 = sub_7FFC9320CA68(&v59);
        v57 = v28;
        if ( (unsigned int)dword_7FFC9327B000 > 5
          && qword_7FFC9327B010 & 0x400000000000i64
          && (qword_7FFC9327B018 & 0x400000000000i64) == qword_7FFC9327B018 )
        {
          v85 = &v57;
          v86 = 4i64;
          v87 = &v59;
          sub_7FFC93226F4C(&unk_7FFC9326DD0C, &unk_7FFC9327D080);
          v88 = 4i64;
          sub_7FFC93201048(v36, (unsigned __int64)&unk_7FFC93273975, v37);
          v28 = v57;
        }
        if ( v28 >= 0 )
        {
LABEL_137:
          if ( Buf1 )
          {
            v28 = sub_7FFC9320567C(Buf1, L"Volume:CSVLK");
            v38 = lpData;
          }
          else
          {
            v38 = 0;
            sub_7FFC93207F8C(0);
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
  v7 = 1;
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
          v73 = 0;
      }
    }
  }
  else
  {
    v73 = -2147483647;
  }
  if ( v13 )
  {
    PHKEY = 0i64;
    v40 = SLGetSLIDList(hSLC, 1i64, pProductSkuId);
    v41 = v40;
    if ( v40 == -1073418222 )
    {
      v41 = -1073418220;
    }
    else if ( v40 >= 0 )
    {
      if ( lpData > 0 )
      {
        _mm_storeu_si128((__m128i *)&v84, *PHKEY);
        goto LABEL_111;
      }
      v41 = -2147467259;
      v42 = 2147500037i64;
LABEL_107:
      sub_7FFC93207F24(v42);
LABEL_111:
      sub_7FFC93207F8C(v41);
      sub_7FFC93212B14(&PHKEY);
      if ( (v41 & 0x80000000) != 0 || mem_addr != v84 )
        v73 = -2147483647;
      goto LABEL_114;
    }
    v42 = v41;
    goto LABEL_107;
  }
LABEL_114:
  if ( v73 )
    SLSetGenuineInformation(pProductSkuId, L"SL_LAST_ACT_ATTEMPT_SERVER_FLAGS", 3i64);
LABEL_116:
  if ( v61 >= 0 )
  {
    if ( v7 )
      sub_7FFC9320CD08(hSLC, pProductSkuId);
    if ( v61 >= 0 )
      sub_7FFC932129D4(v39, v15);
  }
  if ( v57 == -1073418220 )
  {
    sub_7FFC93207F24(1i64);
    sub_7FFC93207F8C(v43);
  }
  else
  {
    sub_7FFC9320DB4C(&v74, v57);
  }
  sub_7FFC93207F8C(v57);
  v46 = (char *)Buf1;
  hResult = v57;
  if ( Buf1 )
  {
    v48 = GetProcessHeap(v45, v44);
    HeapFree(v48, 0i64, v46 - 4);
    sub_7FFC93207F8C(0);
    Buf1 = 0i64;
  }
  v49 = v77;
  if ( v77 )
  {
    v50 = GetProcessHeap(v45, v44);
    HeapFree(v50, 0i64, v49 - 4);
    sub_7FFC93207F8C(0);
    v77 = 0i64;
  }
  v51 = *((_QWORD *)&mem_addrs + 1);
  if ( *((_QWORD *)&mem_addrs + 1) )
  {
    v52 = GetProcessHeap(v45, v44);
    HeapFree(v52, 0i64, v51 - 4);
    sub_7FFC93207F8C(0);
    *((_QWORD *)&mem_addrs + 1) = 0i64;
  }
  v53 = mem_addrs;
  if ( (_QWORD)mem_addrs )
  {
    v54 = GetProcessHeap(v45, v44);
    HeapFree(v54, 0i64, v53 - 4);
    sub_7FFC93207F8C(0);
    *(_QWORD *)&mem_addrs = 0i64;
  }
  sub_7FFC93204C0C(&ppReturnIds);
  if ( eQueryIdType )
    LocalFree(eQueryIdType, hMem);
  return hResult;
}
