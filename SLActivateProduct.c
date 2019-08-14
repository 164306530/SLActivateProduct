__int64 __fastcall SLActivateProduct(__int64 a1, __int64 a2, __int64 a3, __int64 a4, _DWORD *a5, __int64 a6, __int16 a7)
{
  int v7; // er12
  __int64 v8; // r14
  __int64 v9; // r15
  __int64 v10; // rax
  int v11; // edi
  int v12; // eax
  int v13; // er13
  __int64 v14; // rcx
  unsigned int v15; // eax
  bool v16; // sf
  int v17; // eax
  int v18; // ecx
  int v19; // esi
  signed int v20; // eax
  char *v21; // rbx
  unsigned int v22; // edi
  __int64 v23; // rax
  __int128 *v24; // rdx
  signed int v25; // eax
  unsigned int v26; // ebx
  unsigned int v27; // ebx
  signed int v28; // eax
  unsigned int v29; // ebx
  __int64 v30; // rcx
  __int64 v31; // r8
  int v32; // ecx
  __int64 v33; // r8
  unsigned int v34; // ebx
  signed int v35; // eax
  unsigned int v36; // ebx
  __int64 v37; // rcx
  __int64 v38; // rcx
  char *v39; // rbx
  unsigned int v40; // edi
  __int64 v41; // rax
  __int64 v42; // rbx
  __int64 v43; // rax
  __int64 v44; // rbx
  __int64 v45; // rax
  __int64 v46; // rbx
  __int64 v47; // rax
  unsigned int v49; // [rsp+30h] [rbp-D0h]
  unsigned int v50; // [rsp+34h] [rbp-CCh]
  int v51; // [rsp+38h] [rbp-C8h]
  int v52; // [rsp+3Ch] [rbp-C4h]
  int v53; // [rsp+40h] [rbp-C0h]
  __m128i *v54; // [rsp+48h] [rbp-B8h]
  __int64 v55; // [rsp+50h] [rbp-B0h]
  __int128 *v56; // [rsp+58h] [rbp-A8h]
  int v57; // [rsp+60h] [rbp-A0h]
  int v58; // [rsp+64h] [rbp-9Ch]
  char v59; // [rsp+68h] [rbp-98h]
  _DWORD *Dst; // [rsp+70h] [rbp-90h]
  __int64 v61; // [rsp+78h] [rbp-88h]
  __int16 v62; // [rsp+80h] [rbp-80h]
  void *Buf1; // [rsp+88h] [rbp-78h]
  __int64 *v64; // [rsp+90h] [rbp-70h]
  int v65; // [rsp+98h] [rbp-68h]
  __int64 v66; // [rsp+A0h] [rbp-60h]
  __int64 v67; // [rsp+A8h] [rbp-58h]
  __int128 v68; // [rsp+B0h] [rbp-50h]
  __int64 v69; // [rsp+C0h] [rbp-40h]
  int v70; // [rsp+C8h] [rbp-38h]
  int v71; // [rsp+CCh] [rbp-34h]
  char v72; // [rsp+D0h] [rbp-30h]
  char v73; // [rsp+D4h] [rbp-2Ch]
  char v74; // [rsp+D8h] [rbp-28h]
  __int128 v75; // [rsp+E0h] [rbp-20h]
  __int128 v76; // [rsp+F0h] [rbp-10h]
  unsigned int *v77; // [rsp+120h] [rbp+20h]
  __int64 v78; // [rsp+128h] [rbp+28h]
  int *v79; // [rsp+130h] [rbp+30h]
  __int64 v80; // [rsp+138h] [rbp+38h]

  v7 = 0;
  v56 = 0i64;
  v8 = a2;
  v55 = 0i64;
  v9 = a1;
  v66 = 0i64;
  v71 = 0;
  _mm_storeu_si128((__m128i *)&v68, (__m128i)0i64);
  v69 = 0i64;
  v10 = GetTickCount64();
  v70 = -1;
  v67 = v10;
  v54 = 0i64;
  v11 = 0;
  if ( !(unsigned int)RegOpenKeyExW(-2147483646i64, L"SYSTEM\\Setup", 0i64, 131097i64, &v54) )
  {
    v58 = 4;
    if ( !(unsigned int)RegQueryValueExW(v54, L"OOBEInProgress", 0i64, &v72, &v50, &v58) )
      LOBYTE(v11) = v50 == 1;
  }
  sub_7FFC93207F8C(0i64);
  if ( v54 )
    RegCloseKey();
  v12 = v70;
  if ( v11 )
    v12 = 0;
  v70 = v12;
  sub_7FFC93207F8C(0i64);
  memset(&Dst, 0, 0x30ui64);
  v51 = 0;
  v13 = 0;
  sub_7FFC932268C0(&unk_7FFC9326F360, &unk_7FFC9327C078);
  v57 = 0;
  if ( !v9 || !v8 )
    goto LABEL_9;
  v62 = a7;
  v64 = &v66;
  Dst = a5;
  v61 = a6;
  v65 = 0;
  if ( a5 )
  {
    if ( *a5 < 8u )
    {
LABEL_9:
      v14 = 2147942487i64;
LABEL_10:
      v49 = v14;
LABEL_11:
      sub_7FFC93207F24(v14);
      goto LABEL_91;
    }
    if ( a5[1] != 1 )
    {
      sub_7FFC93227294(&unk_7FFC9326F538, &unk_7FFC9327C1A0);
      goto LABEL_9;
    }
    v15 = sub_7FFC9320AA4C(v9, v8, (__int64)&Dst);
    goto LABEL_18;
  }
  v17 = SLGetSLIDList(v9, 1i64, v8);
  v18 = v52;
  v19 = v17;
  if ( v17 < 0 )
    v18 = 0;
  v52 = v18;
  v20 = sub_7FFC9321234C(v9, v8, &Buf1);
  v21 = (char *)Buf1;
  v22 = v20;
  if ( v20 < 0 && Buf1 )
  {
    v23 = GetProcessHeap();
    HeapFree(v23, 0i64, v21 - 4);
    sub_7FFC93207F8C(0i64);
    v21 = 0i64;
    Buf1 = 0i64;
  }
  sub_7FFC93226C14(&unk_7FFC93270438, &unk_7FFC9327CEC8);
  v24 = &xmmword_7FFC9325F628;
  if ( v52 )
    v24 = v56;
  sub_7FFC93205404(&v66, v24, v8, v21, 0i64);
  v49 = v22;
  if ( (v22 & 0x80000000) != 0 )
  {
    sub_7FFC93207F24(v22);
    goto LABEL_91;
  }
  if ( Buf1 )
  {
    v25 = sub_7FFC9320567C(Buf1, L"Volume:GVLK");
    v26 = v50;
  }
  else
  {
    v26 = 0;
    sub_7FFC93207F8C(0i64);
    v25 = 0;
  }
  v49 = v25;
  if ( v25 < 0 )
    goto LABEL_34;
  if ( !v26 )
  {
    if ( Buf1 )
    {
      v25 = sub_7FFC9320567C(Buf1, L"VT:IA");
      v27 = v50;
    }
    else
    {
      v27 = 0;
      sub_7FFC93207F8C(0i64);
      v25 = 0;
    }
    v49 = v25;
    if ( v25 < 0 )
      goto LABEL_34;
    if ( v27 )
    {
      v7 = 1;
      v15 = SLpIAActivateProduct(v9, v8);
      goto LABEL_18;
    }
    v54 = 0i64;
    v28 = SLGetSLIDList(v9, 1i64, v8);
    v29 = v28;
    if ( v28 == -1073418222 )
    {
      v29 = -1073418220;
    }
    else if ( v28 >= 0 )
    {
      if ( v50 > 0 )
      {
        _mm_storeu_si128((__m128i *)&v75, *v54);
        goto LABEL_51;
      }
      v29 = -2147467259;
      v30 = 2147500037i64;
LABEL_47:
      sub_7FFC93207F24(v30);
LABEL_51:
      sub_7FFC93207F8C(v29);
      sub_7FFC93212B14(&v54);
      v49 = v29;
      if ( (v29 & 0x80000000) != 0 )
      {
        v14 = v29;
        goto LABEL_11;
      }
      v13 = 1;
      if ( v19 >= 0
        && v52 == 1
        && *(_QWORD *)v56 == 5580477268562093876i64
        && *((_QWORD *)v56 + 1) == -6988154782983242088i64 )
      {
        if ( v55 )
          LocalFree();
        if ( (unsigned int)SLGetProductSkuInformation(v9, v8, L"DependsOn", 0i64, &v59, &v55) == -1073418222 )
        {
          v25 = sub_7FFC9320CA68(&v51);
          v49 = v25;
          if ( (unsigned int)dword_7FFC9327B000 > 5
            && qword_7FFC9327B010 & 0x400000000000i64
            && (qword_7FFC9327B018 & 0x400000000000i64) == qword_7FFC9327B018 )
          {
            v77 = &v49;
            v79 = &v51;
            v78 = 4i64;
            v80 = 4i64;
            sub_7FFC93201048(4, (unsigned __int64)&unk_7FFC93273975, v31);
            v25 = v49;
          }
          if ( v25 < 0 )
            goto LABEL_34;
          if ( v51 >= 0 )
          {
            v49 = 0;
            v53 = 0;
            goto LABEL_92;
          }
          v25 = sub_7FFC9325878C(&v57);
          v49 = v25;
          if ( v25 < 0 )
            goto LABEL_34;
          if ( v57 )
          {
            v14 = (unsigned int)v51;
            if ( v51 == -2147221164 )
            {
              v14 = 3221536771i64;
              goto LABEL_10;
            }
            v16 = v51 < 0;
            goto LABEL_19;
          }
        }
      }
      v25 = sub_7FFC9320AA4C(v9, v8, (__int64)&Dst);
      v49 = v25;
      if ( v25 >= 0 )
      {
        if ( v19 < 0
          || v52 != 1
          || *(_QWORD *)v56 != 5580477268562093876i64
          || *((_QWORD *)v56 + 1) != -6988154782983242088i64 )
        {
          goto LABEL_137;
        }
        v25 = sub_7FFC9320CA68(&v51);
        v49 = v25;
        if ( (unsigned int)dword_7FFC9327B000 > 5
          && qword_7FFC9327B010 & 0x400000000000i64
          && (qword_7FFC9327B018 & 0x400000000000i64) == qword_7FFC9327B018 )
        {
          v77 = &v49;
          v78 = 4i64;
          v79 = &v51;
          sub_7FFC93226F4C(&unk_7FFC9326DD0C, &unk_7FFC9327D080);
          v80 = 4i64;
          sub_7FFC93201048(v32, (unsigned __int64)&unk_7FFC93273975, v33);
          v25 = v49;
        }
        if ( v25 >= 0 )
        {
LABEL_137:
          if ( Buf1 )
          {
            v25 = sub_7FFC9320567C(Buf1, L"Volume:CSVLK");
            v34 = v50;
          }
          else
          {
            v34 = 0;
            sub_7FFC93207F8C(0i64);
            v25 = 0;
          }
          v49 = v25;
          if ( v25 >= 0 )
          {
            if ( v34 && v52 )
            {
              if ( v55 )
              {
                LocalFree();
                v55 = 0i64;
              }
              SLGetApplicationInformation(v9, v56, L"IsKeyManagementService", &v73, &v59, &v55);
            }
            goto LABEL_91;
          }
        }
      }
LABEL_34:
      v14 = (unsigned int)v25;
      goto LABEL_11;
    }
    v30 = v29;
    goto LABEL_47;
  }
  v7 = 1;
  v15 = SLpVLActivateProduct(v9, v8);
LABEL_18:
  v14 = v15;
  v16 = (v15 & 0x80000000) != 0;
LABEL_19:
  v49 = v14;
  if ( v16 )
    goto LABEL_11;
LABEL_91:
  v53 = v49;
  if ( v49 == -1073422296 )
    goto LABEL_116;
LABEL_92:
  if ( (int)SLSetGenuineInformation(v8, L"SL_LAST_ACT_ATTEMPT_HRESULT", 3i64, 4i64, &v53) < 0 )
    goto LABEL_116;
  GetSystemTimeAsFileTime(&v74);
  SLSetGenuineInformation(v8, L"SL_LAST_ACT_ATTEMPT_TIME", 3i64, 8i64, &v74);
  if ( v53 < 0 )
  {
    if ( v51 < 0
      && ((v51 & 0xF000) != 0x8000 || (v51 & 0x1FFF0000) != 4128768 || v51 >= 0)
      && ((v51 & 0x1FFF0000) != 132186112 || v51 >= 0) )
    {
      v65 = 0;
    }
  }
  else
  {
    v65 = -2147483647;
  }
  if ( v13 )
  {
    v54 = 0i64;
    v35 = SLGetSLIDList(v9, 1i64, v8);
    v36 = v35;
    if ( v35 == -1073418222 )
    {
      v36 = -1073418220;
    }
    else if ( v35 >= 0 )
    {
      if ( v50 > 0 )
      {
        _mm_storeu_si128((__m128i *)&v76, *v54);
        goto LABEL_111;
      }
      v36 = -2147467259;
      v37 = 2147500037i64;
LABEL_107:
      sub_7FFC93207F24(v37);
LABEL_111:
      sub_7FFC93207F8C(v36);
      sub_7FFC93212B14(&v54);
      if ( (v36 & 0x80000000) != 0 || v75 != v76 )
        v65 = -2147483647;
      goto LABEL_114;
    }
    v37 = v36;
    goto LABEL_107;
  }
LABEL_114:
  if ( v65 )
    SLSetGenuineInformation(v8, L"SL_LAST_ACT_ATTEMPT_SERVER_FLAGS", 3i64, 4i64, &v65);
LABEL_116:
  if ( v53 >= 0 )
  {
    if ( v7 )
      sub_7FFC9320CD08(v9, v8);
    if ( v53 >= 0 )
      sub_7FFC932129D4();
  }
  if ( v49 == -1073418220 )
  {
    sub_7FFC93207F24(1i64);
    sub_7FFC93207F8C(v38);
  }
  else
  {
    sub_7FFC9320DB4C(&v66, v49);
  }
  sub_7FFC93207F8C(v49);
  v39 = (char *)Buf1;
  v40 = v49;
  if ( Buf1 )
  {
    v41 = GetProcessHeap();
    HeapFree(v41, 0i64, v39 - 4);
    sub_7FFC93207F8C(0i64);
    Buf1 = 0i64;
  }
  v42 = v69;
  if ( v69 )
  {
    v43 = GetProcessHeap();
    HeapFree(v43, 0i64, v42 - 4);
    sub_7FFC93207F8C(0i64);
    v69 = 0i64;
  }
  v44 = *((_QWORD *)&v68 + 1);
  if ( *((_QWORD *)&v68 + 1) )
  {
    v45 = GetProcessHeap();
    HeapFree(v45, 0i64, v44 - 4);
    sub_7FFC93207F8C(0i64);
    *((_QWORD *)&v68 + 1) = 0i64;
  }
  v46 = v68;
  if ( (_QWORD)v68 )
  {
    v47 = GetProcessHeap();
    HeapFree(v47, 0i64, v46 - 4);
    sub_7FFC93207F8C(0i64);
    *(_QWORD *)&v68 = 0i64;
  }
  sub_7FFC93204C0C(&v55);
  if ( v56 )
    LocalFree();
  return v40;
}
