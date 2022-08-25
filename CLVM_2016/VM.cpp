// VM reversed by me
void __cdecl luaV_execute(int rL, int nexeccalls)
{
  int v2; // ebp
  int rL_; // esi
  _DWORD *enc_savedpc; // ecx
  _DWORD *v5; // edx
  __m128d v6; // xmm1
  int *program_counter; // edi
  int l_ci; // ecx
  int enc_closure_ci; // ecx
  _DWORD *v10; // eax
  unsigned int stack; // ecx
  int *program_counter__1; // eax
  unsigned int instruction_ptr; // edx
  char v14; // al
  bool v15; // zf
  _DWORD *v16; // edx
  _DWORD *v17; // ecx
  int v18; // eax
  _DWORD *stack_value_new; // ecx
  unsigned int *new_stack_value; // ecx
  unsigned int v21; // eax
  unsigned int v22; // edx
  _DWORD *a; // edx
  int v24; // eax
  _DWORD *v25; // ecx
  int v26; // eax
  _DWORD *v27; // edx
  _DWORD *v28; // ecx
  _DWORD *output; // eax
  int v30; // eax
  int v31; // edi
  int v32; // ecx
  int v33; // ecx
  int v34; // eax
  unsigned int v35; // edi
  int v36; // esi
  unsigned int v37; // edx
  int v38; // edx
  _DWORD *v39; // eax
  unsigned int v40; // edx
  int v41; // edx
  __int64 v42; // xmm2_8
  double v43; // xmm1_8
  __int64 v44; // xmm0_8
  __int64 *v45; // eax
  __int64 *v46; // eax
  unsigned int v47; // edx
  __int64 *v48; // edx
  __int64 v49; // xmm1_8
  int v50; // eax
  double v51; // xmm0_8
  __int64 *v52; // eax
  int v53; // ecx
  __int64 v54; // xmm2_8
  BOOL v55; // eax
  int v56; // eax
  int v57; // eax
  __int64 *v58; // edi
  int v59; // eax
  _DWORD *v60; // eax
  unsigned int v61; // edx
  int v62; // edx
  _DWORD *v63; // eax
  unsigned int v64; // edx
  int v65; // edx
  _DWORD *v66; // eax
  unsigned int v67; // edx
  int v68; // edx
  __m128d v69; // xmm6
  double v70; // xmm5_8
  __m128d v71; // xmm4
  __m128d v72; // xmm3
  double v73; // xmm0_8
  double v74; // xmm2_8
  __m128d v75; // xmm0
  __int64 *v76; // eax
  unsigned int v77; // edx
  _DWORD *v78; // edx
  __int64 v79; // xmm0_8
  __int64 *v80; // eax
  __int64 v81; // xmm1_8
  __int64 *v82; // eax
  int v83; // ecx
  __int64 v84; // xmm2_8
  BOOL v85; // eax
  int v86; // eax
  __int64 v87; // xmm0_8
  int v88; // eax
  __int64 *v89; // edi
  int v90; // eax
  unsigned int v91; // eax
  unsigned int v92; // edx
  unsigned int v93; // eax
  int v94; // edx
  int v95; // eax
  int v96; // eax
  _DWORD *v97; // edx
  int v98; // eax
  __m128i v99; // xmm0
  __int64 *v100; // eax
  int v101; // edx
  int v102; // eax
  int v103; // edi
  _DWORD *v104; // eax
  unsigned int v105; // edx
  int v106; // edx
  int v107; // eax
  int v108; // eax
  int v109; // eax
  int v110; // edx
  int v111; // edi
  int v112; // eax
  __int64 *v113; // eax
  int v114; // edx
  __int64 *v115; // ecx
  unsigned int v116; // eax
  int *function; // edx
  int v118; // eax
  __int16 v119; // ax
  int *v120; // edx
  int v121; // eax
  int v122; // eax
  double v123; // xmm1_8
  __m128d v124; // xmm2
  int v125; // eax
  double v126; // xmm3_8
  bool v127; // cf
  int v128; // eax
  __int64 *v129; // edx
  int v130; // eax
  __int64 *v131; // edi
  int v132; // eax
  __int64 *v133; // eax
  __int64 v134; // xmm0_8
  __int64 v135; // xmm2_8
  int *v136; // eax
  double v137; // xmm1_8
  int v138; // esi
  _DWORD *v139; // ecx
  _DWORD *v140; // esi
  int v141; // eax
  int v142; // edx
  int v143; // edx
  __int64 *v144; // eax
  int v145; // edx
  _DWORD *v146; // edi
  _DWORD *v147; // eax
  int v148; // ecx
  char v149; // al
  int v150; // ecx
  int v151; // esi
  int v152; // eax
  bool v153; // cc
  int *v154; // esi
  __int64 *v155; // edx
  int v156; // ecx
  int v157; // eax
  int v158; // eax
  _DWORD *v159; // edx
  char *v160; // ecx
  int v161; // edx
  int v162; // eax
  int v163; // eax
  int v164; // eax
  int v165; // esi
  signed int v166; // ecx
  int v167; // edi
  __int64 *v168; // eax
  __int64 *v169; // esi
  int v170; // ecx
  unsigned int *v171; // edi
  _DWORD *v172; // eax
  _DWORD *v173; // edx
  unsigned int v174; // eax
  int v175; // edi
  int v176; // ecx
  int v177; // esi
  int v178; // eax
  int v179; // edx
  _DWORD *v180; // edx
  _DWORD *v181; // eax
  int v182; // eax
  unsigned int v183; // eax
  unsigned int v184; // edx
  int v185; // eax
  int v186; // eax
  _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // edx
  unsigned int v188; // ecx
  char v189; // cl
  _DWORD *v190; // [esp-130h] [ebp-13Ch]
  __int64 *v191; // [esp-12Ch] [ebp-138h]
  __int64 *v192; // [esp-12Ch] [ebp-138h]
  __int64 *v193; // [esp-12Ch] [ebp-138h]
  __int64 *v194; // [esp-12Ch] [ebp-138h]
  int v195; // [esp-128h] [ebp-134h]
  int v196; // [esp-124h] [ebp-130h]
  int nres; // [esp-124h] [ebp-130h]
  int v198; // [esp-124h] [ebp-130h]
  int v199; // [esp-124h] [ebp-130h]
  __int64 v200; // [esp-F8h] [ebp-104h] BYREF
  int v201; // [esp-F0h] [ebp-FCh]
  _DWORD environment[4]; // [esp-E8h] [ebp-F4h] BYREF
  __int64 v203; // [esp-D8h] [ebp-E4h] BYREF
  int v204; // [esp-D0h] [ebp-DCh]
  __int64 v205; // [esp-C8h] [ebp-D4h] BYREF
  int v206; // [esp-C0h] [ebp-CCh]
  __int64 v207; // [esp-B8h] [ebp-C4h] BYREF
  int v208; // [esp-B0h] [ebp-BCh]
  __int64 v209; // [esp-A8h] [ebp-B4h]
  int v210; // [esp-A0h] [ebp-ACh]
  _DWORD v211[4]; // [esp-98h] [ebp-A4h] BYREF
  double v212; // [esp-88h] [ebp-94h] BYREF
  double v213; // [esp-80h] [ebp-8Ch] BYREF
  double v214; // [esp-78h] [ebp-84h] BYREF
  __int128 v215; // [esp-70h] [ebp-7Ch]
  double v216; // [esp-60h] [ebp-6Ch] BYREF
  double v217; // [esp-58h] [ebp-64h] BYREF
  double v218; // [esp-50h] [ebp-5Ch] BYREF
  double v219; // [esp-48h] [ebp-54h] BYREF
  double v220; // [esp-40h] [ebp-4Ch] BYREF
  int instructions; // [esp-38h] [ebp-44h]
  int v222; // [esp-34h] [ebp-40h]
  char *enc_savedpc_; // [esp-30h] [ebp-3Ch]
  unsigned int v224; // [esp-2Ch] [ebp-38h]
  int encrypted_index; // [esp-28h] [ebp-34h]
  int l_ci_1; // [esp-24h] [ebp-30h]
  int table; // [esp-20h] [ebp-2Ch]
  int constant; // [esp-1Ch] [ebp-28h]
  int *program_counter_; // [esp-18h] [ebp-24h]
  unsigned int instruction_ptr_; // [esp-14h] [ebp-20h]
  __int64 *nresults; // [esp-10h] [ebp-1Ch]
  __int64 *v232; // [esp-Ch] [ebp-18h]
  int v233; // [esp-8h] [ebp-14h]
  unsigned int base; // [esp-4h] [ebp-10h]
  int v235; // [esp+0h] [ebp-Ch]
  _BYTE *v236; // [esp+4h] [ebp-8h]
  _BYTE *retaddr; // [esp+Ch] [ebp+0h]

  v235 = v2;
  v236 = retaddr;
  rL_ = rL;
  enc_savedpc = (_DWORD *)(rL + 20);
  v5 = (_DWORD *)(rL + 8);
  enc_savedpc_ = (char *)(rL + 20);
  v222 = rL + 8;
re_entry:
  v6.m128d_f64[0] = 4.503599627370496e15;
LABEL_3:
  program_counter = (_DWORD *)((char *)enc_savedpc + *enc_savedpc);
  l_ci = **(_DWORD **)(*(_DWORD *)(rL_ + 12) + 16);
  base = *(_DWORD *)(rL_ + 28);
  l_ci_1 = l_ci;                                // +12 = func
  enc_closure_ci = *(_DWORD *)(l_ci + 16);
  v10 = (_DWORD *)((char *)v5 + *v5 + 28);
  constant = enc_closure_ci + l_ci_1 + 48 + *(_DWORD *)(enc_closure_ci + l_ci_1 + 48);
  encrypted_index = (int)v10 + *v10;
  instructions = enc_closure_ci + l_ci_1 + 40 + *(_DWORD *)(enc_closure_ci + l_ci_1 + 40);
  v224 = encrypted_index + 2;
LABEL_4:
  rL_ = rL;
continue:
  stack = base;
  while ( 1 )
  {
    nresults = (__int64 *)(((int)program_counter - instructions) >> 2);
    program_counter__1 = program_counter++;
    instruction_ptr = encrypted_index * *program_counter__1;
    program_counter_ = program_counter;
    instruction_ptr_ = instruction_ptr;
    if ( v224 < 4 )
      break;
    v14 = *(_BYTE *)(rL_ + 57);
    if ( (v14 & 0xC) != 0 )
    {
      v15 = (*(_DWORD *)(rL_ + 92))-- == 1;
      if ( v15 || (v14 & 4) != 0 )
      {
        sub_14ACF0(rL_, program_counter);
        if ( *(_BYTE *)(rL_ + 6) == 1 )
        {
          *(_DWORD *)enc_savedpc_ = (char *)program_counter - enc_savedpc_ - 4;
          return;
        }
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        instruction_ptr = instruction_ptr_;
        base = stack;
      }
    }
    switch ( instruction_ptr >> 26 )            // opcode index
    {
      case 0u:                                  // OP_LOADBOOL
        new_stack_value = (unsigned int *)(base + 16 * (unsigned __int8)(instruction_ptr >> 18));// A register
        *new_stack_value = instruction_ptr & 0x1FF;// B register
        new_stack_value[2] = 3;                 // boolean
        if ( (instruction_ptr & 0x3FE00) == 0 ) // if not GETARG_C
          goto LABEL_273;
        ++program_counter;
        goto continue;
      case 1u:                                  // OP_GETTABLE
        table = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - enc_savedpc_;
        if ( ((instruction_ptr >> 9) & 256) != 0 )// if constant
          v24 = constant + 16 * (unsigned __int8)(instruction_ptr >> 9);
        else                                    // if stack
          v24 = stack + 16 * ((instruction_ptr >> 9) & 0x1FF);
        luaV_gettable(rL_, (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF)), v24, (_DWORD *)table);
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 2u:
        stack_value_new = *(_DWORD **)(*(_DWORD *)(l_ci_1 + 4 * (instruction_ptr & 0x1FF) + 20) + 8);// GETARG_B
        goto move_stack_value;
      case 3u:                                  // OP_SETGLOBAL
        v211[2] = 7;                            // table
        v211[0] = *(_DWORD *)(l_ci_1 + 12);     // environment
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - enc_savedpc_;
        luaV_settable(
          rL_,
          (int)v211,
          (_DWORD *)(constant + 16 * (instruction_ptr & 0x3FFFF)),
          (_DWORD *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18)));
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 4u:                                  // OP_LOADK
        stack_value_new = (_DWORD *)(constant + 16 * (instruction_ptr & 0x3FFFF));// sBx
move_stack_value:
        a = (_DWORD *)(base + 16 * (unsigned __int8)(instruction_ptr >> 18));// GETARG_A
        *a = *stack_value_new;
        a[1] = stack_value_new[1];
        a[2] = stack_value_new[2];
        goto continue;
      case 5u:
        table = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        v25 = *(_DWORD **)(l_ci_1 + 4 * (instruction_ptr & 0x1FF) + 20);
        v26 = *(_DWORD *)table;
        v27 = (_DWORD *)table;
        v233 = (int)v25;
        v28 = (_DWORD *)v25[2];
        *v28 = v26;
        v28[1] = v27[1];
        v28[2] = v27[2];
        if ( (int)v27[2] < 4 || (*(_BYTE *)(*v27 + 4) & 3) == 0 || (*(_BYTE *)(v233 + 4) & 4) == 0 )
          goto LABEL_273;
        sub_13EE10(rL_, v233, *v27);
        v6.m128d_f64[0] = 4.503599627370496e15;
        goto continue;
      case 6u:
        v16 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v17 = (_DWORD *)(base + 16 * (unsigned __int8)(instruction_ptr_ >> 18));
        v15 = (instruction_ptr_ & 0x3FE00) == 0;
        *v17 = *v16;
        v17[1] = v16[1];
        v17[2] = v16[2];
        if ( v15 )
          v18 = *(_DWORD *)(rL_ + 28);
        else
          v18 = *(_DWORD *)(rL_ + 16);
        program_counter = program_counter_;
        *(_DWORD *)(rL_ + 16) = v18;
        goto continue;
      case 7u:
        v21 = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        v22 = stack + 16 * (instruction_ptr & 0x1FF);
        do
        {
          *(_DWORD *)(v22 + 8) = 0;
          v22 -= 16;
        }
        while ( v22 >= v21 );
        continue;
      case 8u:                                  // OP_GETGLOBAL
        environment[2] = 7;
        environment[0] = *(_DWORD *)(l_ci_1 + 12);
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - enc_savedpc_;
        luaV_gettable(
          rL_,
          environment,
          constant + 16 * (instruction_ptr & 0x3FFFF),
          (_DWORD *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18)));
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 9u:                                  // OP_SELF
        v233 = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        v36 = v233;
        v232 = (__int64 *)(stack + 16 * (instruction_ptr & 0x1FF));
        *(_DWORD *)(v233 + 16) = *(_DWORD *)v232;
        v37 = instruction_ptr >> 9;
        *(_DWORD *)(v36 + 20) = *((_DWORD *)v232 + 1);
        *(_DWORD *)(v36 + 24) = *((_DWORD *)v232 + 2);
        rL_ = rL;
        *(_DWORD *)(rL + 20) = (char *)program_counter - enc_savedpc_;
        if ( (v37 & 0x100) != 0 )               // if constant
          v38 = constant + 16 * (unsigned __int8)v37;
        else                                    // stack
          v38 = stack + 16 * (v37 & 0x1FF);
        luaV_gettable(rL, v232, v38, (_DWORD *)v233);
        stack = *(_DWORD *)(rL + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 10u:                                 // OP_DIV
        v232 = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( (instruction_ptr & 0x100) != 0 )
          v63 = (_DWORD *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v63 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v64 = instruction_ptr >> 9;
        v233 = (int)v63;
        if ( (v64 & 0x100) != 0 )
          v65 = constant + 16 * (unsigned __int8)v64;
        else
          v65 = stack + 16 * (v64 & 0x1FF);
        if ( v63[2] == 2 && *(_DWORD *)(v65 + 8) == 2 )
        {
          v42 = xor_constant;
          v43 = COERCE_DOUBLE(*(_QWORD *)v63 ^ xor_constant) / COERCE_DOUBLE(*(_QWORD *)v65 ^ xor_constant);
          goto LABEL_61;
        }
        v193 = (__int64 *)v233;                 // doesnt run unless not number
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        sub_13B0B0(rL_, (int)v232, v193, (__int64 *)v65, 6);
        goto LABEL_152;
      case 11u:                                 // OP_SUB
        nresults = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( (instruction_ptr & 0x100) != 0 )
          v46 = (__int64 *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v46 = (__int64 *)(stack + 16 * (instruction_ptr & 0x1FF));
        v47 = instruction_ptr >> 9;
        v232 = v46;
        if ( (v47 & 0x100) != 0 )
          v48 = (__int64 *)(constant + 16 * (unsigned __int8)v47);
        else
          v48 = (__int64 *)(stack + 16 * (v47 & 0x1FF));
        v15 = *((_DWORD *)v46 + 2) == 2;
        instruction_ptr_ = (unsigned int)v48;
        if ( v15 && *((_DWORD *)v48 + 2) == 2 )
        {
          v49 = *v46;
          v50 = (int)nresults;
          v51 = COERCE_DOUBLE(v49 ^ xor_constant) - COERCE_DOUBLE(*v48 ^ xor_constant);
          v6.m128d_f64[0] = 4.503599627370496e15;
          *nresults = *(_QWORD *)&v51 ^ xor_constant;
          *(_DWORD *)(v50 + 8) = 2;
          continue;
        }
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v52 = v232;
        v53 = *((_DWORD *)v232 + 2);
        if ( v53 == 2 )
        {
          v54 = xor_constant;
        }
        else
        {
          if ( v53 != 4 )
            goto LABEL_85;
          v55 = sub_142470((unsigned __int8 *)(*(_DWORD *)v232 + 24), &v212);
          v48 = (__int64 *)instruction_ptr_;
          if ( !v55 )
            goto LABEL_85;
          v54 = xor_constant;
          v200 = *(_QWORD *)&v212 ^ xor_constant;
          v201 = 2;
          v52 = &v200;
        }
        v233 = (int)v52;
        v56 = *((_DWORD *)v48 + 2);
        if ( v56 == 2 )
          goto LABEL_83;
        if ( v56 == 4 )
        {
          if ( sub_142470((unsigned __int8 *)(*(_DWORD *)v48 + 24), &v220) )
          {
            v54 = xor_constant;
            v205 = *(_QWORD *)&v220 ^ xor_constant;
            v206 = 2;
            v48 = &v205;
LABEL_83:
            v57 = (int)nresults;
            v6.m128d_f64[0] = 4.503599627370496e15;
            *nresults = COERCE_UNSIGNED_INT64(COERCE_DOUBLE(*(_QWORD *)v233 ^ v54) - COERCE_DOUBLE(*v48 ^ v54)) ^ v54;
            *(_DWORD *)(v57 + 8) = 2;
            stack = *(_DWORD *)(rL_ + 28);
            base = stack;
            continue;
          }
          v48 = (__int64 *)instruction_ptr_;
        }
LABEL_85:
        if ( !sub_13C960((_DWORD *)rL_, v232, v48, (int)nresults, 10) )
        {
          v58 = v232;
          v59 = *((_DWORD *)v232 + 2);
          if ( v59 == 2 || v59 == 4 && sub_142470((unsigned __int8 *)(*(_DWORD *)v232 + 24), &v217) )
            v58 = (__int64 *)instruction_ptr_;
          luaG_typeerror(rL_, (int)v58);
        }
LABEL_152:
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 12u:                                 // OP_MOD
        v232 = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( (instruction_ptr & 0x100) != 0 )
          v66 = (_DWORD *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v66 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v67 = instruction_ptr >> 9;
        v233 = (int)v66;
        if ( (v67 & 0x100) != 0 )
          v68 = constant + 16 * (unsigned __int8)v67;
        else
          v68 = stack + 16 * (v67 & 0x1FF);
        if ( v66[2] == 2 && *(_DWORD *)(v68 + 8) == 2 )
        {
          v69 = _mm_xor_pd((__m128d)*(unsigned __int64 *)v66, (__m128d)xor_constant);
          *(_QWORD *)&v70 = *(_QWORD *)v68 ^ xor_constant;
          v71.m128d_f64[1] = v69.m128d_f64[1];
          v71.m128d_f64[0] = v69.m128d_f64[0] / v70;
          v72 = _mm_and_pd((__m128d)0x8000000000000000ui64, v71);
          v73 = _mm_cmplt_sd(_mm_xor_pd(v71, v72), v6).m128d_f64[0];
          v74 = v69.m128d_f64[0] / v70
              + COERCE_DOUBLE(*(_QWORD *)&v73 & 0x4330000000000000i64 | *(_QWORD *)&v72.m128d_f64[0])
              - COERCE_DOUBLE(*(_QWORD *)&v73 & 0x4330000000000000i64 | *(_QWORD *)&v72.m128d_f64[0]);
          v75.m128d_f64[1] = v69.m128d_f64[1];
          v75.m128d_f64[0] = v74 - v69.m128d_f64[0] / v70;
          v44 = COERCE_UNSIGNED_INT64(
                  v69.m128d_f64[0]
                - (v74 - COERCE_DOUBLE(*(_OWORD *)&_mm_cmpgt_sd(v75, v72) & 0x3FF0000000000000i64)) * v70) ^ xor_constant;
          goto LABEL_62;
        }
        v194 = (__int64 *)v233;
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        sub_13B0B0(rL_, (int)v232, v194, (__int64 *)v68, 8);
        goto LABEL_152;
      case 13u:                                 // OP_NEWTABLE
        v30 = (instruction_ptr >> 9) & 0x1FF;
        v31 = instruction_ptr & 0x1FF;
        instruction_ptr_ = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        v32 = (v30 >> 3) & 0x1F;
        if ( v32 )
          v30 = (((instruction_ptr >> 9) & 7) + 8) << (v32 - 1);
        v33 = (v31 >> 3) & 0x1F;
        if ( v33 )
          v31 = ((instruction_ptr & 7) + 8) << (v33 - 1);
        v34 = luaH_new(rL_, v31, v30);
        v35 = instruction_ptr_;
        *(_DWORD *)instruction_ptr_ = v34;
        *(_DWORD *)(v35 + 8) = 7;
        program_counter = program_counter_;
        *(_DWORD *)(rL_ + 20) = (char *)program_counter_ - rL_ - 20;
        if ( *(_DWORD *)(*(_DWORD *)(rL_ + 8) + rL_ + 96) < *(_DWORD *)(*(_DWORD *)(rL_ + 8) + rL_ + 84) )
          goto LABEL_152;
        luaC_step(rL_);
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 14u:                                 // something with numbers but my ida fucked up
        nresults = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( (instruction_ptr & 0x100) != 0 )
          v76 = (__int64 *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v76 = (__int64 *)(stack + 16 * (instruction_ptr & 0x1FF));
        v77 = instruction_ptr >> 9;
        v232 = v76;
        if ( (v77 & 0x100) != 0 )
          v78 = (_DWORD *)(constant + 16 * (unsigned __int8)v77);
        else
          v78 = (_DWORD *)(stack + 16 * (v77 & 0x1FF));
        v15 = *((_DWORD *)v76 + 2) == 2;
        instruction_ptr_ = (unsigned int)v78;
        if ( v15 && v78[2] == 2 )
        {
          v79 = *v76 ^ xor_constant;
          v215 = xor_constant;
          sub_9307B8();
          v80 = nresults;
          v81 = v79 ^ v215;
          goto LABEL_130;
        }
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v82 = v232;
        v83 = *((_DWORD *)v232 + 2);
        if ( v83 == 2 )
        {
          v84 = xor_constant;
        }
        else
        {
          if ( v83 != 4 )
            goto LABEL_142;
          v85 = sub_142470((unsigned __int8 *)(*(_DWORD *)v232 + 24), &v213);
          v78 = (_DWORD *)instruction_ptr_;
          if ( !v85 )
            goto LABEL_142;
          v84 = xor_constant;
          v203 = *(_QWORD *)&v213 ^ xor_constant;
          v204 = 2;
          v82 = &v203;
        }
        v233 = (int)v82;
        v86 = v78[2];
        if ( v86 == 2 )
          goto LABEL_140;
        if ( v86 == 4 )
        {
          if ( sub_142470((unsigned __int8 *)(*v78 + 24), &v219) )
          {
            v84 = xor_constant;
            v209 = *(_QWORD *)&v219 ^ xor_constant;
            v210 = 2;
LABEL_140:
            v87 = *(_QWORD *)v233 ^ v84;
            sub_9307B8();
            v88 = (int)nresults;
            *nresults = v87 ^ xor_constant;
            v6.m128d_f64[0] = 4.503599627370496e15;
            *(_DWORD *)(v88 + 8) = 2;
            stack = *(_DWORD *)(rL_ + 28);
            base = stack;
            continue;
          }
          v78 = (_DWORD *)instruction_ptr_;
        }
LABEL_142:
        if ( !sub_13C960((_DWORD *)rL_, v232, v78, (int)nresults, 11) )
        {
          v89 = v232;
          v90 = *((_DWORD *)v232 + 2);
          if ( v90 == 2 || v90 == 4 && sub_142470((unsigned __int8 *)(*(_DWORD *)v232 + 24), &v218) )
            v89 = (__int64 *)instruction_ptr_;
          luaG_typeerror(rL_, (int)v89);
        }
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 15u:                                 // OP_SETTABLE
        table = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - enc_savedpc_;
        if ( ((instruction_ptr >> 9) & 256) != 0 )// constant
          output = (_DWORD *)(constant + 16 * (unsigned __int8)(instruction_ptr >> 9));
        else                                    // stack
          output = (_DWORD *)(stack + 16 * ((instruction_ptr >> 9) & 0x1FF));
        if ( (instruction_ptr & 256) != 0 )     // godly compiler, if constant
          luaV_settable(rL_, table, (_DWORD *)(constant + 16 * (unsigned __int8)instruction_ptr), output);
        else                                    // if stack
          luaV_settable(rL_, table, (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF)), output);
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 16u:                                 // OP_ADD
        v232 = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( (instruction_ptr & 0x100) != 0 )
          v39 = (_DWORD *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v39 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v40 = instruction_ptr >> 9;
        v233 = (int)v39;
        if ( (v40 & 0x100) != 0 )
          v41 = constant + 16 * (unsigned __int8)v40;
        else
          v41 = stack + 16 * (v40 & 0x1FF);
        if ( v39[2] == 2 && *(_DWORD *)(v41 + 8) == 2 )
        {
          v42 = xor_constant;
          v43 = COERCE_DOUBLE(*(_QWORD *)v41 ^ xor_constant) + COERCE_DOUBLE(*(_QWORD *)v39 ^ xor_constant);
          goto LABEL_61;
        }
        v191 = (__int64 *)v233;
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        sub_13B0B0(rL_, (int)v232, v191, (__int64 *)v41, 7);
        goto LABEL_152;
      case 17u:                                 // OP_MUL
        v232 = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( (instruction_ptr & 0x100) != 0 )
          v60 = (_DWORD *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v60 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v61 = instruction_ptr >> 9;
        v233 = (int)v60;
        if ( (v61 & 0x100) != 0 )
          v62 = constant + 16 * (unsigned __int8)v61;
        else
          v62 = stack + 16 * (v61 & 0x1FF);
        if ( v60[2] != 2 || *(_DWORD *)(v62 + 8) != 2 )
        {
          v192 = (__int64 *)v233;
          *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
          sub_13B0B0(rL_, (int)v232, v192, (__int64 *)v62, 5);
          goto LABEL_152;
        }
        v42 = xor_constant;
        v43 = COERCE_DOUBLE(*(_QWORD *)v62 ^ xor_constant) * COERCE_DOUBLE(*(_QWORD *)v60 ^ xor_constant);
LABEL_61:
        v44 = *(_QWORD *)&v43 ^ v42;
LABEL_62:
        v45 = v232;
        goto LABEL_63;
      case 18u:
        v96 = (unsigned __int8)(instruction_ptr >> 18);
        v97 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v232 = (__int64 *)(stack + 16 * v96);
        v98 = v97[2];
        instruction_ptr_ = (unsigned int)v97;
        if ( v98 == 4 )
        {
          v100 = v232;
          *v232 = COERCE_UNSIGNED_INT64((double)*(unsigned int *)(*v97 + 8)) ^ xor_constant;
          v6.m128d_f64[0] = 4.503599627370496e15;
          *((_DWORD *)v100 + 2) = 2;
          continue;
        }
        if ( v98 != 7 )
        {
          *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
          if ( !sub_13C960((_DWORD *)rL_, v97, luaO_nilobject, (int)v232, 13) )
            luaG_typeerror(rL_, instruction_ptr_);
          goto LABEL_152;
        }
        v99 = _mm_cvtsi32_si128(sub_140740(*v97));
        v80 = v232;
        v81 = *(_OWORD *)&_mm_cvtepi32_pd(v99) ^ xor_constant;
LABEL_130:
        *v80 = v81;
        v6.m128d_f64[0] = 4.503599627370496e15;
        *((_DWORD *)v80 + 2) = 2;
        goto continue;
      case 19u:
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        if ( ((instruction_ptr >> 9) & 0x100) != 0 )
          v108 = constant + 16 * (unsigned __int8)(instruction_ptr >> 9);
        else
          v108 = stack + 16 * ((instruction_ptr >> 9) & 0x1FF);
        if ( (instruction_ptr & 0x100) != 0 )
          v107 = sub_144CC0(rL_, constant + 16 * (unsigned __int8)instruction_ptr, v108);
        else
          v107 = sub_144CC0(rL_, stack + 16 * (instruction_ptr & 0x1FF), v108);
        goto LABEL_193;
      case 20u:
        program_counter = &program_counter[(instruction_ptr & 0x3FFFF) - 0x1FFFF];
        if ( (unsigned int)(retaddr - (_BYTE *)off_E41000) < 0xBAB3CA
          || (unsigned int)(retaddr - (_BYTE *)off_DB02F0) < 0x122AC0 )
        {
          goto LABEL_273;
        }
        dword_107AF28 |= 0x200000u;
        dword_16358C4 = 0;
        sub_14BB70(rL_);
        v6.m128d_f64[0] = 4.503599627370496e15;
        goto continue;
      case 21u:
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        if ( ((instruction_ptr >> 9) & 0x100) != 0 )
          v109 = constant + 16 * (unsigned __int8)(instruction_ptr >> 9);
        else
          v109 = stack + 16 * ((instruction_ptr >> 9) & 0x1FF);
        if ( (instruction_ptr & 0x100) != 0 )
          v110 = constant + 16 * (unsigned __int8)instruction_ptr;
        else
          v110 = stack + 16 * (instruction_ptr & 0x1FF);
        v107 = sub_13E9E0(rL_, v110, v109);
        goto LABEL_193;
      case 22u:
        v93 = instruction_ptr >> 18;
        v94 = 2 * (instruction_ptr & 0x1FF);
        v95 = 2 * (unsigned __int8)v93;
        if ( *(_DWORD *)(stack + 8 * v94 + 8) && (*(_DWORD *)(stack + 8 * v94 + 8) != 3 || *(_DWORD *)(stack + 8 * v94)) )
        {
          *(_DWORD *)(stack + 8 * v95) = 0;
          *(_DWORD *)(stack + 8 * v95 + 8) = 3;
        }
        else
        {
          *(_DWORD *)(stack + 8 * v95) = 1;
          *(_DWORD *)(stack + 8 * v95 + 8) = 3;
        }
        continue;
      case 23u:
        v112 = !*(_DWORD *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18) + 8)
            || *(_DWORD *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18) + 8) == 3
            && !*(_DWORD *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        if ( v112 != ((instruction_ptr >> 9) & 0x1FF) )
          goto LABEL_204;
        goto LABEL_208;
      case 24u:
        v91 = instruction_ptr >> 18;
        v92 = stack + 16 * (instruction_ptr & 0x1FF);
        v45 = (__int64 *)(stack + 16 * (unsigned __int8)v91);
        v15 = *(_DWORD *)(v92 + 8) == 2;
        table = (int)v45;
        if ( !v15 )
        {
          v190 = (_DWORD *)table;
          *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
          sub_13B0B0(rL_, (int)v190, (__int64 *)v92, (__int64 *)v92, 9);
          goto LABEL_152;
        }
        v44 = COERCE_UNSIGNED_INT64(-COERCE_DOUBLE(*(_QWORD *)v92 ^ xor_constant)) ^ xor_constant;
LABEL_63:
        v6.m128d_f64[0] = 4.503599627370496e15;
        *v45 = v44;
        *((_DWORD *)v45 + 2) = 2;
        continue;
      case 25u:
        v233 = instruction_ptr & 0x1FF;
        v196 = (instruction_ptr >> 9) & 0x1FF;
        v195 = v196 - v233 + 1;
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        sub_142A50(rL_, v195, v196);
        if ( *(_DWORD *)(*(_DWORD *)(rL_ + 8) + rL_ + 96) >= *(_DWORD *)(*(_DWORD *)(rL_ + 8) + rL_ + 84) )
          luaC_step(rL_);
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        v101 = 2 * v233;
        v102 = *(_DWORD *)(stack + 16 * v233);
        v103 = 2 * (unsigned __int8)(instruction_ptr_ >> 18);
        base = stack;
        *(_DWORD *)(stack + 8 * v103) = v102;
        *(_DWORD *)(stack + 8 * v103 + 4) = *(_DWORD *)(stack + 8 * v101 + 4);
        *(_DWORD *)(stack + 8 * v103 + 8) = *(_DWORD *)(stack + 8 * v101 + 8);
        program_counter = program_counter_;
        continue;
      case 26u:
        if ( (instruction_ptr & 0x100) != 0 )
          v104 = (_DWORD *)(constant + 16 * (unsigned __int8)instruction_ptr);
        else
          v104 = (_DWORD *)(stack + 16 * (instruction_ptr & 0x1FF));
        v105 = instruction_ptr >> 9;
        v233 = (int)v104;
        if ( (v105 & 0x100) != 0 )
          v106 = constant + 16 * (unsigned __int8)v105;
        else
          v106 = stack + 16 * (v105 & 0x1FF);
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v107 = *(_DWORD *)(v233 + 8) == *(_DWORD *)(v106 + 8) && sub_142D60(rL_, v233, v106);
LABEL_193:
        v111 = (int)program_counter_;
        if ( v107 == (unsigned __int8)(instruction_ptr_ >> 18) )
        {
          v111 = (int)&program_counter_[((encrypted_index * *program_counter_) & 0x3FFFF) - 0x1FFFF];
          if ( (unsigned int)(retaddr - (_BYTE *)off_E41000) >= 0xBAB3CA
            && (unsigned int)(retaddr - (_BYTE *)off_DB02F0) >= 0x122AC0 )
          {
            dword_107AF28 |= 0x200000u;
            dword_16358C4 = 0;
            sub_14BB70(rL_);
          }
        }
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        program_counter = (int *)(v111 + 4);
        continue;
      case 27u:
        nresults -= 3724935 * instruction_ptr;
        v119 = (6907 * instruction_ptr + 10891) ^ (unsigned __int16)nresults;
        v120 = (int *)(stack
                     + 16
                     * (unsigned __int8)((((21306107 * instruction_ptr - 27776373) ^ (unsigned int)nresults) & 0x3FFFFFF | 0x6C000000) >> 18));
        v121 = v119 & 0x1FF;
        if ( v121 )
          *(_DWORD *)(rL_ + 16) = &v120[4 * v121];
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v122 = luaD_precall(rL_, v120, -1);
        if ( !v122 )
        {
          v171 = (unsigned int *)(*(_DWORD *)(rL_ + 12) - 24);
          v15 = *(_DWORD *)(rL_ + 120) == 0;
          v172 = (_DWORD *)v171[4];
          v173 = (_DWORD *)v171[10];
          v224 = (unsigned int)v171;
          v233 = (int)v172;
          table = (int)v173;
          if ( !v15 )
          {
            sub_13FDB0(rL_, v171[3]);
            v173 = (_DWORD *)table;
          }
          v174 = ((v171[9] - (_DWORD)v173) & 0xFFFFFFF0) + v171[4];
          v171[3] = v174;
          v175 = 0;
          *(_DWORD *)(rL_ + 28) = v174;
          if ( (unsigned int)v173 < *(_DWORD *)(rL_ + 16) )
          {
            v176 = 0;
            do
            {
              v177 = v233;
              ++v175;
              *(_DWORD *)(v176 + v233) = *v173;
              *(_DWORD *)(v176 + v177 + 4) = v173[1];
              v178 = v173[2];
              v179 = v177;
              rL_ = rL;
              *(_DWORD *)(v176 + v179 + 8) = v178;
              v176 = 16 * v175;
              v173 = (_DWORD *)(16 * v175 + table);
            }
            while ( (unsigned int)v173 < *(_DWORD *)(rL + 16) );
          }
          v180 = (_DWORD *)v224;
          v181 = (_DWORD *)(16 * v175 + v233);
          *(_DWORD *)(rL_ + 16) = v181;
          v180[2] = v181;
          v182 = *(_DWORD *)(rL_ + 20);
          ++v180[1];
          enc_savedpc = (_DWORD *)(rL_ + 20);
          *v180 = rL_ + 20 + v182;
          *(_DWORD *)(rL_ + 12) -= 24;
          v5 = (_DWORD *)(rL_ + 8);
          goto re_entry;
        }
        if ( v122 != 1 )
          return;
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        break;
      case 28u:
        v138 = (unsigned __int8)(instruction_ptr >> 18);
        v139 = (_DWORD *)(base + 16 * v138);
        v139[20] = v139[8];
        v139[21] = v139[9];
        v139[22] = v139[10];
        v139[16] = v139[4];
        v139[17] = v139[5];
        v139[18] = v139[6];
        v139[12] = *v139;
        v139[13] = v139[1];
        v139[14] = v139[2];
        *(_DWORD *)(rL + 16) = v139 + 24;
        v198 = (instruction_ptr_ >> 9) & 0x1FF;
        *(_DWORD *)enc_savedpc_ = (char *)program_counter - enc_savedpc_;
        luaD_call(rL, (int)(v139 + 12), v198);
        stack = *(_DWORD *)(rL + 28);
        v140 = (_DWORD *)(stack + 16 * (v138 + 3));
        *(_DWORD *)(rL + 16) = *(_DWORD *)(*(_DWORD *)(rL + 12) + 8);
        v15 = v140[2] == 0;
        base = stack;
        if ( v15 )
        {
          v6.m128d_f64[0] = 4.503599627370496e15;
          rL_ = rL;
          program_counter = program_counter_ + 1;
        }
        else
        {
          program_counter = program_counter_;
          *(v140 - 4) = *v140;
          *(v140 - 3) = v140[1];
          *(v140 - 2) = v140[2];
          rL_ = rL;
LABEL_204:
          program_counter = &program_counter[((encrypted_index * *program_counter) & 0x3FFFF) - 0x1FFFF];
          if ( (unsigned int)(retaddr - (_BYTE *)off_E41000) >= 0xBAB3CA
            && (unsigned int)(retaddr - (_BYTE *)off_DB02F0) >= 0x122AC0 )
          {
            dword_107AF28 |= 0x200000u;
            dword_16358C4 = 0;
            sub_14BB70(rL_);
          }
          stack = base;
LABEL_208:
          v6.m128d_f64[0] = 4.503599627370496e15;
          ++program_counter;
        }
        continue;
      case 29u:
        table = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        *(_QWORD *)&v123 = *(_QWORD *)(table + 32) ^ xor_constant;
        v124 = _mm_xor_pd((__m128d)*(unsigned __int64 *)table, (__m128d)xor_constant);
        v124.m128d_f64[0] = v124.m128d_f64[0] + v123;
        v125 = 0;
        *(_QWORD *)&v126 = *(_QWORD *)(table + 16) ^ xor_constant;
        v215 = (__int128)v124;
        if ( v123 <= 0.0 )
          v127 = v124.m128d_f64[0] < v126;
        else
          v127 = v126 < v124.m128d_f64[0];
        v6.m128d_f64[0] = 4.503599627370496e15;
        LOBYTE(v125) = !v127;
        if ( !v125 )
          continue;
        program_counter = &program_counter[(instruction_ptr & 0x3FFFF) - 0x1FFFF];
        if ( (unsigned int)(retaddr - (_BYTE *)off_E41000) >= 0xBAB3CA
          && (unsigned int)(retaddr - (_BYTE *)off_DB02F0) >= 0x122AC0 )
        {
          dword_107AF28 |= 0x200000u;
          dword_16358C4 = 0;
          sub_14BB70(rL_);
          *(_QWORD *)&v124.m128d_f64[0] = v215;
        }
        v128 = table;
        *(_QWORD *)table = *(_QWORD *)&v124.m128d_f64[0] ^ xor_constant;
        *(_DWORD *)(v128 + 8) = 2;
        *(_QWORD *)(v128 + 48) = *(_QWORD *)&v124.m128d_f64[0] ^ xor_constant;
        v6.m128d_f64[0] = 4.503599627370496e15;
        *(_DWORD *)(v128 + 56) = 2;
        goto continue;
      case 30u:
        v233 = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        v141 = instruction_ptr & 0x1FF;
        v142 = (instruction_ptr >> 9) & 0x1FF;
        instruction_ptr_ = v141;
        if ( !v141 )
        {
          instruction_ptr_ = ((*(_DWORD *)(rL_ + 16) - v233) >> 4) - 1;
          *(_DWORD *)(rL_ + 16) = *(_DWORD *)(*(_DWORD *)(rL_ + 12) + 8);
        }
        if ( !v142 )
        {
          v143 = *program_counter++;
          v142 = encrypted_index * v143;
          program_counter_ = program_counter;
        }
        if ( *(_DWORD *)(v233 + 8) != 7 )
          continue;
        nresults = *(__int64 **)v233;
        v144 = (__int64 *)(50 * v142 + instruction_ptr_ - 50);
        v145 = (int)nresults;
        v232 = v144;
        if ( (int)v144 > *((_DWORD *)nresults + 4) )
        {
          sub_140A60(rL_, (int)nresults, (int)v144);
          v145 = (int)nresults;
          stack = base;
          v144 = v232;
        }
        v6.m128d_f64[0] = 4.503599627370496e15;
        if ( (int)instruction_ptr_ <= 0 )
          continue;
        v146 = (_DWORD *)(v233 + 16 * instruction_ptr_);
        do
        {
          v147 = luaH_getnum(v145, (int)v144);
          if ( v147 == luaO_nilobject )
          {
            v207 = COERCE_UNSIGNED_INT64((double)(int)v232) ^ xor_constant;
            v208 = 2;
            v147 = sub_148C30(rL_, (int)nresults, &v207);
          }
          v148 = *v146;
          v232 = (__int64 *)((char *)v232 - 1);
          v145 = (int)nresults;
          *v147 = v148;
          v147[1] = v146[1];
          v147[2] = v146[2];
          if ( (int)v146[2] >= 4 && (*(_BYTE *)(*v146 + 4) & 3) != 0 )
          {
            v149 = *(_BYTE *)(v145 + 4);
            if ( (v149 & 4) != 0 )
            {
              v150 = v222 + *(_DWORD *)(rL_ + 8);
              *(_BYTE *)(v145 + 4) = v149 & 0xFB;
              *(_DWORD *)(v145 + 32) = *(_DWORD *)(v150 + 32);
              *(_DWORD *)(v150 + 32) = v145;
            }
          }
          v146 -= 4;
          --instruction_ptr_;
          v144 = v232;
        }
        while ( (int)instruction_ptr_ > 0 );
        goto LABEL_272;
      case 31u:                                 // OP_CALL
        nresults += 0xFFC72979 * instruction_ptr;
        v116 = ((0x1451AFB * instruction_ptr - 0x1A7D575) ^ (unsigned int)nresults) & 0x3FFFFFF | 0x7C000000;// call encryption LOL
        function = (int *)(stack + 16 * (unsigned __int8)(v116 >> 18));
        nresults = (__int64 *)(((v116 >> 9) & 0x1FF) - 1);
        if ( (v116 & 0x1FF) != 0 )
          *(_DWORD *)(rL_ + 16) = &function[4 * (v116 & 0x1FF)];
        nres = (int)nresults;
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v118 = luaD_precall(rL_, function, nres);
        if ( !v118 )
        {
          ++nexeccalls;
          enc_savedpc = (_DWORD *)(rL_ + 20);
          v5 = (_DWORD *)(rL_ + 8);
          goto re_entry;
        }
        if ( v118 != 1 )
          return;
        if ( (int)nresults >= 0 )
          *(_DWORD *)(rL_ + 16) = *(_DWORD *)(*(_DWORD *)(rL_ + 12) + 8);
        stack = *(_DWORD *)(rL_ + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      case 32u:
        sub_13FDB0(rL_, stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        v6.m128d_f64[0] = 4.503599627370496e15;
        goto continue;
      case 33u:
        table = stack + 16 * (unsigned __int8)(instruction_ptr >> 18);
        v113 = (__int64 *)(stack + 16 * (instruction_ptr & 0x1FF));
        v232 = v113;
        v233 = !*((_DWORD *)v113 + 2) || *((_DWORD *)v113 + 2) == 3 && !*(_DWORD *)v113;
        if ( v233 == ((instruction_ptr >> 9) & 0x1FF) )
          goto LABEL_208;
        v114 = table;
        v115 = v232;
        *(_DWORD *)table = *(_DWORD *)v113;
        *(_DWORD *)(v114 + 4) = *((_DWORD *)v115 + 1);
        *(_DWORD *)(v114 + 8) = *((_DWORD *)v115 + 2);
        goto LABEL_204;
      case 34u:                                 // OP_RETURN
        v224 = instruction_ptr >> 26;
        switch ( instruction_ptr >> 26 )        // encryption lol
        {
          case 0x1Bu:
          case 0x1Fu:
          case 0x22u:
          case 0x25u:
            nresults -= 3724935 * instruction_ptr;
            v183 = (v224 << 26) | ((0x1451AFB * instruction_ptr - 27776373) ^ (unsigned int)nresults) & 0x3FFFFFF;
            break;
          default:
            v183 = instruction_ptr;
            break;
        }
        v184 = stack + 16 * (unsigned __int8)(v183 >> 18);
        v224 = v184;
        v185 = v183 & 0x1FF;
        if ( v185 )
          *(_DWORD *)(rL_ + 16) = v184 + 16 * v185 - 16;
        if ( *(_DWORD *)(rL_ + 120) )
        {
          sub_13FDB0(rL_, stack);
          v184 = v224;
        }
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v186 = sub_13F630(rL_, (_DWORD *)v184);
        if ( !--nexeccalls )
          return;
        v6.m128d_f64[0] = 4.503599627370496e15;
        enc_savedpc = (_DWORD *)(rL_ + 20);
        v5 = (_DWORD *)(rL_ + 8);
        if ( !v186 )
          goto LABEL_3;
        enc_savedpc = (_DWORD *)(rL_ + 20);
        *(_DWORD *)(rL_ + 16) = *(_DWORD *)(*(_DWORD *)(rL_ + 12) + 8);
        v5 = (_DWORD *)(rL_ + 8);
        goto re_entry;
      case 35u:                                 // OP_FORPREP
        v129 = (__int64 *)(stack + 16 * (unsigned __int8)(instruction_ptr >> 18));
        nresults = v129 + 4;
        *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
        v130 = *((_DWORD *)v129 + 2);
        v232 = v129;
        if ( v130 == 2 )
        {
          v131 = v232;
        }
        else
        {
          if ( v130 != 4 || !sub_142470((unsigned __int8 *)(*(_DWORD *)v129 + 24), &v216) )
            luaG_runerror(rL_, "'for' initial value must be a number");
          v131 = v232;
          *v232 = *(_QWORD *)&v216 ^ xor_constant;
          *((_DWORD *)v131 + 2) = 2;
        }
        v132 = *((_DWORD *)v131 + 6);
        if ( v132 != 2 )
        {
          if ( v132 != 4
            || !sub_142470((unsigned __int8 *)(*((_DWORD *)v131 + 4) + 24), &v214)
            || (v131[2] = *(_QWORD *)&v214 ^ xor_constant, *((_DWORD *)v131 + 6) = 2, v131 == (__int64 *)-16) )
          {
            luaG_runerror(rL_, "'for' limit must be a number");
          }
        }
        v133 = nresults;
        if ( *((_DWORD *)nresults + 2) != 2 )
        {
          v133 = (__int64 *)sub_144FB0(nresults, nresults);
          nresults = v133;
          if ( !v133 )
            luaG_runerror(rL_, "'for' step must be a number");
        }
        v134 = *v133;
        v135 = xor_constant;
        v136 = program_counter_;
        v137 = COERCE_DOUBLE(*v131 ^ xor_constant) - COERCE_DOUBLE(v134 ^ xor_constant);
        *((_DWORD *)v131 + 2) = 2;
        *v131 = *(_QWORD *)&v137 ^ v135;
        program_counter_ = &v136[(instruction_ptr_ & 0x3FFFF) - 0x1FFFF];
        if ( (unsigned int)(retaddr - (_BYTE *)off_E41000) < 0xBAB3CA
          || (unsigned int)(retaddr - (_BYTE *)off_DB02F0) < 0x122AC0 )
        {
LABEL_272:
          program_counter = program_counter_;
LABEL_273:
          v6.m128d_f64[0] = 4.503599627370496e15;
        }
        else
        {
          dword_107AF28 |= 0x200000u;
          dword_16358C4 = 0;
          sub_14BB70(rL_);
          v6.m128d_f64[0] = 4.503599627370496e15;
          program_counter = program_counter_;
        }
        goto continue;
      case 36u:
        v232 = (__int64 *)(16 * (unsigned __int8)(instruction_ptr >> 18));
        v233 = (int)v232 + stack;
        table = *(_DWORD *)(rL_ + 12);
        nresults = (__int64 *)((*(_DWORD *)(table + 12) - *(_DWORD *)(table + 16)) >> 4);
        v161 = (instruction_ptr & 0x1FF) - 1;
        nresults = (__int64 *)((char *)nresults - *(unsigned __int8 *)(*(_DWORD *)(l_ci_1 + 16) + l_ci_1 + 89));
        nresults = (__int64 *)((char *)nresults - 1);
        stack = base;
        if ( v161 == -1 )
        {
          *(_DWORD *)(rL_ + 20) = (char *)program_counter - rL_ - 20;
          v162 = *(_DWORD *)(rL_ + 32) - *(_DWORD *)(rL_ + 16);
          instruction_ptr_ = 16 * (_DWORD)nresults;
          if ( v162 <= 16 * (int)nresults )
          {
            v163 = *(_DWORD *)(rL_ + 48);
            if ( (int)nresults > v163 )
              v164 = (int)nresults + v163;
            else
              v164 = 2 * v163;
            luaD_reallocstack(rL_, v164);
          }
          stack = *(_DWORD *)(rL_ + 28);
          v161 = (int)nresults;
          v233 = (int)v232 + stack;
          base = stack;
          *(_DWORD *)(rL_ + 16) = (char *)v232 + stack + instruction_ptr_;
        }
        v6.m128d_f64[0] = 4.503599627370496e15;
        instruction_ptr_ = 0;
        if ( v161 <= 0 )
          continue;
        v165 = (int)nresults;
        v166 = instruction_ptr_;
        v167 = -16 * (_DWORD)nresults;
        v168 = (__int64 *)(v233 + 8);
        v232 = (__int64 *)(v233 + 8);
        do
        {
          if ( v166 >= v165 )
          {
            *(_DWORD *)v168 = 0;
          }
          else
          {
            v169 = v232;
            v170 = *(_DWORD *)(table + 12);
            *((_DWORD *)v232 - 2) = *(_DWORD *)(v170 + v167);
            *((_DWORD *)v169 - 1) = *(_DWORD *)(v170 + v167 + 4);
            *(_DWORD *)v169 = *(_DWORD *)(v170 + v167 + 8);
            v166 = instruction_ptr_;
            v168 = v169;
            v165 = (int)nresults;
          }
          ++v166;
          v168 += 2;
          v167 += 16;
          instruction_ptr_ = v166;
          v232 = v168;
        }
        while ( v166 < v161 );
        v6.m128d_f64[0] = 4.503599627370496e15;
        program_counter = program_counter_;
        goto LABEL_4;
      case 37u:                                 // OP_CLOSURE
        v199 = *(_DWORD *)(l_ci_1 + 12);
        table = stack
              + 16
              * (unsigned __int8)((((21306107 * instruction_ptr - 27776373) ^ (unsigned int)&nresults[-3724935 * instruction_ptr]) & 0x3FFFFFF | 0x94000000) >> 18);
        v151 = *(_DWORD *)(l_ci_1
                         + *(_DWORD *)(l_ci_1 + 16)
                         + 24
                         + 4
                         * (((21306107 * instruction_ptr - 27776373) ^ (unsigned int)&nresults[-3724935
                                                                                             * instruction_ptr]) & 0x3FFFF)
                         + *(_DWORD *)(l_ci_1 + *(_DWORD *)(l_ci_1 + 16) + 24));
        v233 = *(unsigned __int8 *)(v151 + 74);
        v152 = luaF_newlclosure(rL, v233, v199);
        v153 = v233 <= 0;
        nresults = (__int64 *)v152;
        *(_DWORD *)(v152 + 16) = v151 - (v152 + 16);
        if ( !v153 )
        {
          v154 = program_counter_;
          v155 = (__int64 *)(v152 + 20);
          v232 = (__int64 *)(v152 + 20);
          do
          {
            v156 = (encrypted_index * *v154) & 0x1FF;
            if ( ((encrypted_index * *v154) & 0xFC000000) == 0x8000000 )
            {
              v157 = *(_DWORD *)(l_ci_1 + 4 * v156 + 20);
            }
            else
            {
              v157 = sub_13FEB0(rL, base + 16 * v156);
              v155 = v232;
            }
            *(_DWORD *)v155 = v157;
            v155 = (__int64 *)((char *)v155 + 4);
            ++v154;
            v15 = v233-- == 1;
            v232 = v155;
          }
          while ( !v15 );
          program_counter_ = v154;
        }
        v158 = table;
        program_counter = program_counter_;
        v159 = (_DWORD *)v222;
        rL_ = rL;
        *(_DWORD *)table = nresults;
        v160 = enc_savedpc_;
        *(_DWORD *)(v158 + 8) = 6;
        *(_DWORD *)v160 = (char *)program_counter - v160;
        if ( *(_DWORD *)((char *)v159 + *v159 + 88) >= *(_DWORD *)((char *)v159 + *v159 + 76) )
          luaC_step(rL);
        stack = *(_DWORD *)(rL + 28);
        v6.m128d_f64[0] = 4.503599627370496e15;
        base = stack;
        continue;
      default:
        continue;
    }
  }
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  table = -12235722;
  v188 = 0;
  while ( ExceptionList->Next != (_EXCEPTION_REGISTRATION_RECORD *)-1 )
  {
    if ( (char *)((char *)ExceptionList->Handler - 27182026) <= (char *)table )
    {
      v189 = 3 * v188 + 1;
      goto LABEL_325;
    }
    ++v188;
    ExceptionList = ExceptionList->Next;
    if ( v188 >= 2 )
      return;
  }
  if ( (PEXCEPTION_ROUTINE *)((char *)&ExceptionList[3].Next[-3397754].Handler + 2) > (PEXCEPTION_ROUTINE *)table )
    return;
  v189 = 3 * v188;
LABEL_325:
  if ( 1 << v189 )
    unk_1659AC8 |= 0x1000u;
}
