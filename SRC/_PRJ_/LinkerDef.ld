/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-tricore")
OUTPUT_ARCH(tricore)
EXTERN(STARTUP_START)
EXTERN(ApplIntJmpTable)
EXTERN(TotalNumberOfCores)
ENTRY(STARTUP_START)

__TRICORE_DERIVATE_MEMORY_MAP__ = 0x230;

/* LCF_CSA0_SIZE shall be consistent with CSA_CPU0_SIZE in APPLI_StackSize.h */
LCF_CSA0_SIZE      = 8k;
/* LCF_USTACK0_SIZE shall be consistent with USTACK_CPU0_SIZE in APPLI_StackSize.h */
LCF_USTACK0_SIZE   = 8k;
LCF_ISTACK0_SIZE   = 1k;

LCF_CALIB_SIZE     = 64k;
LCF_HEAP_SIZE      = 2k;

LCF_DSPR0_START    = 0x70000000;
LCF_DSPR0_SIZE     = 184k;

LCF_CSA0_OFFSET    = (LCF_DSPR0_SIZE     - LCF_CSA0_SIZE);
LCF_ISTACK0_OFFSET = (LCF_CSA0_OFFSET    - 256 - LCF_ISTACK0_SIZE);
LCF_USTACK0_OFFSET = (LCF_ISTACK0_OFFSET - 256 - LCF_USTACK0_SIZE);

LCF_HEAP0_OFFSET   = (LCF_USTACK0_OFFSET - LCF_HEAP_SIZE);

LCF_CKS_CAL        = 0x80060000;
LCF_CALIB_BEG      = 0x80060024;

LCF_INTVEC0_START  = 0x80100000;
LCF_TRAPVEC0_START = 0x80102000;
LCF_APPLVECT_START = 0x80102520;
LCF_CKS_LOG        = 0x80102540;
LCF_VER_LDB        = 0x80102544;
LCF_CKS_TMS_LOG    = 0x8010254C;
LCF_TMS_CODE_BEG   = 0x80102550;
LCF_FBL_SIGN       = 0x8001FFC0;
LCF_CODE_COPY_CALIB = 0x801C0000;

RESET = 0x80000020;

Calibration_debut =__CALIB_BEGIN;
Calibration_fin   =__CALIB_END;

MEMORY
{

   dsram0_local (w!xp): org = 0xd0010000, len = 1K
   dsram0 (w!xp):       org = 0x70010400, len = 119K
   dsram_calib (w!xp):  org = 0x70000000, len = 64K
   psram0 (w!xp): org = 0x70100000, len = 8K

   psram_local (w!xp): org = 0xc0000000, len = 24K

   pfls0 (rx!p): org = 0x80000000, len = 2M
   pfls0_nc (rx!p): org = 0xA0000000, len = 2M

   dfls0 (rx!p): org = 0xaf000000, len = 128K

   edmem (w!xp): org = 0x9f000000, len = 512K
   edmem_nc (w!xp): org = 0xbf000000, len = 512K
}

/* map local memory address to a global address */ 
REGION_MAP( CPU0 , ORIGIN(dsram0_local), LENGTH(dsram0_local), ORIGIN(dsram0))

/*Un comment one of the below statements to enable CpuX DMI RAM to hold global variables*/
/*REGION_ALIAS( default_ram , dsram0)*/
REGION_ALIAS( default_ram , dsram0)
/*REGION_ALIAS( default_ram , dsram2)*/

CORE_ID = GLOBAL ;

SECTIONS
{
   /*This section is always required as Boot mode header 0 address absolutely restricted at address 0x80000000*/
   .bmhd_0 (0x80000000) : FLAGS(arl)
   {
      BootModeHeader0 = .;
      KEEP (*(.bmhd_0))
   } > pfls0

   /*This section is always required as user start address absolutely restricted at address 0x80000020*/
   .startup (0x80000020) : FLAGS(rxl)
   {
      BootModeIndex = .;
      . = ALIGN(8);
      KEEP (*(.start))
      . = ALIGN(8);
   } > pfls0 =0x800

   /*This section is always required as Boot mode header 1 address absolutely restricted at address 0x80020000*/
   .bmhd_1 (0x80020000) : FLAGS(arl)
   {
      BootModeIndex = .;
      KEEP (*(.bmhd_1))
   } > pfls0

   .FblSignature (LCF_FBL_SIGN): FLAGS(arl)
   {
      FblSignature = .;
      KEEP (*(.FblSignature))
   } > pfls0
   
   .acmsa (0x80050000): FLAGS(arl)
   { 
      AppCalibMarkerStartArea = .;
      KEEP (*(.acmsa))
      . = ALIGN(4);
    } > pfls0 
    
   CKS_CAL (LCF_CKS_CAL) : FLAGS(arl)
   {
      KEEP(*(CKS_CAL));
      . = ALIGN(4);
   } > pfls0

/******************************************************************************/
/* Calibrations                                                               */
/******************************************************************************/
   .calib (LCF_CALIB_BEG) : FLAGS(arl)
   {
      . = ALIGN(4);
      PROVIDE(__CALIB_BEGIN = .);
      SHORT(0);
      KEEP(*(CALIB_BEG));
      KEEP(*(CKS_TMS_CAL));
      . = ALIGN(4);
      KEEP(*(TMS_CALIB_BEG));
      KEEP(*(TMS_CALIB));
      . = ALIGN(4);
      KEEP(*(TMS_CALIB_END));
      KEEP(*(.calib));
      KEEP(*(.calib.*));
      KEEP(*(CALIB)); /* optional, artifact from Renesas mapping */
   } > pfls0

   .calib_cpu0  : FLAGS(arl)
   {
      PROVIDE(__CALIB_CPU0_BEGIN = .);
      KEEP(*(.calib_cpu0));
      KEEP(*(.calib_cpu0.*));
      . = ALIGN(8);
      PROVIDE(__CALIB_CPU0_END = .);
      PROVIDE(__CALIB_END = .);
      . = LCF_CKS_CAL + LCF_CALIB_SIZE - 4;
      LONG(-1);
   } > pfls0 = -1


   .eeprom  : FLAGS(axl)
   {
      *(.eeprom)
      *(.eeprom.*)
      *(EEPROM) /* optional, artifact from Renesas mapping */
      . = ALIGN(8);
   } > dfls0

/******************************************************************************/
/* Interrupts vector table                                                    */
/******************************************************************************/

   .inttab.osinterrupts (LCF_INTVEC0_START + 0x0) : FLAGS(axl)
   {
      KEEP(*(.inttab.osinterrupts));
      KEEP(*(.inttab.osinterrupts.*));
   }
   
   __INTTAB_CPU0 = LCF_INTVEC0_START;

/******************************************************************************/
/* Traps vector table                                                         */
/******************************************************************************/
   .traptab_tc0 (LCF_TRAPVEC0_START) :
   {
      PROVIDE(__TRAPTAB_CPU0 = .);
      KEEP (*(.traptab_cpu0*));
      PROVIDE(__TRAPTAB_CPU0_END = .);
      KEEP(*(.inttab.ostraps));
      KEEP(*(.inttab.ostraps.*));
   } > pfls0

   .applvect (LCF_APPLVECT_START):
   {
      KEEP (*(APPLVECT));
      . = ALIGN(4);
   } > pfls0
   
   CKS_LOG (LCF_CKS_LOG) : FLAGS(arl)
   {
      KEEP(*(CKS_LOG));
      . = ALIGN(4);
   } > pfls0

   VER_LDB (LCF_VER_LDB) : FLAGS(arl)
   {
      KEEP(*(VER_LDB));
      . = ALIGN(4);
   } > pfls0

   CKS_TMS_LOG (LCF_CKS_TMS_LOG) : FLAGS(arl)
   {
      KEEP(*(CKS_TMS_LOG));
      . = ALIGN(4);
   } > pfls0


   TMS_CODE_BEG (LCF_TMS_CODE_BEG) : FLAGS(arl)
   {
      . = ALIGN(4);
      KEEP(*(TMS_CODE_BEG));
   } > pfls0

   TMS_CODE : FLAGS(axl)
   {
      *(TMS_CODE)
   } > pfls0

   TMS_CODE_END : FLAGS(arl)
   {
      . = ALIGN(4);
      KEEP(*(TMS_CODE_END));
   } > pfls0
   
/******************************************************************************/
/* CODE DATA area                                                             */
/******************************************************************************/

   .zrodata : FLAGS(arl)
   {
      *(.zrodata)
      *(.zrodata.*)
   } > pfls0

   .sdata2 : FLAGS(arsl)
   {
      *(.srodata)
      *(.srodata.*)
   } > pfls0

   _SMALL_DATA2_ = SIZEOF(CORE_SEC(.sdata2)) ? ADDR(CORE_SEC(.sdata2)) + 32k : (ADDR(CORE_SEC(.sdata2)) & 0xF0000000) + 32k ;
   __A1_MEM = _SMALL_DATA2_;

   .rodata ALIGN(4) : FLAGS(arl)
   {
      *(.rodata)
      *(.rodata.*)
      *(.gnu.linkonce.r.*)
      /*
      * Create the clear and copy tables that tell the startup code
      * which memory areas to clear and to copy, respectively.
      */
      . = ALIGN(4) ;
      PROVIDE(__clear_table = .) ;
      LONG(0 + ADDR(.CPU1.zbss));             LONG(SIZEOF(.CPU1.zbss));
      LONG(0 + ADDR(.CPU1.bss));              LONG(SIZEOF(.CPU1.bss));
      LONG(0 + ADDR(.CPU0.zbss));             LONG(SIZEOF(.CPU0.zbss));
      LONG(0 + ADDR(.CPU0.bss));              LONG(SIZEOF(.CPU0.bss));
      LONG(0 + ADDR(.zbss));                  LONG(SIZEOF(.zbss));
      LONG(0 + ADDR(.sbss));                  LONG(SIZEOF(.sbss));
      LONG(0 + ADDR(.bss));                   LONG(SIZEOF(.bss));
      LONG(-1);                               LONG(-1);
      PROVIDE(__copy_table = .) ;
      LONG(LOADADDR(.CPU1.zdata));            LONG(0 + ADDR(.CPU1.zdata));            LONG(SIZEOF(.CPU1.zdata));
      LONG(LOADADDR(.CPU1.data));             LONG(0 + ADDR(.CPU1.data));             LONG(SIZEOF(.CPU1.data));
      LONG(LOADADDR(.CPU0.zdata));            LONG(0 + ADDR(.CPU0.zdata));            LONG(SIZEOF(.CPU0.zdata));
      LONG(LOADADDR(.CPU0.data));             LONG(0 + ADDR(.CPU0.data));             LONG(SIZEOF(.CPU0.data));
      LONG(LOADADDR(.zdata));                 LONG(0 + ADDR(.zdata));                 LONG(SIZEOF(.zdata));
      LONG(LOADADDR(.sdata));                 LONG(0 + ADDR(.sdata));                 LONG(SIZEOF(.sdata));
      LONG(LOADADDR(.data));                  LONG(0 + ADDR(.data));                  LONG(SIZEOF(.data));
      LONG(LOADADDR(.code_cached_cpu0));      LONG(0 + ADDR(.code_cached_cpu0));      LONG(SIZEOF(.code_cached_cpu0));
      LONG(LOADADDR(.CPU0.endless_loop));     LONG(0 + ADDR(.CPU0.endless_loop));     LONG(SIZEOF(.CPU0.endless_loop)); 
      LONG(LOADADDR(.code_copy_calib));       LONG(0 + ADDR(.code_copy_calib));       LONG(SIZEOF(.code_copy_calib)); 
      LONG(LOADADDR(.const_copy_calib));      LONG(0 + ADDR(.const_copy_calib));      LONG(SIZEOF(.const_copy_calib)); 
      LONG(-1);                               LONG(-1);                               LONG(-1);
      PROVIDE(__power_on_clear_table = .) ;
      LONG(0 + ADDR(.CPU1.power_on_cleared)); LONG(SIZEOF(.CPU1.power_on_cleared));
      LONG(0 + ADDR(.CPU0.power_on_cleared)); LONG(SIZEOF(.CPU0.power_on_cleared));
      LONG(0 + ADDR(.power_on_cleared));      LONG(SIZEOF(.power_on_cleared));
      LONG(0 + ADDR(.CPU1.uncleared));        LONG(SIZEOF(.CPU1.uncleared));
      LONG(0 + ADDR(.CPU0.uncleared));        LONG(SIZEOF(.CPU0.uncleared));
      LONG(0 + ADDR(.uncleared));             LONG(SIZEOF(.uncleared));
      LONG(-1);                               LONG(-1);
      PROVIDE(__power_on_copy_table = .) ;
      LONG(LOADADDR(.CPU1.power_on_init));    LONG(0 + ADDR(.CPU1.power_on_init)); LONG(SIZEOF(.CPU1.power_on_init));
      LONG(LOADADDR(.CPU0.power_on_init));    LONG(0 + ADDR(.CPU0.power_on_init)); LONG(SIZEOF(.CPU0.power_on_init));
      LONG(LOADADDR(.power_on_init));         LONG(0 + ADDR(.power_on_init));      LONG(SIZEOF(.power_on_init));
      LONG(-1);                                LONG(-1);                            LONG(-1);
      . = ALIGN(8);
   } > pfls0

   .text  : FLAGS(axl)
   {
      *(.text)
      *(.text.*)
      *(.gnu.linkonce.t.*)
      *(.gnu.warning)        /* .gnu.warning sections are handled specially by elf32.em. */
      . = ALIGN(8);
   } > pfls0

   .code  : FLAGS(axl)
   {
      *(.code)
      *(.code.*)
      *(CODE) /* optional, artifact from Renesas mapping */
      . = ALIGN(8);
   } > pfls0

   .const  : FLAGS(arl)
   {
      KEEP(*(.const));
      KEEP(*(.const.*));
      KEEP(*(CONST)); /* optional, artifact from Renesas mapping */
      . = ALIGN(8);
   } > pfls0
   
   .code_cpu0  : FLAGS(axl)
   {
      *(.code_cpu0)
      *(.code_cpu0.*)
      . = ALIGN(8);
   } > pfls0

   .code_cached_cpu0  : FLAGS(axl)
   {
      *(.code_cached_cpu0)
      *(.code_cached_cpu0.*)
      . = ALIGN(8);
   } > psram0 AT> pfls0

   .const_cpu0  : FLAGS(arl)
   {
      KEEP(*(.const_cpu0));
      KEEP(*(.const_cpu0.*));
      . = ALIGN(8);
   } > pfls0

   .code_cpu1  : FLAGS(axl)
   {
      *(.code_cpu1)
      *(.code_cpu1.*)
      . = ALIGN(8);
   } > pfls0

   .code_cached_cpu1  : FLAGS(axl)
   {
      *(.code_cached_cpu1)
      *(.code_cached_cpu1.*)
      . = ALIGN(8);
   } > psram0 AT> pfls0

   .const_cpu1  : FLAGS(arl)
   {
      KEEP(*(.const_cpu1));
      KEEP(*(.const_cpu1.*));
      . = ALIGN(8);
   } > pfls0
}

/******************************************************************************/
/* RAM area                                                                   */
/******************************************************************************/

/*Near data sections*/

CORE_ID = CPU1;

SECTIONS
{
   CORE_SEC(.zdata) (LCF_DSPR0_START): FLAGS(awzl)
   {
      . = ALIGN(4) ;
      KEEP(*(.zdata_cpu1));
      KEEP(*(.zdata_cpu1.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0

    CORE_SEC(.zbss): FLAGS(awz)
   {
      . = ALIGN(4) ;
      KEEP(*(.zbss_cpu1));
      KEEP(*(.zbss_cpu1.*));
      . = ALIGN(4) ;
   } > dsram0
}

CORE_ID = CPU0;

SECTIONS
{
    CORE_SEC(.endless_loop): FLAGS(ax)
   {
      . = ALIGN(8);
      KEEP(*(.rtmcld_endless_loop));
      KEEP(*(.rtmcld_endless_loop.*));
      . = ALIGN(8);
   } > psram0 AT> pfls0

   CORE_SEC(.zdata) (LCF_DSPR0_START): FLAGS(awzl)
   {
      . = ALIGN(4) ;
      KEEP(*(.zdata_cpu0));
      KEEP(*(.zdata_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0

   .code_copy_calib : FLAGS(axl)
   {
      . = ALIGN(8);
      KEEP(*(.code_copy_calib));
      KEEP(*(.code_copy_calib.*));
      . = ALIGN(8);
   } > psram0 AT> pfls0
   .const_copy_calib : FLAGS(arl)
   {
      . = ALIGN(8);
      KEEP(*(.const_copy_calib));
      KEEP(*(.const_copy_calib.*));
      . = ALIGN(8);
   } > psram0 AT> pfls0

   CORE_SEC(.zbss) (NOLOAD): FLAGS(awz)
   {
      . = ALIGN(4) ;
      KEEP(*(.zbss_cpu0));
      KEEP(*(.zbss_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0
}

/*RAM sections without cpu sufix will go to default ram defined above with REGION_ALIAS*/

CORE_ID = GLOBAL;

SECTIONS
{

   CORE_SEC(.zdata) : FLAGS(awzl)
   {
      . = ALIGN(4) ;
      KEEP(*(.zdata));
      KEEP(*(.zdata.*));
      *(.gnu.linkonce.z.*)
      . = ALIGN(4) ;
   } > default_ram AT> pfls0

   CORE_SEC(.zbss) (NOLOAD) : FLAGS(awz)
   {
      . = ALIGN(4) ;
      KEEP(*(.zbss));
      KEEP(*(.zbss.*));
      KEEP(*(.bbss));
      KEEP(*(.bbss.*));
      *(.gnu.linkonce.zb.*)
      . = ALIGN(4) ;
   } > default_ram

   CORE_SEC(.sdata) : FLAGS(awsl)
   {
      . = ALIGN(4) ;
      KEEP(*(.sdata));
      KEEP(*(.sdata.*));
      . = ALIGN(4) ;
   } > default_ram AT> pfls0
   _SMALL_DATA_ = SIZEOF(CORE_SEC(.sdata)) ? ADDR(CORE_SEC(.sdata)) + 32k : (ADDR(CORE_SEC(.sdata)) & 0xF0000000) + 32k ;
   __A0_MEM = _SMALL_DATA_;
   
   CORE_SEC(.sbss) (NOLOAD): FLAGS(aws)
   {
      . = ALIGN(4) ;
      KEEP(*(.sbss));
      KEEP(*(.sbss.*));
      . = ALIGN(4) ;
   } > default_ram

   CORE_SEC(.uncleared) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.uncleared));
      KEEP(*(.uncleared.*));   
      . = ALIGN(4) ;
   } > default_ram AT> pfls0

   CORE_SEC(.data) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.data));
      KEEP(*(.data.*));
      *(.gnu.linkonce.d.*)
      . = ALIGN(4) ;
   } > default_ram AT> pfls0

   CORE_SEC(.power_on_init) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.power_on_init));
      KEEP(*(.power_on_init.*));
      . = ALIGN(4) ;
   } > default_ram AT> pfls0

   CORE_SEC(.bss) (NOLOAD) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.bss));
      KEEP(*(.bss.*));
      *(.gnu.linkonce.b.*)
      . = ALIGN(4) ;
   } > default_ram

   CORE_SEC(.power_on_cleared) (NOLOAD) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.power_on_cleared));
      KEEP(*(.power_on_cleared.*));
	  KEEP(*(.all_ram_clear_at_init_flag));
      KEEP(*(.all_ram_clear_at_init_flag.*));
      . = ALIGN(4) ;
   } > default_ram

   CORE_SEC(.data) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.data_cpu0));
      KEEP(*(.data_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0
}

CORE_ID = CPU1;

SECTIONS
{
   CORE_SEC(.uncleared) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.uncleared_cpu1));
      KEEP(*(.uncleared_cpu1.*));   
      . = ALIGN(4) ;
   } > dsram0

   CORE_SEC(.data) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.data_cpu1));
      KEEP(*(.data_cpu1.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0

   CORE_SEC(.power_on_init) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.power_on_init_cpu1));
      KEEP(*(.power_on_init_cpu1.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0
   
   CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.bss_cpu1));
      KEEP(*(.bss_cpu1.*));
      . = ALIGN(4) ;
   } > dsram0
   
   CORE_SEC(.power_on_cleared) (NOLOAD) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.power_on_cleared_cpu1));
      KEEP(*(.power_on_cleared_cpu1.*));
      . = ALIGN(4) ;
   } > dsram0
}

CORE_ID = CPU0;

SECTIONS
{
   CORE_SEC(.uncleared) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.uncleared_cpu0));
      KEEP(*(.uncleared_cpu0.*));   
      . = ALIGN(4) ;
   } > dsram0

   CORE_SEC(.data) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.data_cpu0));
      KEEP(*(.data_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0

   CORE_SEC(.power_on_init) : FLAGS(awl)
   {
      . = ALIGN(4) ;
      KEEP(*(.power_on_init_cpu0));
      KEEP(*(.power_on_init_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0 AT> pfls0
   
   CORE_SEC(.bss) (NOLOAD): FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.bss_cpu0));
      KEEP(*(.bss_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0
   
   CORE_SEC(.power_on_cleared) (NOLOAD) : FLAGS(aw)
   {
      . = ALIGN(4) ;
      KEEP(*(.power_on_cleared_cpu0));
      KEEP(*(.power_on_cleared_cpu0.*));
      . = ALIGN(4) ;
   } > dsram0
}


/******************************************************************************/
/* Stacks area                                                                */
/******************************************************************************/

CORE_ID = GLOBAL;

SECTIONS
{
   CORE_SEC(.ustack) (LCF_DSPR0_START + LCF_USTACK0_OFFSET): FLAGS(aw)
   {
      PROVIDE(__USTACK0_END = .);
      . = ALIGN(4) ;
      KEEP(*(.ustack_cpu0));
      KEEP(*(.ustack_cpu0.*));
      . = ALIGN(4) ;
      PROVIDE(__USTACK0 = LCF_DSPR0_START + LCF_USTACK0_OFFSET + LCF_USTACK0_SIZE);
   } > dsram0

   CORE_SEC(.istack) (LCF_DSPR0_START + LCF_ISTACK0_OFFSET): FLAGS(aw)
   {
      PROVIDE(__ISTACK0_END = .);
      *(.istack_cpu0)
      PROVIDE(__ISTACK0 = LCF_DSPR0_START + LCF_ISTACK0_OFFSET + LCF_ISTACK0_SIZE);
   } > dsram0

   CORE_SEC(.csa) (LCF_DSPR0_START + LCF_CSA0_OFFSET): FLAGS(aw)
   {
      PROVIDE(__CSA0 = .);
      . = ALIGN(64) ;
      KEEP(*(.csa_cpu0));
      KEEP(*(.csa_cpu0.*));
      PROVIDE(__CSA0_END = LCF_DSPR0_START + LCF_CSA0_OFFSET + LCF_CSA0_SIZE);
   } > dsram0
}


/******************************************************************************/
/* Miscellaneous                                                              */
/******************************************************************************/

CORE_ID = GLOBAL;

SECTIONS
{
   CORE_SEC(.sdata3) : FLAGS(arsl)
   {
      *(.rodata_a8)
      *(.rodata_a8.*)
   } > pfls0

   _SMALL_DATA3_ = SIZEOF(CORE_SEC(.sdata3)) ? ADDR(CORE_SEC(.sdata3)) + 32k : (ADDR(CORE_SEC(.sdata3)) & 0xF0000000) + 32k ;
   __A8_MEM = _SMALL_DATA3_;

   /*
    * DWARF debug sections.
    * Symbols in the DWARF debugging sections are relative to the
    * beginning of the section, so we begin them at 0.
    */
   /*
    * DWARF 1
    */
   .comment         0 : { *(.comment) }
   .debug           0 : { *(.debug) }
   .line            0 : { *(.line) }
   /*
    * GNU DWARF 1 extensions
    */
   .debug_srcinfo   0 : { *(.debug_srcinfo) }
   .debug_sfnames   0 : { *(.debug_sfnames) }
   /*
    * DWARF 1.1 and DWARF 2
    */
   .debug_aranges   0 : { *(.debug_aranges) }
   .debug_pubnames  0 : { *(.debug_pubnames) }
   /*
    * DWARF 2
    */
   .debug_info      0 : { *(.debug_info) }
   .debug_abbrev    0 : { *(.debug_abbrev) }
   .debug_line      0 : { *(.debug_line) }
   .debug_frame     0 : { *(.debug_frame) }
   .debug_str       0 : { *(.debug_str) }
   .debug_loc       0 : { *(.debug_loc) }
   .debug_macinfo   0 : { *(.debug_macinfo) }
   .debug_ranges    0 : { *(.debug_ranges) }
   /*
    * SGI/MIPS DWARF 2 extensions
    */
   .debug_weaknames 0 : { *(.debug_weaknames) }
   .debug_funcnames 0 : { *(.debug_funcnames) }
   .debug_typenames 0 : { *(.debug_typenames) }
   .debug_varnames  0 : { *(.debug_varnames) }
   /*
    * Optional sections that may only appear when relocating.
    */
   /*
    * Optional sections that may appear regardless of relocating.
    */
   .version_info    0 : { *(.version_info) }
   .boffs           0 : { KEEP (*(.boffs)) }


   .acmea (0x801fffe0): FLAGS(arl)
   { 
      AppCalibMarkerEndArea = .;
      KEEP (*(.acmea))
      . = ALIGN(4);
    } > pfls0 
}
